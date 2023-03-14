#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    int listen_fd, conn_fd;
    struct sockaddr_in serv_addr, client_addr;
    char buffer[1024];
    int port = 8080;

    // Create a socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize the address structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    // Bind the socket to the specified address and port
    bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Listen for incoming connections
    listen(listen_fd, 5);

    cout << "Server is listening on port " << port << endl;

    // Accept incoming connections
    socklen_t client_addr_len = sizeof(client_addr);
    conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);

    // Receive data from the client
    memset(buffer, 0, sizeof(buffer));
    read(conn_fd, buffer, sizeof(buffer)-1);

    cout << "Received message from client: " << buffer << endl;

    // Send a response back to the client
    const char* response = "Hello, Client!";
    write(conn_fd, response, strlen(response));

    // Close the connection
    close(conn_fd);

    return 0;
}
