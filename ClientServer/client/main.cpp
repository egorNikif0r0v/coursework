#include "../clientserver.cpp"

int main() {
    char* ip = "127.0.0.1";
    Client first_client("first_client", ip, 24522);
    first_client.Connect();
    char buff[first_client.GetBufferSize()];
    first_client.Write(first_client.GetSocket(), first_client.GetNameClient(), 13);
    

    return 0;
}