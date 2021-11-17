from connection import client

if __name__ == "__main__":
    client_ = client()
    while True:
        client_.send_message()