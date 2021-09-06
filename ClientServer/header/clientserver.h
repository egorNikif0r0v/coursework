#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Connection {
protected:
    enum status_ {
        up,
        faild,
        slip,
        listen,
    };

    struct sockaddr_in adr = {0};
    int8_t status;
    int socket;
    uint16_t port = 37123;
    const int buffer_size = 256; 

    int Socket(int, int, int);

public:
    void SetPort(uint16_t);
    uint16_t GetPort();
};


class Client : public Connection{
private:
    char* adress;

    void Connect(int, const struct sockaddr*, socklen_t);
    void Inet_pton(int, const char*, void*);

public:
    Client() {};
    // adress
    Client(char*) {};
    // adress, port
    Client(char*, uint16_t) {};

    void Connect();
    void Reconnect();
    void Disconnect();
};

class Server : public Connection {
private:
    int8_t count_client;

    void Bind(int, const struct sockaddr*, socklen_t);
    void Listen(int, int);
    int Accept(int, struct sockaddr*, socklen_t*);

public:
    Server() {}
    // countclient
    Server(int8_t) {};
    // countclient, port
    Server(int8_t, uint16_t) {};

    

    void Start();
    void StartListen();
    void Restart();
    void Slip();
    void Stop();
};


#endif