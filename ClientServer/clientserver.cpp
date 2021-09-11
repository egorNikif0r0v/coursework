#include "header/clientserver.h"

//...
void Connection::SetPort(uint16_t port) {
    this->port = port;
}
uint16_t Connection::GetPort() {
    return this->port;
}

void Connection::Socket(int domain, int type, int protocol) {
    this->socket_ = socket(domain, type, protocol);
    if(this->socket_ == -1) {
        perror("socket :: fail\n");
        exit(EXIT_FAILURE);
    } else {
        perror("socket :");
    }
}
int Connection::GetSocket() {
    return socket_;
}

int Connection::GetBufferSize() {
    return buffer_size;
}
void Connection::SetBufferSize(int buffer_size) {
    this->buffer_size = buffer_size;
}

int Connection::Read(int user, char* buffer, int buffer_size) {
    int nread = read(user, buffer, buffer_size);
    if(nread == -1) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }
    return nread;
}
void Connection::Write(int user, char* buffer, int nread) {
    write(user, buffer, nread);
}
//...


//...
Client::Client() {
    this->adress = "127.0.0.1";
    this->name_client = "non";
}
Client::Client(char* name_client, char* adress){
    this->adress = adress;
    this->name_client = name_client;
}
Client::Client(char* name_client, char* adress, uint16_t port) : Client(name_client, adress){
    this->port = port;
}

char* Client::GetNameClient() {
    return name_client;
}

void Client::Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    uint8_t status = connect(sockfd, addr, addrlen);
    if(status == -1) {
        perror("connect fail");
        exit(EXIT_FAILURE);
    }else {
        perror("connect :");
    }
}
void Client::Inet_pton(int af, const char *src, void *dst) {
uint8_t status = inet_pton(af, src, dst);
    if(status == 0) {
        printf("inet_pton :: fail: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family");
        exit(EXIT_FAILURE);
    } else if(status == -1) {
        perror("inet_pton :: fail");
        exit(EXIT_FAILURE);
    } else {
        perror("inet_pton :");
    }
}

void Client::Connect() {
    Connection::Socket(AF_INET, SOCK_STREAM, 0);

    this->adr.sin_family = AF_INET;
    this->adr.sin_port = htons(this->port);

    Client::Inet_pton(AF_INET, this->adress, &this->adr.sin_addr);
    Client::Connect(socket_, (struct sockaddr *) &this->adr, sizeof adr);
}
void Client::Reconnect() {
    close(socket_);
    Client::Connect();
}
void Client::Disconnect() {
    close(socket_);
}
//...


//...
Server::Server() {
    this->count_client = 1;
    this->name_server = "non";
}
Server::Server(char* name_server, int8_t count_client) {
    this->count_client = count_client;
    this->name_server = name_server;
}
Server::Server(char* name_server, int8_t count_client, uint16_t port) : Server(name_server, count_client) {
    this->port = port;
}

char* Server::GetNameServer() {
    return this->name_server;
}

void Server::Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    uint8_t status = bind(sockfd, addr, addrlen);
    if (status == -1) {
        perror("bind :: failed\n");
        exit(EXIT_FAILURE);
    }else {
        perror("bind :");
    }
}
void Server::Listen(int sockfd, int backlog) {
    uint8_t status = listen(sockfd, backlog);
    if (status == -1) {
        perror("listen :: fail\n");
        exit(EXIT_FAILURE);
    }else {
        perror("listen :");
    }
}
int Server::Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    this->accept_ = accept(sockfd, addr, addrlen);
    if (this->accept_ == -1) {
        perror("accept :: fail");
        exit(EXIT_FAILURE);
    }else {
        perror("accept :");
    }
    return this->accept_;
}

int Server::GetAccept() {
    return this->accept_;
}

void Server::Start() {
    Socket(AF_INET, SOCK_STREAM, 0);
    this->adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(this->port);
    Bind(this->socket_, (struct sockaddr *) &this->adr, sizeof this->adr);
}
void Server::StartListen() {
    Server::Listen(this->socket_, this->count_client);
    socklen_t adrlen = sizeof this->adr;
    this->accept_ = Server::Accept(this->socket_, (struct sockaddr *) &this->adr, &adrlen);
}
void Server::Restart() {
    Stop();
    Start();
}
void Server::Stop() {
    exit(EXIT_FAILURE);
    close(this->accept_);
    close(this->socket_);
}

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
