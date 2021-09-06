#include "../header/clientserver.h"

int main() {
    char* ip = "127.0.0.1";
    Client first_client(ip);
    
    uint16_t port = 34732;
    first_client.SetPort(port); // default port 37123
    first_client.Connect();

    /*
    int socket = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);

    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(socket, (struct sockaddr *) &adr, sizeof adr);
    
    write(socket, "Hello\n", 6);
    char buf[256];
    ssize_t nread;
    nread = read(socket, buf, 256);
    if (nread == -1) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }else if(nread == 0) {
        printf("EOF occured\n");
    }
    write(STDOUT_FILENO, buf, nread);

    sleep(5);
    close(socket);
    */
    return 0;
}