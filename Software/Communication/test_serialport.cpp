#include <iostream>
#include <cassert>
#include "SerialPort.h"

using namespace std;

void testSerialPort() {
    SerialPort port;

    // Test Open method
    assert(port.Open("/dev/ttyS0", 9600, 8, SerialPort::Parity::None, 1));
    assert(!port.Open("/dev/ttyS1", 115200, 7, SerialPort::Parity::Odd, 2)); // Invalid parameters

    // Test Read and Write methods
    const char* data = "Hello, world!";
    assert(port.Write(data, strlen(data)) == strlen(data));
    
    char buffer[256];
    int bytesRead = port.Read(buffer, 256);
    assert(bytesRead == strlen(data));
    assert(strcmp(buffer, data) == 0);

    port.Close();
}

int main() {
    testSerialPort();
    cout << "All tests passed." << endl;
    return 0;
}
