#ifndef RS232COMMUNICATION_H
#define RS232COMMUNICATION_H

#include <vector>
#include <mutex>
#include <thread>
#include "SerialPort.h"

class RS232Communication {
public:
    explicit RS232Communication(const std::vector<std::string>& portNames);
    virtual ~RS232Communication();

    bool start();
    void stop();

private:
    void run();
    void readFromPort(SerialPort& port);
    void writeToPort(SerialPort& port);

    std::vector<SerialPort> ports_;
    std::vector<std::thread> threads_;
    std::vector<std::mutex> mutexes_;
    bool isRunning_;
};

#endif // RS232COMMUNICATION_H
