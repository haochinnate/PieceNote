// socket.h
#include <WinSock2.h>
#include <iostream>
#include <string>
#pragma comment(lib,"Ws2_32.lib")

class Socket {
public:
    Socket();
    virtual ~Socket();
    bool bind(unsigned short port);
    bool listen(int backlog = SOMAXCONN);
    bool accept(Socket& clientSock, std::string& clientIP);
    bool connect(const std::string& serverIP, unsigned short port);
    int recv(std::string& msg);
    int send(const std::string& msg);
    void close();
protected:
    SOCKET _sockfd;
};

class Server : public Socket {
public:
    Server() = default;
    bool select(const std::string& clientIP);
    bool isClientConnected(const std::string& clientIP);
};

class Client : public Socket {
public:
    Client() = default;
};

// socket.cpp
Socket::Socket() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Socket::~Socket() {
    closesocket(_sockfd);
    WSACleanup();
}

bool Socket::bind(unsigned short port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    return (::bind(_sockfd, (SOCKADDR*)&addr, sizeof(addr)) != SOCKET_ERROR);
}

bool Socket::listen(int backlog) {
    return (::listen(_sockfd, backlog) != SOCKET_ERROR);
}

bool Socket::accept(Socket& clientSock, std::string& clientIP) {
    sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);
    SOCKET clientfd = ::accept(_sockfd, (SOCKADDR*)&clientAddr, &addrLen);
    if (clientfd == INVALID_SOCKET) {
        return false;
    }
    clientSock._sockfd = clientfd;
    clientIP = inet_ntoa(clientAddr.sin_addr);
    return true;
}

bool Socket::connect(const std::string& serverIP, unsigned short port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = inet_addr(serverIP.c_str());
    return (::connect(_sockfd, (SOCKADDR*)&addr, sizeof(addr)) != SOCKET_ERROR);
}

int Socket::recv(std::string& msg) {
    char buf[1024];
    int len = ::recv(_sockfd, buf, sizeof(buf), 0);
if (len <= 0) {
    return len;
}
msg.assign(buf, len);
return len;
}

int Socket::send(const std::string& msg) {
return ::send(_sockfd, msg.c_str(), msg.size(), 0);
}

void Socket::close() {
closesocket(_sockfd);
}

bool Server::select(const std::string& clientIP) {
fd_set fds;
FD_ZERO(&fds);
FD_SET(_sockfd, &fds);
timeval timeout = { 0, 0 };
int ret = select(0, &fds, nullptr, nullptr, &timeout);
if (ret == SOCKET_ERROR) {
return false;
}
if (ret == 0) {
return false;
}
sockaddr_in clientAddr;
int addrLen = sizeof(clientAddr);
SOCKET clientfd = ::accept(_sockfd, (SOCKADDR*)&clientAddr, &addrLen);
if (clientfd == INVALID_SOCKET) {
return false;
}
if (inet_ntoa(clientAddr.sin_addr) == clientIP) {
_sockfd = clientfd;
return true;
}
closesocket(clientfd);
return false;
}

bool Server::isClientConnected(const std::string& clientIP) {
fd_set fds;
FD_ZERO(&fds);
FD_SET(_sockfd, &fds);
timeval timeout = { 0, 0 };
int ret = select(0, nullptr, &fds, nullptr, &timeout);
if (ret == SOCKET_ERROR) {
return false;
}
if (ret == 0) {
return false;
}
sockaddr_in clientAddr;
int addrLen = sizeof(clientAddr);
SOCKET clientfd = ::accept(_sockfd, (SOCKADDR*)&clientAddr, &addrLen);
if (clientfd == INVALID_SOCKET) {
return false;
}
if (inet_ntoa(clientAddr.sin_addr) == clientIP) {
closesocket(clientfd);
return true;
}
closesocket(clientfd);
return false;
}


// 在 `main.cpp` 使用範例中，我們示範了如何使用 `Socket`、`Server` 與 `Client` 類別，建立一個簡單的 Server-Client 應用程式。

// ```c++
// main.cpp
#include "socket.h"
#include <iostream>

int main() {
    // 建立 Server
    Server server;
    server.bind(8080);
    server.listen();

    // 等待 Client 連接
    std::cout << "Waiting for client..." << std::endl;
    std::string clientIP;
    Client client;
    server.accept(client, clientIP);
    std::cout << "Client connected from " << clientIP << std::endl;

    // Server 發送訊息給 Client
    std::string msg = "Hello from server!";
    server.send(msg);

    // Client 接收 Server 的訊息
    std::string recvMsg;
    client.recv(recvMsg);
    std::cout << "Received message from server: " << recvMsg << std::endl;

    // 關閉 Socket
    server.close();
    client.close();

    return 0;
}



// test.cpp
#include "socket.h"
#include <gtest/gtest.h>

TEST(SocketTest, BindTest) {
    Socket socket;
    EXPECT_TRUE(socket.bind(8080));
    EXPECT_FALSE(socket.bind(8080)); // 端口被占用，綁定失敗
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// main.cpp
#include <iostream>
#include "socket.h"
#include "server.h"

int main() {
    SocketLib::Server server;
    server.start(8080, [](SocketLib::Socket client) {
        while (true) {
            std::string message = client.recv();
            if (message.empty()) {
                break;
            }
            client.send(message);
        }
    });
    return 0;
}

// main.cpp
#include <iostream>
#include "socket.h"
#include "client.h"

int main() {
    SocketLib::Client client;
    client.connect("127.0.0.1", 8080);
    client.send("Hello, world!");
    std::string message = client.recv();
    std::cout << message << std::endl; // 輸出 "Hello, world!"
    return 0;
}
