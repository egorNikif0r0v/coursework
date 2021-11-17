import threading


from connection import server

if __name__ == "__main__":
    server_ = server()
    server_.get_info()
    while True:
        if server_.connected_users < server_.total_users:
            print('users: ', server_.connected_users)
            threading.Thread(target=server_.get_message, args=(server_.listening(),) , daemon=True).start()
        else:
            server.shot_down()
