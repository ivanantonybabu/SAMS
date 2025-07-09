# Smart Attendance and Engagement Monitoring System (SAMS) 🎓📷📶

An intelligent IoT-based system designed to automate student attendance and monitor classroom engagement using facial recognition, RFID authentication, and Eye Aspect Ratio (EAR) analysis.

## 🔍 Overview

The SAMS project aims to modernize traditional attendance tracking and student monitoring by combining:
- RFID-based teacher authentication
- Real-time facial recognition for student identification
- Engagement analysis using computer vision (EAR)
- A web-based dashboard for attendance/engagement reports
- Firebase backend for data storage

The system architecture is based on a master-slave model:
- **Raspberry Pi 5** as the master unit handling processing, camera, and database
- **NodeMCU (ESP8266)** as the slave controller interfacing with RFID, OLED display, and speaker

## 🛠️ Features

- ✅ RFID-based class session authentication
- 📷 Real-time facial recognition using OpenCV and Dlib
- 👀 Eye Aspect Ratio (EAR)-based engagement monitoring
- 🔔 Audio and visual feedback via speaker and OLED display
- ☁️ Firebase database for secure, real-time data storage
- 🌐 Flask-based HTTP server for communication
- 🖥️ Web-based UI with login and dashboard panel

## 📦 Components Used

### Hardware
- Raspberry Pi 5 (with steel enclosure)
- Pi Camera (5MP or 8MP)
- NodeMCU ESP8266
- RC522 RFID Reader
- 128x64 OLED Display (I2C)
- SmartElex Speaker Module
- Breadboard & Jumper Wires
- 9V and 5V power supplies

### Software & Libraries
- Python 3
- OpenCV, Dlib, MediaPipe
- Flask (for backend API)
- Firebase (Realtime Database)
- Arduino IDE (for NodeMCU)
- HTML/CSS/JS for dashboard

## 📸 System Workflow

1. **Start Class:** Teacher taps authorized RFID tag → NodeMCU sends UID to Flask server
2. **Authentication:** Flask server verifies UID and triggers face recognition on Pi
3. **Attendance Marking:** Pi Camera captures faces → matched students are marked present
4. **Engagement Monitoring:** EAR is calculated continuously → inattentive behavior logged
5. **End Class:** Teacher taps RFID again → session ends, data pushed to Firebase

## 📊 Dashboard

The system includes a responsive web dashboard:
- **Login Page:** Secure access for faculty
- **Dashboard Panel:** View attendance logs, session timestamps, and engagement summaries

## 🧪 Testing & Validation

- Flask server tested under network stress and rapid RFID scans
- Face detection and EAR analysis verified in different lighting conditions
- NodeMCU communication and response times validated for real-time feedback

## 📁 File Structure

/SAMS
├── raspberry/ # Python backend and face recognition
├── nodemcu/ # Arduino code for NodeMCU
├── flask_server/ # Flask-based API
├── firebase_config/ # Firebase keys and integration
├── dashboard/ # HTML/CSS/JS frontend
├── circuit_diagrams/
├── block_diagram.png
└── README.md



## 🚀 Future Scope

- Liveness detection for advanced facial spoof prevention
- Emotion detection for deeper engagement analytics
- Integration with LMS platforms (Google Classroom, Moodle)
- Mobile app for teacher/admin control
- Cloud-based dashboard and analytics reports

## ⚠️ Limitations

- Requires a stable internet connection for cloud sync
- Performance may degrade in large classrooms without upgraded hardware

## 🧠 Developed By

**Ivan Antony Babu**  
Assisted by
Karun santhosh,Hima H, Naveen c lal,Muhsin ali
School of Engineering, CUSAT  
Division of Electronics Engineering

## 📃 License

This project is licensed under the MIT License. Feel free to use and modify with credit.

