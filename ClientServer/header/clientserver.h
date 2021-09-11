#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

class Connection {
protected:
    /*enum status_ {
        up,
        faild,
        slip,
        listen,
    };*/

    struct sockaddr_in adr = {0};
    int socket_;
    uint16_t port = 37123;

    int buffer_size = 256;


    void Socket(int, int, int);

public:
    int GetSocket();

    int GetBufferSize();
    void SetBufferSize(int);

    int Read(int, char*, int);
    void Write(int ,char*, int);

    void SetPort(uint16_t);
    uint16_t GetPort();
};


class Client : public Connection{
private:
    char* adress;
    char* name_client;

    void Connect(int, const struct sockaddr*, socklen_t);
    void Inet_pton(int, const char*, void*);

public:
    Client();
    // adress
    Client(char*, char*);
    // adress, port
    Client(char*, char*, uint16_t);

    char* GetNameClient();

    void Connect();
    void Reconnect();
    void Disconnect();
};

class Server : public Connection {
private:
    int8_t count_client;
    int accept_ = -1;
    char* name_server;

    void Bind(int, const struct sockaddr*, socklen_t);
    void Listen(int, int);
    int Accept(int, struct sockaddr*, socklen_t*);

public:
    Server();
    // countclient
    Server(char* , int8_t);
    // countclient, port
    Server(char*, int8_t, uint16_t);

    int GetAccept();

    char* GetNameServer();

    void Start();
    void StartListen();
    void Restart();
    void Slip();
    void Stop();
};


#endif