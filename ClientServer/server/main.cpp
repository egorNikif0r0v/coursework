#include "../clientserver.cpp"

int main() {
    uint8_t count_client = 6;
    Server server("server", count_client);
    char buf[server.GetBufferSize()];

    server.SetPort(24522);
    server.Start();
    server.StartListen();
    int nread = server.Read(server.GetAccept(), buf, server.GetBufferSize());
    server.Write(STDOUT_FILENO, buf, nread);
    sleep(5);
    server.Stop();

    return 0;
}