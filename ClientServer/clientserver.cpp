#include "../header/clientserver.h"

//...
void Connection::SetPort(uint16_t port) {
    this->port = port;
}
uint16_t Connection::GetPort() {
    return this->port;
}
int Connection::Socket(int domain, int type, int protocol) {
    this->status = socket(domain, type, protocol);
    if(this->status == -1) {
        perror("socket :: fail");
        exit(EXIT_FAILURE);
    } else {
        perror("socket :: OK");
    }
    return this->status;
}
//...


//...
Client::Client() {
    this->adress = "127.0.0.1";
    Client::Connect();
}
Client::Client(char* adress) {
    this->adress = adress;
}
Client::Client(char* adress, uint16_t port) {
    this->adress = adress;
    this->port = port;
    Client::Connect();
}

void Client::Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    this->status = connect(sockfd, addr, addrlen);
    if(this->status == -1) {
        perror("connect fail\n");
        exit(EXIT_FAILURE);
    }else {
        perror("connect :: OK\n");
    }
}
void Inet_pton(int af, const char *src, void *dst) {
int status = inet_pton(af, src, dst);
    if(status == 0) {
        printf("inet_pton :: fail: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family\n");
        exit(EXIT_FAILURE);
    } else if(status == -1) {
        perror("inet_pton :: fail\n");
        exit(EXIT_FAILURE);
    } else {
        perror("inet_pton :: OK\n");
    }
}

void Client::Connect() {
    int socket = Connection::Socket(AF_INET, SOCK_STREAM, 0);

    this->adr.sin_family = AF_INET;
    this->adr.sin_port = htons(this->port);

    Client::Inet_pton(AF_INET, this->adress, &this->adr.sin_addr);
    Client::Connect(socket, (struct sockaddr *) &this->adr, sizeof adr);
}
void Client::Reconnect() {
    close(socket);
    Client::Connect();
}
void Client::Disconnect() {
    close(socket);
}
//...


//...
Server::Server() {
    this->count_client = 1;
    Server::Start();
}
Server::Server(int8_t count_client) {
    this->count_client = count_client;
    Server::Start();
}
Server::Server(int8_t count_client, uint16_t port) {
    this->count_client = count_client;
    this->port = port;
    Server::Start();
}

void Server::Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    this->status = bind(sockfd, addr, addrlen);
    if (this->status == -1) {
        perror("bind :: failed");
        exit(EXIT_FAILURE);
    }else {
        perror("bind :: OK\n");
    }
}
void Server::Listen(int sockfd, int backlog) {
    this->status = listen(sockfd, backlog);
    if (this->status == -1) {
        perror("listen :: fail\n");
        exit(EXIT_FAILURE);
    }else {
        perror("listen :: OK\n");
    }
}
int Server::Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    this->status = accept(sockfd, addr, addrlen);
    if (this->status == -1) {
        perror("accept :: fail\n");
        exit(EXIT_FAILURE);
    }else {
        perror("accept :: OK\n");
    }
    return this->status;
}

void Server::Start() {
    int socket = Socket(AF_INET, SOCK_STREAM, 0);
    this->adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(this->port);
    Bind(socket, (struct sockaddr *) &this->adr, sizeof this->adr);
}
void Server::StartListen() {
    Server::Listen(this->socket, this->count_client);
    socklen_t adrlen = sizeof this->adr;
    int accept = Server::Accept(this->socket, (struct sockaddr *) &this->adr, &adrlen);
}
void Server::Restart() {
    //close(this->fd);
    close(this->port);
    Start();
}
void Server::Stop() {
    //close(this->fd);
    close(this->port);
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
