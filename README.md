# LinuxPractice

A learning project for building a simulated **C++ Sensor Controller** that sends sensor data to a **Go Server**. The goal is to practice Linux fundamentals, network programming, HTTP/TCP communication, and Go concurrency step by step.

## Tech Stack

![C++](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus&logoColor=white)
![Go](https://img.shields.io/badge/Go-Concurrency-00ADD8?logo=go&logoColor=white)
![HTTP](https://img.shields.io/badge/Protocol-HTTP-5A45FF)
![TCP](https://img.shields.io/badge/Network-TCP-0B7285)
![Linux](https://img.shields.io/badge/Linux-Practice-FCC624?logo=linux&logoColor=black)
![Bash](https://img.shields.io/badge/Bash-Scripting-4EAA25?logo=gnubash&logoColor=white)

## Goal

The C++ side acts like a sensor controller. It generates fake sensor values, converts them into JSON, and sends them to the Go server through HTTP.

The Go side is used to practice:

- Receiving HTTP requests
- Decoding JSON payloads
- Sending work into a channel
- Processing data with multiple goroutines
- Observing concurrency through server logs

## Architecture

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

## Project Structure

```text
.
+-- client/
|   +-- main.cpp
|   +-- README.md
+-- server/
|   +-- go.mod
|   +-- main.go
+-- README.md
```

## Run

### 1. Start the Go server

```bash
cd server
go run .
```

If your machine blocks `go run` because of local policy, build and run the binary instead:

```bash
cd server
go build -o server.exe .
./server.exe
```

### 2. Build and run the C++ client

On Windows:

```bash
cd client
g++ main.cpp -lws2_32 -o client.exe
./client.exe
```

## Learning Path

1. Create a struct for sensor data.
2. Build JSON from C++ values.
3. Send an HTTP request from C++.
4. Receive JSON in Go.
5. Push decoded data into a channel.
6. Create worker goroutines.
7. Increase the number of sensors and observe concurrency.
