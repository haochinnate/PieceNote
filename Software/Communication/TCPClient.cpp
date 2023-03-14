#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class TCPClient {
public:
    TCPClient(const char* server_ip, int port) : server_ip(server_ip), port(port) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);
    }

    void connectServer() {
        connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    }

    void send(const char* message) {
        write(sockfd, message, strlen(message));
    }

    void receive() {
        memset(buffer, 0, sizeof(buffer));
        read(sockfd, buffer, sizeof(buffer)-1);

        cout << "Received message from server: " << buffer << endl;
    }

    ~TCPClient() {
        close(sockfd);
    }

private:
    const char* server_ip;
    int port;
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[1024];
};
