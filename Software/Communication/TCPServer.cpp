#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class TCPServer {
public:
    TCPServer(int port) : port(port) {
        listen_fd = socket(AF_INET, SOCK_STREAM, 0);

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(port);

        bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    }

    void listenAndAccept() {
        listen(listen_fd, 5);

        cout << "Server is listening on port " << port << endl;

        socklen_t client_addr_len = sizeof(client_addr);
        conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    }

    void receive() {
        memset(buffer, 0, sizeof(buffer));
        read(conn_fd, buffer, sizeof(buffer)-1);

        cout << "Received message from client: " << buffer << endl;
    }

    void send(const char* response) {
        write(conn_fd, response, strlen(response));
    }

    ~TCPServer() {
        close(conn_fd);
        close(listen_fd);
    }

private:
    int port;
    int listen_fd;
    int conn_fd;
    struct sockaddr_in serv_addr, client_addr;
    char buffer[1024];
};
