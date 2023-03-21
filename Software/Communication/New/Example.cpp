
現在我們可以提供一個使用 RS232 和 Serial Port 的範例程式，讓使用者參考。

Example.cpp
```c++
#include "RS232.h"
#include "SerialPort.h"
#include <iostream>

int main() {
    // RS232 example
    RS232 rs232("COM1", 9600);
    if (rs232.isConnected()) {
        std::cout << "RS232 connection established." << std::endl;
        char buffer[] = "Hello RS232!";
        rs232.writeData(buffer, sizeof(buffer));
        std::cout << "Data sent via RS232." << std::endl;
        char readBuffer[256];
        int bytesRead = rs232.readData(readBuffer, sizeof(readBuffer));
        std::cout << "Data received via RS232: " << readBuffer << std::endl;
    }
    else {
        std::cout << "Could not establish RS232 connection." << std::endl;
    }

    // Serial Port example
    SerialPort serial("COM2", 9600);
    if (serial.isConnected()) {
        std::cout << "Serial Port connection established." << std::endl;
        char buffer[] = "Hello Serial Port!";
        serial.writeData(buffer, sizeof(buffer));
        std::cout << "Data sent via Serial Port." << std::endl;
        char readBuffer[256];
        int bytesRead = serial.readData(readBuffer, sizeof(readBuffer));
        std::cout << "Data received via Serial Port: " << readBuffer << std::endl;
    }
    else {
        std::cout << "Could not establish Serial Port connection." << std::endl;
    }

    return 0;
}
