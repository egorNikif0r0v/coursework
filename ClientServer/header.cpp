#include "header.h"

//...
void Connection::SetPort(uint16_t port) {
    this->port = port;
}
uint16_t Connection::GetPort() {
    return this->port;
}
int8_t Connection::GetStatus() {
    return this->status_;
}
int Connection::Socket(int domain, int type, int protocol) {
    int status = socket(domain, type, protocol);
    if (status == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return status;
}
//...


//...
Client::Client(char* adress) {
    this->adress = adress;
}
void Client::Connect() {}
void Client::Reconnect() {}
void Client::Disconnect() {}
//...


//...
Server::Server(int8_t count_client) {
    this->count_client = count_client;
}
void Server::Start() {}
void Server::Restart() {}
void Server::Stop() {}
//...


/*
int Socket(int domain, int type, int protocol) {
    int status = socket(domain, type, protocol);
    if (status == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return status;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int status = bind(sockfd, addr, addrlen);
    if (status == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog) {
    int status = listen(sockfd, backlog);
    if (status == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int status = accept(sockfd, addr, addrlen);
    if (status == -1) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return status;
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int status = connect(sockfd, addr, addrlen);
    if (status == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst) {
    int status = inet_pton(af, src, dst);
    if (status == 0) {
        printf("inet_pton failed: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family\n");
        exit(EXIT_FAILURE);
    }
    if (status == -1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}
*/
