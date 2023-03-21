#include "catch.hpp"
#include "RS232.h"
#include "SerialPort.h"

TEST_CASE("RS232 Test", "[RS232]") {
    RS232 rs232("COM1", 9600);
    REQUIRE(rs232.isConnected() == true);

    char writeBuffer[] = "Hello RS232!";
    rs232.writeData(writeBuffer, sizeof(writeBuffer));

    char readBuffer[256];
    int bytesRead = rs232.readData(readBuffer, sizeof(readBuffer));
    REQUIRE(bytesRead > 0);
    REQUIRE(std::string(readBuffer).substr(0, bytesRead) == std::string(writeBuffer));
}

TEST_CASE("SerialPort Test", "[SerialPort]") {
    SerialPort serial("COM2", 9600);
    REQUIRE(serial.isConnected() == true);

    char writeBuffer[] = "Hello Serial Port!";
    serial.writeData(writeBuffer, sizeof(writeBuffer));

    char readBuffer[256];
    int bytesRead = serial.readData(readBuffer, sizeof(readBuffer));
    REQUIRE(bytesRead > 0);
    REQUIRE(std::string(readBuffer).substr(0, bytesRead) == std::string(writeBuffer));
}
