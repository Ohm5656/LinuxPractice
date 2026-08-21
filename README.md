# LinuxPractice

A learning project for practicing Linux, Networking, Bash Scripting, Go, C++, and Infrastructure fundamentals.

## Project Goal

จำลอง Client หลายเครื่องส่งข้อมูลผ่าน Network ไปยัง Go Server
เพื่อฝึกทักษะด้าน:

- Linux
- Networking
- Bash Scripting
- C++
- Go
- Client-Server Architecture
- HTTP / TCP
- Concurrency
- Logging
- Monitoring
- Automation

## Architecture

```text
C++ Client Simulator

device-001 ─┐
device-002 ─┤
device-003 ─┤
    ...      ├──── HTTP/TCP ────> Go Server
device-1000 ─┘                       │
                                    ├── Receive Request
                                    ├── Decode JSON
                                    ├── Concurrency
                                    ├── Queue / Channel
                                    ├── Logs
                                    └── Metrics
