#ifndef ERPROC_H
#define ERPROC_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Connection {
protected:
    enum status{
        failed = -1,
        up = 0,
    };

    int8_t status_;
    uint16_t port = 37123;
    const int buffer_size = 256; 

    int Socket(int, int, int);

public:
    void SetPort(uint16_t);
    uint16_t GetPort();

    int8_t GetStatus();
};


class Client : public Connection{
private:
    char* adress;

public:
    // adress
    Client(char*) {};
    // adress, port
    Client(const char*, const uint16_t) {};

    void Connect(int, const struct sockaddr*, socklen_t);
    void Inet_pton(int, const char*, void*);

    void Connect();
    void Reconnect();
    void Disconnect();
};

class Server : public Connection {
private:
    int8_t count_client;

public:
    // countclient
    Server(int8_t) {};
    // countclient, port
    Server(const int8_t, const uint16_t) {};

    void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    void Listen(int sockfd, int backlog);
    int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

    void Start();
    void Restart();
    void Stop();
};

#endif