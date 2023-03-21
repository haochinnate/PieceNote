#pragma once

#include <Windows.h>

class RS232 {
public:
    RS232(const char* portName, int baudRate);
    ~RS232();

    bool write(const char* data, int length);
    bool read(char* data, int length);

private:
    HANDLE _serialPort;
};

/////////////////////////////////////////

#include "RS232.h"

RS232::RS232(const char* portName, int baudRate) {
    _serialPort = CreateFileA(portName, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
    if (_serialPort == INVALID_HANDLE_VALUE) {
        throw "Unable to open serial port";
    }

    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);
    if (!GetCommState(_serialPort, &serialParams)) {
        throw "Unable to get serial port parameters";
    }
    serialParams.BaudRate = baudRate;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY;
    if (!SetCommState(_serialPort, &serialParams)) {
        throw "Unable to set serial port parameters";
    }
}

RS232::~RS232() {
    if (_serialPort != INVALID_HANDLE_VALUE) {
        CloseHandle(_serialPort);
        _serialPort = INVALID_HANDLE_VALUE;
    }
}

bool RS232::write(const char* data, int length) {
    DWORD bytesWritten = 0;
    if (!WriteFile(_serialPort, data, length, &bytesWritten, nullptr)) {
        return false;
    }
    return (bytesWritten == length);
}

bool RS232::read(char* data, int length) {
    DWORD bytesRead = 0;
    if (!ReadFile(_serialPort, data, length, &bytesRead, nullptr)) {
        return false;
    }
    return (bytesRead == length);
}

//////////////////////////////////////

#include "RS232.h"
#include <iostream>

int main() {
    try {
        RS232 port("COM1", 9600);

        const char* dataToSend = "Hello, world!";
        port.write(dataToSend, strlen(dataToSend));

        char receivedData[256];
        port.read(receivedData, strlen(dataToSend));
        std::cout << receivedData << std::endl;
    }
    catch (const char* errorMessage) {
        std::cerr << errorMessage << std::endl;
        return 1;
    }

    return 0;
}

/////////////////////////////////////////

#include "RS232.h"
#include <cassert>

void testRS232() {
    RS232 port("COM1", 9600);

    const char* dataToSend = "Hello, world!";
    assert(port.write(dataToSend, strlen(dataToSend)));

    char receivedData[256];
    assert(port.read(receivedData,
    strlen(dataToSend)));
    assert(strcmp(receivedData, dataToSend) == 0);
}

int main() {
testRS232();
return 0;
}