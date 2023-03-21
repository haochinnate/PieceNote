#include <Windows.h>
#include <mutex>

class RS232 {
public:
    RS232(const char* portName, DWORD baudRate) : baudRate(baudRate) {
        hComm = CreateFileA(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hComm == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Unable to open port");
        }
        setupSerialPort();
    }

    ~RS232() {
        CloseHandle(hComm);
    }

    void writeData(const char* dataToSend) {
        std::lock_guard<std::mutex> lock(mtx);
        DWORD bytesWritten = 0;
        WriteFile(hComm, dataToSend, strlen(dataToSend), &bytesWritten, NULL);
        FlushFileBuffers(hComm);
    }

    void readData(char* receivedData, DWORD bufferSize) {
        std::lock_guard<std::mutex> lock(mtx);
        DWORD bytesRead = 0;
        ReadFile(hComm, receivedData, bufferSize, &bytesRead, NULL);
        receivedData[bytesRead] = '\0';
    }

private:
    HANDLE hComm;
    DWORD baudRate;
    std::mutex mtx;

    void setupSerialPort() {
        DCB dcbSerialParams = { 0 };
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

        if (!GetCommState(hComm, &dcbSerialParams)) {
            throw std::runtime_error("Error getting serial port state");
        }

        dcbSerialParams.BaudRate = baudRate;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = NOPARITY;

        if (!SetCommState(hComm, &dcbSerialParams)) {
            throw std::runtime_error("Error setting serial port state");
        }

        COMMTIMEOUTS timeouts = { 0 };
        timeouts.ReadIntervalTimeout = 50;
        timeouts.ReadTotalTimeoutConstant = 50;
        timeouts.ReadTotalTimeoutMultiplier = 10;
        timeouts.WriteTotalTimeoutConstant = 50;
        timeouts.WriteTotalTimeoutMultiplier = 10;

        if (!SetCommTimeouts(hComm, &timeouts)) {
            throw std::runtime_error("Error setting serial port timeouts");
        }
    }
};

////////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include <mutex>
#include <condition_variable>

class RS232 {
public:
    RS232(const char* portName, DWORD baudRate) : baudRate(baudRate) {
        hComm = CreateFileA(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hComm == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Unable to open port");
        }
        setupSerialPort();
    }

    ~RS232() {
        CloseHandle(hComm);
    }

    void writeData(const char* dataToSend) {
        std::unique_lock<std::mutex> lock(mtx);
        DWORD bytesWritten = 0;
        WriteFile(hComm, dataToSend, strlen(dataToSend), &bytesWritten, NULL);
        FlushFileBuffers(hComm);
        cv.notify_one();
    }

    void readData(char* receivedData, DWORD bufferSize) {
        std::unique_lock<std::mutex> lock(mtx);
        DWORD bytesRead = 0;
        ReadFile(hComm, receivedData, bufferSize, &bytesRead, NULL);
        receivedData[bytesRead] = '\0';
        cv.wait(lock);
    }

private:
    HANDLE hComm;
    DWORD baudRate;
    std::mutex mtx;
    std::condition_variable cv;

    void setupSerialPort() {
        DCB dcbSerialParams = { 0 };
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

        if (!GetCommState(hComm, &dcbSerialParams)) {
            throw std::runtime_error("Error getting serial port state");
        }

        dcbSerialParams.BaudRate = baudRate;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = NOPARITY;

        if (!SetCommState(hComm, &dcbSerialParams)) {
            throw std::runtime_error("Error setting serial port state");
        }

        COMMTIMEOUTS timeouts = { 0 };
        timeouts.ReadIntervalTimeout = 50;
        timeouts.ReadTotalTimeoutConstant = 50;
        timeouts.ReadTotalTimeoutMultiplier = 10;
        timeouts.WriteTotalTimeoutConstant = 50;
        timeouts.WriteTotalTimeoutMultiplier = 10;

        if (!SetCommTimeouts(hComm, &timeouts)) {
            throw std::runtime_error("Error setting serial port timeouts");
        }
    }
};
