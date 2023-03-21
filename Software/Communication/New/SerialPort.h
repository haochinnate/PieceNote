#pragma once
#include <string>
#include <Windows.h>

class SerialPort {
public:
    SerialPort(std::string portName);
    SerialPort(std::string portName, unsigned int baudRate);
    ~SerialPort();

    bool isConnected();
    bool openPort();
    void closePort();
    bool writeData(char* buffer, unsigned int bufSize);
    int readData(char* buffer, unsigned int bufSize);

private:
    HANDLE hSerial;
    bool connected;
    COMSTAT status;
    DWORD errors;

    // another code
    HANDLE hComm;
    bool connected;
    DCB dcbSerialParams;
    COMMTIMEOUTS timeouts;
};
