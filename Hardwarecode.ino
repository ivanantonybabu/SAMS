#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// WiFi Credentials
const char* ssid = "Night123";
const char* password = "20202022";

// Server URL
const char* serverName = "http://192.168.120.38:5000/rfid";

// OLED Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SDA_OLED      D2
#define SCL_OLED      D1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RFID Setup
#define SS_PIN    D4
#define RST_PIN   D3
MFRC522 rfid(SS_PIN, RST_PIN);

// Speaker
#define SPEAKER_PIN D8

bool classOngoing = false;
String activeTag = "";
String currentClass = "";

int melody[] = {660, 660, 0, 660, 0, 510, 660, 0, 770, 0, 380};
int duration[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait for WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  // OLED
  Wire.begin(SDA_OLED, SCL_OLED);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }

  display.clearDisplay();
  display.display();

  // RFID
  SPI.begin();
  rfid.PCD_Init();

  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  if (!classOngoing) showTapMessage();

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String tagUID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      tagUID += String(rfid.uid.uidByte[i], HEX);
    }
    tagUID.toUpperCase();

    if (classOngoing && tagUID == activeTag) {
      endClass(tagUID);
    } else {
      if (tagUID == "44F85141") startClass("Python   Class", tagUID);
      else if (tagUID == "D0371858") startClass("AIC Class", tagUID);
      else playPoliceAlarm();
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  if (classOngoing) blinkClassName(currentClass);
}

void sendToServer(String uid, String action, String className = "") {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"uid\":\"" + uid + "\",\"action\":\"" + action + "\",\"class\":\"" + className + "\"}";
    int httpResponseCode = http.POST(payload);
    Serial.println("POST response: " + String(httpResponseCode));
    http.end();
  }
}

void showTapMessage() {
  display.clearDisplay();
  display.setTextSize(2);
  for (int i = 0; i < 3; i++) {
    display.setTextColor(i % 2 == 0 ? SSD1306_WHITE : SSD1306_BLACK);
    display.setCursor(25, 20);
    display.println("Tap Pls");
    display.display();
    delay(500);
  }
}

void startClass(String className, String tagUID) {
  activeTag = tagUID;
  currentClass = className;
  classOngoing = true;

  displayText(className);
  playDoorBell();
  sendToServer(tagUID, "START", className);
}

void endClass(String tagUID) {
  classOngoing = false;
  displayText("Class     Over");
  delay(2000);
  playSuperMario();
  sendToServer(tagUID, "END");
}

void displayText(String text) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println(text);
  display.display();
}

void blinkClassName(String className) {
  displayText(className);
  delay(500);
  display.clearDisplay();
  display.display();
  delay(500);
}

void playDoorBell() {
  tone(SPEAKER_PIN, 1000, 500); delay(500);
  tone(SPEAKER_PIN, 1200, 500); delay(500);
  noTone(SPEAKER_PIN);
}

void playSuperMario() {
  for (int i = 0; i < sizeof(melody)/sizeof(melody[0]); i++) {
    if (melody[i] == 0) delay(duration[i]);
    else {
      tone(SPEAKER_PIN, melody[i], duration[i]);
      delay(duration[i] + 50);
    }
  }
  noTone(SPEAKER_PIN);
}

void playPoliceAlarm() {
  tone(SPEAKER_PIN, 200, 1000);
  delay(1000);
  noTone(SPEAKER_PIN);
}
