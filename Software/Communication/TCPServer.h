#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class TCPServer {
public:
    TCPServer(int port);

    void listenAndAccept();

    void receive();

    void send(const char* response);

    ~TCPServer();

private:
    int port;
    int listen_fd;
    int conn_fd;
    struct sockaddr_in serv_addr, client_addr;
    char buffer[1024];
};

#endif
