int main() {
SerialPortParams params;
params.portName = "/dev/ttyUSB0"; // 請更改為您的串口名稱
params.baudRate = 9600; // 請更改為您的波特率
params.dataBits = 8; // 請更改為您的資料位元
params.stopBits = 1; // 請更改為您的停止位元
params.parity = 'N'; // 請更改為
SerialPort port;
if (!port.Open(params)) {
    cout << "Failed to open serial port." << endl;
    return 1;
}

char buffer[256];
int bytesRead = port.Read(buffer, 256);
if (bytesRead < 0) {
    cout << "Failed to read from serial port." << endl;
    port.Close();
    return 1;
}

int bytesWritten = port.Write(buffer, bytesRead);
if (bytesWritten < 0) {
    cout << "Failed to write to serial port." << endl;
    port.Close();
    return 1;
}

port.Close();
return 0;
}