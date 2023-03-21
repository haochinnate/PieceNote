#ifndef SERIALPORT_WINAPI_H
#define SERIALPORT_WINAPI_H

#include <string>
#include <windows.h>

class SerialPort {
public:
    SerialPort(std::string portName, int baudRate);
    ~SerialPort();

    bool isConnected();
    bool writeData(const char* data, int dataSize);
    int readData(char* buffer, int bufferSize);

private:
    std::string m_portName;
    int m_baudRate;
    HANDLE m_handle;
};

#endif // SERIALPORT_WINAPI_H
