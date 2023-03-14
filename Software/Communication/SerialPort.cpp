#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <termios.h>
#endif

using namespace std;

// 定義串口通訊的參數
struct SerialPortParams {
    string portName; // 串口名稱，例如"/dev/ttyUSB0"或"COM1"
    int baudRate; // 波特率，例如9600、19200等等
    int dataBits; // 資料位元，通常為8
    int stopBits; // 停止位元，通常為1或2
    char parity; // 奇偶校驗，通常為'N'、'O'或'E'
};

// 定義串口通訊的類
class SerialPort {
public:
    SerialPort(const SerialPortParams& params) : portName_(params.portName), baudRate_(params.baudRate), dataBits_(params.dataBits), stopBits_(params.stopBits), parity_(params.parity) {}

    bool Open() {
#ifdef _WIN32
        // 在Windows上開啟串口
        portHandle_ = CreateFileA(portName_.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (portHandle_ == INVALID_HANDLE_VALUE) {
            cout << "Failed to open serial port: " << portName_ << endl;
            return false;
        }
        DCB dcb;
        dcb.DCBlength = sizeof(dcb);
        if (!GetCommState(portHandle_, &dcb)) {
            cout << "Failed to get serial port state." << endl;
            CloseHandle(portHandle_);
            return false;
        }
        dcb.BaudRate = baudRate_;
        dcb.ByteSize = dataBits_;
        dcb.StopBits = stopBits_;
        dcb.Parity = parity_;
        if (!SetCommState(portHandle_, &dcb)) {
            cout << "Failed to set serial port state." << endl;
            CloseHandle(portHandle_);
            return false;
        }
        COMMTIMEOUTS timeouts = { 0 };
        timeouts.ReadIntervalTimeout = 10;
        timeouts.ReadTotalTimeoutMultiplier = 10;
        timeouts.ReadTotalTimeoutConstant = 100;
        timeouts.WriteTotalTimeoutMultiplier = 10;
        timeouts.WriteTotalTimeoutConstant = 100;
        if (!SetCommTimeouts(portHandle_, &timeouts)) {
            cout << "Failed to set serial port timeouts." << endl;
            CloseHandle(portHandle_);
            return false;
        }
#else
        // 在Linux上開啟串口
        portHandle_ = open(portName_.c_str(), O_RDWR | O_NOCTTY);
        if (portHandle_ == -1) {
            cout << "Failed to open serial port: " << portName_ << endl;
            return false;
        }
        termios tty;
        memset(&tty, 0
    , sizeof(tty));
    if (tcgetattr(portHandle_, &tty) != 0) {
        cout << "Failed to get serial port state." << endl;
        close(portHandle_);
        return false;
    }
    cfsetospeed(&tty, baudRate_);
    cfsetispeed(&tty, baudRate_);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 5;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    if (parity_ == 'E') {
        tty.c_cflag |= PARENB;
    } else if (parity_ == 'O') {
        tty.c_cflag |= (PARENB | PARODD);
    }
    if (stopBits_ == 2) {
        tty.c_cflag |= CSTOPB;
    } else {
        tty.c_cflag &= ~CSTOPB;
    }
    if (tcsetattr(portHandle_, TCSANOW, &tty) != 0) {
        cout << "Failed to set serial port state." << endl;
        close(portHandle_);
        return false;
    }
#endif
return true;
}


void Close() {
#ifdef WIN32
CloseHandle(portHandle);
#else
close(portHandle_);
#endif
}


int Read(char* buffer, int length) {
#ifdef WIN32
DWORD bytesRead;
if (!ReadFile(portHandle, buffer, length, &bytesRead, NULL)) {
return -1;
}
return bytesRead;
#else
int bytesRead = 0;
while (bytesRead < length) {
int n = read(portHandle_, buffer + bytesRead, length - bytesRead);
if (n <= 0) {
return -1;
}
bytesRead += n;
}
return bytesRead;
#endif
}

int Write(const char* buffer, int length) {
#ifdef WIN32
DWORD bytesWritten;
if (!WriteFile(portHandle, buffer, length, &bytesWritten, NULL)) {
return -1;
}
return bytesWritten;
#else
int bytesWritten = 0;
while (bytesWritten < length) {
int n = write(portHandle_, buffer + bytesWritten, length - bytesWritten);
if (n <= 0) {
return -1;
}
bytesWritten += n;
}
return bytesWritten;
#endif
}

private:
string portName_;
int baudRate_;
int dataBits_;
int stopBits_;
char parity_;
#ifdef WIN32
HANDLE portHandle;
#else
int portHandle_;
#endif
};