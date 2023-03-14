#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "SerialPort.h"

using namespace std;

class RS232Communication {
public:
    RS232Communication() : m_isRunning(false) {}

    // Add a device to the communication list
    void AddDevice(const string& name, int baudRate, int dataBits, SerialPort::Parity parity, int stopBits) {
        m_devices.push_back(DeviceInfo(name, baudRate, dataBits, parity, stopBits));
    }

    // Start communication
    void Start() {
        m_isRunning = true;
        m_thread = thread(&RS232Communication::CommunicationThread, this);
    }

    // Stop communication
    void Stop() {
        m_isRunning = false;
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }

private:
    struct DeviceInfo {
        string name;
        int baudRate;
        int dataBits;
        SerialPort::Parity parity;
        int stopBits;

        DeviceInfo(const string& n, int br, int db, SerialPort::Parity p, int sb) :
            name(n), baudRate(br), dataBits(db), parity(p), stopBits(sb) {}
    };

    void CommunicationThread() {
        while (m_isRunning) {
            for (auto& device : m_devices) {
                lock_guard<mutex> lock(m_mutex);

                // Open the device
                SerialPort port;
                if (!port.Open(device.name, device.baudRate, device.dataBits, device.parity, device.stopBits)) {
                    continue;
                }

                // Read and write data
                const char* data = "Hello, world!";
                port.Write(data, strlen(data));
                char buffer[256];
                int bytesRead = port.Read(buffer, 256);
                if (bytesRead > 0) {
                    cout << "Device " << device.name << " received: " << buffer << endl;
                }

                // Close the device
                port.Close();
            }

            // Wait for a certain period of time before switching to the next device
            unique_lock<mutex> lock(m_mutex);
            m_cv.wait_for(lock, chrono::milliseconds(100));
        }
    }

    vector<DeviceInfo> m_devices;
    bool m_isRunning;
    thread m_thread;
    mutex m_mutex;
    condition_variable m_cv;
};

int main() {
    // Add two devices to the communication list
    RS232Communication communication;
    communication.AddDevice("/dev/ttyS0", 9600, 8, SerialPort::Parity::None, 1);
    communication.AddDevice("/dev/ttyS1", 115200, 7, SerialPort::Parity::Odd, 2);

    // Start communication
    communication.Start();

    // Wait for a certain period of time
    this_thread::sleep_for(chrono::seconds(10));

    // Stop communication
    communication.Stop();

    return 0;
}
