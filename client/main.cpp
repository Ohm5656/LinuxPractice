#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include <random>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

struct SensorData {
    int sensor_id;
    int sequence;
    double temperature;
    double humidity;
    std::string created_at;
};

std::string build_json(const SensorData& data) {
    std::ostringstream json;

    json << "{";
    json << "\"sensor_id\":" << data.sensor_id << ",";
    json << "\"sequence\":" << data.sequence << ",";
    json << "\"temperature\":" << data.temperature << ",";
    json << "\"humidity\":" << data.humidity << ",";
    json << "\"created_at\":\"" << data.created_at << "\"";
    json << "}";

    return json.str();
}

std::string now_as_text() {
    auto now = std::chrono::system_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(
        now.time_since_epoch()
    ).count();

    return std::to_string(seconds);
}

bool send_http_post(const std::string& host, const std::string& port, const std::string& path, const std::string& body) {
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo* result = nullptr;
    int lookup_status = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
    if (lookup_status != 0) {
        std::cerr << "getaddrinfo failed\n";
        return false;
    }

    SOCKET client_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "socket failed\n";
        freeaddrinfo(result);
        return false;
    }

    int connect_status = connect(client_socket, result->ai_addr, static_cast<int>(result->ai_addrlen));
    freeaddrinfo(result);

    if (connect_status == SOCKET_ERROR) {
        std::cerr << "connect failed\n";
        closesocket(client_socket);
        return false;
    }

    std::ostringstream request;
    request << "POST " << path << " HTTP/1.1\r\n";
    request << "Host: " << host << "\r\n";
    request << "Content-Type: application/json\r\n";
    request << "Content-Length: " << body.size() << "\r\n";
    request << "Connection: close\r\n";
    request << "\r\n";
    request << body;

    std::string message = request.str();
    int send_status = send(client_socket, message.c_str(), static_cast<int>(message.size()), 0);

    closesocket(client_socket);

    return send_status != SOCKET_ERROR;
}

int main() {
    WSADATA network_data;
    int startup_status = WSAStartup(MAKEWORD(2, 2), &network_data);
    if (startup_status != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_real_distribution<double> temperature_range(24.0, 35.0);
    std::uniform_real_distribution<double> humidity_range(40.0, 80.0);

    for (int sequence = 1; sequence <= 10; sequence++) {
        SensorData data;
        data.sensor_id = 101;
        data.sequence = sequence;
        data.temperature = temperature_range(generator);
        data.humidity = humidity_range(generator);
        data.created_at = now_as_text();

        std::string body = build_json(data);
        bool sent = send_http_post("127.0.0.1", "8080", "/sensor", body);

        if (sent) {
            std::cout << "sent: " << body << std::endl;
        } else {
            std::cerr << "send failed: " << body << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    WSACleanup();
    return 0;
}
