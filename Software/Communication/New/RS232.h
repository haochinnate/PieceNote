#pragma once
#include <string>
#include <Windows.h>

class RS232 {
public:
    RS232(std::string portName, unsigned int baudRate);
    ~RS232();

    bool isConnected();
    bool openPort();
    void closePort();
    bool writeData(char* buffer, unsigned int bufSize);
    int readData(char* buffer, unsigned int bufSize);

private:
    HANDLE hComm;
    bool connected;
    DCB dcbSerialParams;
    COMMTIMEOUTS timeouts;
};
