# LinuxPractice 🚀

โปรเจกต์ฝึกเขียนระบบจำลอง **C++ Sensor Controller** ส่งข้อมูลไปยัง **Go Server** เพื่อฝึกพื้นฐาน Linux, Network Programming และ Concurrency แบบค่อยเป็นค่อยไป

## 🧰 Tech Stack

![C++](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus&logoColor=white)
![Go](https://img.shields.io/badge/Go-Concurrency-00ADD8?logo=go&logoColor=white)
![HTTP](https://img.shields.io/badge/Protocol-HTTP-5A45FF)
![TCP](https://img.shields.io/badge/Network-TCP-0B7285)
![Linux](https://img.shields.io/badge/Linux-Practice-FCC624?logo=linux&logoColor=black)
![Bash](https://img.shields.io/badge/Bash-Scripting-4EAA25?logo=gnubash&logoColor=white)

## 🎯 Goal

จำลอง controller ฝั่ง C++ ให้สร้างข้อมูล sensor แล้วส่งเป็น JSON ผ่าน HTTP ไปยัง Go server

ฝั่ง Go จะฝึก:

- รับ HTTP request
- Decode JSON
- ส่งงานเข้า channel
- ประมวลผลด้วย goroutine หลายตัว
- สังเกตการทำงานของ concurrency จาก log

## 🧠 Architecture

```text
C++ Sensor Controller
        |
        | JSON over HTTP
        v
Go HTTP Server
        |
        v
Channel Queue
        |
        +--> Worker Goroutine 1
        +--> Worker Goroutine 2
        +--> Worker Goroutine 3
```

## 📁 Project Structure

```text
.
├── client/
│   └── main.cpp
├── server/
│   ├── go.mod
│   └── main.go
└── README.md
```

## ▶️ Run

### 1. Start Go server

```bash
cd server
go run .
```

ถ้าเครื่องบล็อก `go run` เพราะ policy ให้ build ก่อนแล้วค่อยรัน binary:

```bash
cd server
go build -o server.exe .
./server.exe
```

### 2. Build and run C++ client

บน Windows:

```bash
cd client
g++ main.cpp -lws2_32 -o client.exe
./client.exe
```

## 📚 Learning Path

1. เขียน struct สำหรับ sensor data
2. สร้าง JSON จาก C++
3. ส่ง HTTP request จาก C++
4. รับ JSON ด้วย Go
5. ส่งข้อมูลเข้า channel
6. สร้าง worker goroutine
7. เพิ่มจำนวน sensor และสังเกต concurrency
