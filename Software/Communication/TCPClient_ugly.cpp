#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    int port = 8080;
    const char* server_ip = "127.0.0.1";

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize the address structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IP address from string to binary form
    inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);

    // Connect to the server
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Send a message to the server
    const char* message = "Hello, Server!";
    write(sockfd, message, strlen(message));

    // Receive a response from the server
    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer)-1);

    cout << "Received message from server: " << buffer << endl;

    // Close the socket
    close(sockfd);

    return 0;
}
