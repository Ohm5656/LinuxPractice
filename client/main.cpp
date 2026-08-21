#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>

struct SensorData {
    std::string deviceID;
    std::array<int, 5> gates;
};

int main() {

    // ตั้ง seed สำหรับ random แค่ครั้งเดียว
    std::srand(std::time(nullptr));

    // vector สำหรับเก็บหลาย device
    std::vector<SensorData> sensors;

    // ==============================
    // สร้าง Device 5 เครื่อง
    // ==============================
    for (int a = 0; a < 5; a++) {

        SensorData sensor;

        // device-1, device-2, ...
        sensor.deviceID = "device-" + std::to_string(a + 1);

        // ใส่ device ที่สร้างเสร็จลง vector
        sensors.push_back(sensor);
    }

    // ==============================
    // ทำงานไปเรื่อย ๆ จน Ctrl + C
    // ==============================
    while (true) {

        // วนทุก Device
        for (int a = 0; a < 5; a++) {

            // สุ่ม Sensor 5 ค่าให้ Device นี้
            for (int i = 0; i < 5; i++) {
                sensors[a].gates[i] = std::rand() % 101;
            }
        }

        // ==============================
        // แสดงข้อมูลทั้งหมด
        // ==============================
        for (int a = 0; a < 5; a++) {

            std::cout << "Device : "
                      << sensors[a].deviceID
                      << std::endl;

            for (int i = 0; i < 5; i++) {

                std::cout << "Sensor "
                          << i + 1
                          << " : "
                          << sensors[a].gates[i]
                          << std::endl;
            }

            std::cout << "--------------------" << std::endl;
        }

        // รอ 1 วินาที ก่อนสุ่มข้อมูลรอบใหม่
        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }

    return 0;
}
