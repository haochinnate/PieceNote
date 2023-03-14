#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>

class SerialPort {
public:
    explicit SerialPort(const std::string& portName);
    virtual ~SerialPort();

    bool isOpen() const;
    bool open();
    void close();
    int read(char* buffer, int size);
    int write(const char* data, int size);

private:
    std::string portName_;
    int fd_;
    bool isOpen_;
};

#endif // SERIALPORT_H
