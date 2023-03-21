#include "SerialPort_WinAPI.h"
#include <iostream>

SerialPort::SerialPort(std::string portName, int baudRate) : m_portName(portName), m_baudRate(baudRate) {
    m_handle = CreateFile(m_portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (m_handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: could not connect to serial port." << std::endl;
    }
    else {
        DCB dcb;
        if (!GetCommState(m_handle, &dcb)) {
            std::cerr << "Error: could not get serial port settings." << std::endl;
            CloseHandle(m_handle);
            m_handle = INVALID_HANDLE_VALUE;
        }
        else {
            dcb.BaudRate = m_baudRate;
            dcb.ByteSize = 8;
            dcb.Parity = NOPARITY;
            dcb.StopBits = ONESTOPBIT;
            if (!SetCommState(m_handle, &dcb)) {
                std::cerr << "Error: could not set serial port settings." << std::endl;
                CloseHandle(m_handle);
                m_handle = INVALID_HANDLE_VALUE;
            }
            else {
                COMMTIMEOUTS timeouts;
                timeouts.ReadIntervalTimeout = 50;
                timeouts.ReadTotalTimeoutConstant = 50;
                timeouts.ReadTotalTimeoutMultiplier = 10;
                timeouts.WriteTotalTimeoutConstant = 50;
                timeouts.WriteTotalTimeoutMultiplier = 10;
                if (!SetCommTimeouts(m_handle, &timeouts)) {
                    std::cerr << "Error: could not set serial port timeouts." << std::endl;
                    CloseHandle(m_handle);
                    m_handle = INVALID_HANDLE_VALUE;
                }
            }
        }
    }
}

SerialPort::~SerialPort() {
    if (isConnected()) {
        CloseHandle(m_handle);
    }
}

bool SerialPort::isConnected() {
    return m_handle != INVALID_HANDLE_VALUE;
}

bool SerialPort::writeData(const char* data, int dataSize) {
    if (!isConnected()) {
        std::cerr << "Error: not connected to serial port." << std::endl;
        return false;
    }

    DWORD bytesWritten;
    bool success = WriteFile(m_handle, data, dataSize, &bytesWritten, NULL) == TRUE;

    if (!success) {
        std::cerr << "Error: could not write to serial port." << std::endl;
    }

    return success;
}

int SerialPort::readData(char* buffer, int bufferSize) {
    if (!isConnected()) {
        std::cerr << "Error: not connected to serial port." << std::endl;
        return -1;
    }

    DWORD bytesRead;
    bool success = ReadFile(m_handle, buffer, bufferSize, &bytesRead, NULL) == TRUE;

    if (!success) {
        std
    cerr << "Error: could not read from serial port." << std::endl;
    return -1;
}

return bytesRead;
}
