#include "RS232.h"
#include <iostream>

RS232::RS232(std::string portName, unsigned int baudRate) {
    connected = false;
    hComm = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hComm == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cerr << "ERROR: Serial port does not exist!" << std::endl;
        }
        else {
            std::cerr << "ERROR: Could not open serial port!" << std::endl;
        }
    }
    else {
        if (!GetCommState(hComm, &dcbSerialParams)) {
            std::cerr << "ERROR: Could not get serial port state!" << std::endl;
        }
        else {
            dcbSerialParams.BaudRate = baudRate;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;
            if (!SetCommState(hComm, &dcbSerialParams)) {
                std::cerr << "ERROR: Could not set serial port state!" << std::endl;
            }
            else {
                timeouts.ReadIntervalTimeout = 50;
                timeouts.ReadTotalTimeoutConstant = 50;
                timeouts.ReadTotalTimeoutMultiplier = 10;
                timeouts.WriteTotalTimeoutConstant = 50;
                timeouts.WriteTotalTimeoutMultiplier = 10;
                if (!SetCommTimeouts(hComm, &timeouts)) {
                    std::cerr << "ERROR: Could not set serial port timeouts!" << std::endl;
                }
                else {
                    connected = true;
                    PurgeComm(hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);
                }
            }
        }
    }
}

RS232::~RS232() {
    if (connected) {
        connected = false;
        CloseHandle(hComm);
    }
}

bool RS232::isConnected() {
    return connected;
}

bool RS232::openPort() {
    return connected;
}

void RS232::closePort() {
    if (connected) {
        connected = false;
        CloseHandle(hComm);
    }
}

bool RS232::writeData(char* buffer, unsigned int bufSize) {
    DWORD bytesSent;
    if (!WriteFile(hComm, (void*)buffer, bufSize, &bytesSent, 0)) {
        ClearCommError(hComm, NULL, NULL);
        return false;
    }
    else {
        return true;
    }
}

int RS232::readData(char* buffer, unsigned int bufSize) {
    DWORD bytesRead;
    unsigned int toRead = 0;

    if (!ClearCommError(hComm, NULL, NULL)) {
        return 0;
    }

    if (WaitForSingleObject(hComm, 50) == WAIT_OBJECT_0) {
        if (!ReadFile(hComm, buffer, bufSize, &bytesRead, NULL)) {
            return 0;
        }
        else {
            return bytesRead;
        }
    }
    else
    return 0;
}
