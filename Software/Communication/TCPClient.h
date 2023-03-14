#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class TCPClient {
public:
    TCPClient(const char* server_ip, int port);

    void connectServer();

    void send(const char* message);

    void receive();

    ~TCPClient();

private:
    const char* server_ip;
    int port;
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[1024];
};

#endif
