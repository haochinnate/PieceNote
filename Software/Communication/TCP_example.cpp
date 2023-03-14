int main(int argc, char *argv[]) {
    int port = 8080;
    TCPServer server(port);

    server.listenAndAccept();
    server.receive();

    const char* response = "Hello, Client!";
    server.send(response);

    return 0;
}

int main(int argc, char *argv[]) {
    int port = 8080;
    const char* server_ip = "127.0.0.1";
    TCPClient client(server_ip, port);

    client.connectServer();

    const char* message = "Hello, Server!";
    client.send(message);
    client.receive();

    return 0;
}
