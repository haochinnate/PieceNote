#include "SerialPort.h"
#include <iostream>

SerialPort::SerialPort(std::string portName) {
    connected = false;
    hSerial = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cerr << "ERROR: Serial port does not exist!" << std::endl;
        }
        else {
            std::cerr << "ERROR: Could not open serial port!" << std::endl;
        }
    }
    else {
        DCB dcbSerialParams = { 0 };
        if (!GetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "ERROR: Could not get serial port state!" << std::endl;
        }
        else {
            dcbSerialParams.BaudRate = CBR_9600;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;
            if (!SetCommState(hSerial, &dcbSerialParams)) {
                std::cerr << "ERROR: Could not set serial port state!" << std::endl;
            }
            else {
                connected = true;
                PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}

SerialPort::~SerialPort() {
    if (connected) {
        connected = false;
        CloseHandle(hSerial);
    }
}

bool SerialPort::isConnected() {
    return connected;
}

bool SerialPort::openPort() {
    return connected;
}

void SerialPort::closePort() {
    if (connected) {
        connected = false;
        CloseHandle(hSerial);
    }
}

bool SerialPort::writeData(char* buffer, unsigned int bufSize) {
    DWORD bytesSent;
    if (!WriteFile(hSerial, (void*)buffer, bufSize, &bytesSent, 0)) {
        ClearCommError(hSerial, &errors, &status);
        return false;
    }
    else {
        return true;
    }
}

int SerialPort::readData(char* buffer, unsigned int bufSize) {
    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(hSerial, &errors, &status);
    if (status.cbInQue > 0) {
        if (status.cbInQue > bufSize) {
            toRead = bufSize;
        }
        else {
            toRead = status.cbInQue;
        }
    }

    if (ReadFile(hSerial, buffer, toRead, &bytesRead, NULL)) {
        return bytesRead;
    }
    else {
        return 0;
    }
}

// another code
#include "SerialPort.h"
#include <iostream>

SerialPort::SerialPort(std::string portName, unsigned int baudRate) {
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

SerialPort::~SerialPort() {
    if (connected) {
        connected = false;
        CloseHandle(hComm);
    }
}

bool SerialPort::isConnected() {
    return connected;
}

bool SerialPort::openPort() {
    return connected;
}

void SerialPort::closePort() {
    if (connected) {
        connected = false;
        CloseHandle(hComm);
    }
}

bool SerialPort::writeData(char* buffer, unsigned int bufSize) {
    DWORD bytesSent;
    if (!WriteFile(hComm, (void*)buffer, bufSize, &bytesSent, 0)) {
        ClearCommError(hComm, NULL, NULL);
        return false;
    }
    else {
        return true;
    }
}

int SerialPort::readData(char* buffer, unsigned int bufSize) {
    DWORD bytesRead;
    unsigned int toRead = 0;

    if (!ClearCommError(hComm, NULL, NULL)) {
        return 0;
    }

    if (WaitForSingleObject(hComm, 50) == WAIT_OBJECT_0) {

    if (PeekNamedPipe(hComm, NULL, 0, NULL, &toRead, NULL)) {
        if (toRead > 0) {
            if (ReadFile(hComm, buffer, bufSize, &bytesRead, NULL)) {
                return bytesRead;
            }
        }
    }
}
return 0;
}