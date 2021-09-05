#include "../header.h"

int main() {
    uint8_t count_client = 6;
    Server server(count_client);

    server.SetPort(24533);
    server.Start();
    server.Stop();

    /*
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    socklen_t adrlen = sizeof adr;
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);
    ssize_t nread;
    char buf[256];
    nread = read(fd, buf, 256);
    if (nread == -1) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }else if(nread == 0) {
        printf("END OF FILE occured\n");
    }
    write(STDOUT_FILENO, buf, nread);
    write(fd, buf, nread);

    sleep(25);

    close(fd);
    close(server);
    */
    return 0;
}