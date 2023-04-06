// TcpSocket.hpp

#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include <string>

namespace TcpSocket {
    class Server {
public:
    Server(int port);
    ~Server();
    bool start();
    void stop();
    void send(int client_id, const std::string& message);
    std::string receive(int client_id);

private:
    int m_port;
    int m_server_socket;
    bool m_running;
};

class Client {
public:
    Client(const std::string& address, int port);
    ~Client();
    bool connect();
    void disconnect();
    void send(const std::string& message);
    std::string receive();

private:
    std::string m_address;
    int m_port;
    int m_socket;
    bool m_connected;
};
}

#endif // TCPSOCKET_HPP

// TcpSocket.cpp

#include "TcpSocket.hpp"
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

namespace TcpSocket {

Server::Server(int port) : m_port(port), m_server_socket(0), m_running(false) {}

Server::~Server() {
    stop();
}

bool Server::start() {
    if (m_running) {
        return true;
    }
    m_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_socket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return false;
    }
    int opt = 1;
    if (setsockopt(m_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Failed to set socket options." << std::endl;
        return false;
    }
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(m_port);
    if (bind(m_server_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Failed to bind to port " << m_port << "." << std::endl;
        return false;
    }
    if (listen(m_server_socket, 5) == -1) {
        std::cerr << "Failed to listen on socket." << std::endl;
        return false;
    }
    m_running = true;
    return true;
}

void Server::stop() {
    if (m_running) {
        close(m_server_socket);
        m_running = false;
    }
}

void Server::send(int client_id, const std::string& message) {
    std::stringstream ss;
    ss << "Client " << client_id << ": " << message << std::endl;
    std::string message_str = ss.str();
    write(client_id, message_str.c_str(), message_str.length());
}

std::string Server::receive(int client_id) {
    char buffer[4096] = {0};
    int valread = read(client_id, buffer, 
4096);
if (valread == -1) {
std::cerr << "Failed to receive data from client." << std::endl;
return "";
} else if (valread == 0) {
std::cerr << "Client disconnected." << std::endl;
return "";
} else {
std::string message_str(buffer, valread);
std::stringstream ss;
ss << "Client " << client_id << ": " << message_str << std::endl;
return ss.str();
}
}

Client::Client(const std::string& address, int port) : m_address(address), m_port(port), m_socket(0), m_connected(false) {}

Client::~Client() {
    disconnect();
}

bool Client::connect() {
    if (m_connected) {
        return true;
    }
    struct hostent *he;
    if ((he = gethostbyname(m_address.c_str())) == nullptr) {
        std::cerr << "Failed to resolve host." << std::endl;
        return false;
    }
    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr = *((struct in_addr *)he->h_addr);
    server_address.sin_port = htons(m_port);
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return false;
    }
    if (::connect(m_socket, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Failed to connect to server." << std::endl;
        return false;
    }
    m_connected = true;
    return true;
}

void Client::disconnect() {
    if (m_connected) {
        close(m_socket);
        m_connected = false;
    }
}

void Client::send(const std::string& message) {
    write(m_socket, message.c_str(), message.length());
}

std::string Client::receive() {
    char buffer[4096] = {0};
    int valread = read(m_socket, buffer, 4096);
    if (valread == -1) {
        std::cerr << "Failed to receive data from server." << std::endl;
        return "";
    } else if (valread == 0) {
        std::cerr << "Server disconnected." << std::endl;
        return "";
    } else {
        std::string message_str(buffer, valread);
        return message_str;
    }
}
}

// TcpSocketTest.cpp

#include "TcpSocket.hpp"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

using namespace TcpSocket;

TEST(TcpSocketTest, ServerTest) {
Server server(12345);
ASSERT_TRUE(server.start());
std::thread client_thread([&]() {
    Client client("localhost", 12345);
    ASSERT_TRUE(client.connect());
    client.send("Hello, server!");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    client.disconnect();
});

int client_id = -1;
std::string message = "";
while (message.empty()) {
    client_id = accept(server.m_server_socket, nullptr, nullptr);
    message = server.receive(client_id);
}
EXPECT_EQ("Client 5: Hello, server!\n", message);

server.send(client_id, "Hello, client!");
std::this_thread::sleep_for(std::chrono::milliseconds(100));
server.stop();
client_thread.join();
}

TEST(TcpSocketTest, ClientTest) {
Server server(12345);
ASSERT_TRUE(server.start());

std::thread server_thread([&]() {
    int client_id = accept(server.m_server_socket, nullptr, nullptr);
    server.send(client_id, "Hello, client!");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    server.disconnect(client_id);
    server.stop();
});

std::this_thread::sleep_for(std::chrono::milliseconds(100));

Client client("localhost", 12345);
ASSERT_TRUE(client.connect());
std::string message = client.receive();
EXPECT_EQ("Hello, client!", message);
client.disconnect();
server_thread.join();
}

int main(int argc, char **argv) {
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}

// main.cpp

#include "TcpSocket.hpp"
#include <iostream>

using namespace TcpSocket;

int main() {
// Create server on port 12345
Server server(12345);
if (!server.start()) {
std::cerr << "Failed to start server." << std::endl;
return 1;
}

// Accept connections and handle client messages
while (true) {
    int client_id = accept(server.m_server_socket, nullptr, nullptr);
    std::string message = server.receive(client_id);
    std::cout << message;
    server.send(client_id, "Message received.");
    server.disconnect(client_id);
}

}

// TcpSocket.hpp

#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include <string>

namespace TcpSocket {
    class Server {
public:
    Server(int port);
    ~Server();
    bool start();
    void stop();
    void send(int client_id, const std::string& message);
    std::string receive(int client_id);

private:
    int m_port;
    int m_server_socket;
    bool m_listening;
};

class Client {
public:
    Client(const std::string& address, int port);
    ~Client();
    bool connect();
    void disconnect();
    void send(const std::string& message);
    std::string receive();

private:
    std::string m_address;
    int m_port;
    int m_socket;
    bool m_connected;
};

}

#endif // TCPSOCKET_HPP

// TcpSocket.cpp

#include "TcpSocket.hpp"
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace TcpSocket {
    // Server implementation

Server::Server(int port) :
    m_port(port), m_server_socket(-1), m_listening(false) {}

Server::~Server() {
    stop();
}

bool Server::start() {
    // Create socket
    m_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_socket == -1) {
        return false;
    }

    // Set socket options
    int option = 1;
    setsockopt(m_server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    fcntl(m_server_socket, F_SETFL, O_NONBLOCK);

    // Bind socket to port
    sockaddr_in server_address;
    std::memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(m_port);
    if (bind(m_server_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        return false;
    }

    // Listen for incoming connections
    if (listen(m_server_socket, SOMAXCONN) == -1) {
        return false;
    }

    m_listening = true;
    return true;
}

void Server::stop() {
    if (m_server_socket != -1) {
        close(m_server_socket);
        m_server_socket = -1;
    }
    m_listening = false;
}

void Server::send(int client_id, const std::string& message) {
    write(client_id, message.c_str(), message.length());
}

std::string Server::receive(int client_id) {
    std::string buffer;
    char data[1024];
    ssize_t bytes_received;
    do {
        bytes_received = recv(client_id, data, sizeof(data), 0);
        if (bytes_received > 0) {
            buffer.append(data, bytes_received);
        }
    } while (bytes_received == sizeof(data));
    return buffer;
}

void Server::disconnect(int client_id) {
    close(client_id);
}

// Client implementation

Client::Client(const std::string& address, int port) :
    m_address(address), m_port(port), m_socket(-1), m_connected(false) {}

Client::~Client() {
    disconnect();
}

bool Client::connect() {
    // Get server address
    addrinfo hints, *server_info;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(m_address.c_str(), std::to_string(m_port).c_str(), &hints, &server_info) != 0) {
        return false;
    }

    // Create socket
    m_socket = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
    if (m_socket == -1) {
        return false;
    }

    // Connect to server
    if (::connect(m_socket, server_info->ai_addr, server_info->ai_addrlen) == -1) {
        return false;
    }

    m_connected = true;
    freeaddrinfo(server_info);
    return true;
}

void Client::disconnect() {
    if (m_socket != -1) {
        close(m_socket);
       
        m_socket = -1;
    }
    m_connected = false;
}

void Client::send(const std::string& message) {
    write(m_socket, message.c_str(), message.length());
}

std::string Client::receive() {
    std::string buffer;
    char data[1024];
    ssize_t bytes_received;
    do {
        bytes_received = recv(m_socket, data, sizeof(data), 0);
        if (bytes_received > 0) {
            buffer.append(data, bytes_received);
        }
    } while (bytes_received == sizeof(data));
    return buffer;
}

// Exported class implementation

TcpSocket::TcpSocket(int port) :
    m_server(port), m_client(nullptr) {}

TcpSocket::TcpSocket(const std::string& address, int port) :
    m_server(0), m_client(new Client(address, port)) {}

TcpSocket::~TcpSocket() {
    if (m_client != nullptr) {
        delete m_client;
    }
}

bool TcpSocket::start() {
    return m_server.start();
}

void TcpSocket::stop() {
    m_server.stop();
}

void TcpSocket::send(const std::string& message) {
    if (m_client != nullptr && m_client->is_connected()) {
        m_client->send(message);
    }
}

std::string TcpSocket::receive() {
    if (m_client != nullptr && m_client->is_connected()) {
        return m_client->receive();
    }
    return std::string();
}

bool TcpSocket::is_listening() const {
    return m_server.is_listening();
}

bool TcpSocket::is_connected() const {
    return m_client != nullptr && m_client->is_connected();
}

void TcpSocket::disconnect() {
    if (m_client != nullptr) {
        m_client->disconnect();
    }
}

int TcpSocket::accept() {
    return m_server.accept();
}

} // namespace TcpSocket

// TcpSocket.hpp

#ifndef TCP_SOCKET_HPP
#define TCP_SOCKET_HPP

#include <string>

namespace TcpSocket {

class Server {
public:
    Server(int port);
    ~Server();
    bool start();
    void stop();
    void send(int client_id, const std::string& message);
    std::string receive(int client_id);
    void disconnect(int client_id);
    int accept() { return ::accept(m_server_socket, nullptr, nullptr); }
    bool is_listening() const { return m_listening; }
private:
    int m_port;
    int m_server_socket;
    bool m_listening;
};

class Client {
public:
    Client(const std::string& address, int port);
    ~Client();
    bool connect();
    void disconnect();
    void send(const std::string& message);
    std::string receive();
    bool is_connected() const { return m_connected; }
private:
    std::string m_address;
    int m_port;
    int m_socket;
    bool m_connected;
};

class TcpSocket {
public:
    TcpSocket(int port);
    TcpSocket(const std::string& address, int port);
    ~TcpSocket();
    bool start();
    void stop();
    void send(const std::string& message);
    std::string receive();
    bool is_listening() const;
    bool is_connected() const;
    void disconnect();
    int accept();
private:
    Server m_server;
    Client* m_client;
};
} // namespace TcpSocket

#endif // TCP_SOCKET_HPP

// main.cpp

#include "TcpSocket.hpp"
#include <iostream>

int main() {
TcpSocket::TcpSocket

// Create server
TcpSocket::TcpSocket server(12345);
if (!server.start()) {
    std::cerr << "Failed to start server." << std::endl;
    return 1;
}
std::cout << "Server started on port " << 12345 << "." << std::endl;

// Accept connections
std::cout << "Waiting for connections..." << std::endl;
while (server.is_listening()) {
    int client_socket = server.accept();
    if (client_socket == -1) {
        std::cerr << "Error accepting connection." << std::endl;
        continue;
    }
    std::cout << "Accepted connection from client " << client_socket << "." << std::endl;

    // Receive messages from client
    bool connected = true;
    while (connected) {
        std::string message = server.receive(client_socket);
        if (!message.empty()) {
            std::cout << "Received message from client " << client_socket << ": " << message << std::endl;
            // Echo message back to client
            server.send(client_socket, message);
        } else {
            // Client has disconnected
            std::cout << "Client " << client_socket << " has disconnected." << std::endl;
            server.disconnect(client_socket);
            connected = false;
        }
    }
}

server.stop();

return 0;
}

// test.cpp

#include "TcpSocket.hpp"
#include <gtest/gtest.h>

TEST(TcpSocketTest, ServerStartStop) {
TcpSocket::TcpSocket server(12345);
ASSERT_TRUE(server.start());
server.stop();
ASSERT_FALSE(server.is_listening());
}

TEST(TcpSocketTest, ClientConnectDisconnect) {
TcpSocket::TcpSocket server(12345);
ASSERT_TRUE(server.start());
TcpSocket::TcpSocket client("localhost", 12345);
ASSERT_TRUE(client.is_connected());

client.disconnect();
ASSERT_FALSE(client.is_connected());

server.stop();
}

int main(int argc, char** argv) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}

// example.cpp

#include "TcpSocket.hpp"
#include <iostream>
#include <thread>

void client_thread() {
// Connect to server
TcpSocket::TcpSocket client("localhost", 12345);
if (!client.is_connected()) {
std::cerr << "Failed to connect to server." << std::endl;
return;
}

// Send message to server
std::string message = "Hello from client!";
client.send(message);

// Receive message from server
message = client.receive();
std::cout << "Received message from server: " << message << std::endl;

// Disconnect from server
client.disconnect();

}

int main() {
// Start server
std::thread server_thread(server_thread);

// Wait for server to start
std::this_thread::sleep_for(std::chrono::seconds(1));

// Start client
std::thread client_thread(client_thread);

// Wait for client to finish
client_thread.join();

// Stop server
server_thread.join();

return 0;

}


