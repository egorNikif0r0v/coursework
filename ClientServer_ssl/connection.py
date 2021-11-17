from socket import * 
import ssl
import sys
import traceback
import json

version_dict = {
    "tlsv1.0" : ssl.PROTOCOL_TLSv1,
    "tlsv1.1" : ssl.PROTOCOL_TLSv1_1,
    "tlsv1.2" : ssl.PROTOCOL_TLSv1_2,
    "sslv23"  : ssl.PROTOCOL_SSLv23,
}
conf_file = open('config/conf.json', 'r')
data = json.load(conf_file)

class connect:
    def __init__(self):
        self.HOST = data['connect']['node_data']['host']
        self.PORT = int(data['connect']['node_data']['port'])
        self.ssl_version = None
        self.ciphers = None
        self.certfile = data['connect']['path']['certfile']
        self.keyfile = data['connect']['path']['keyfile']
        
    def get_info(self):
        print("version - ", self.ssl_version, "ciphers - ", self.ciphers, "certfile - ", self.certfile,\
                        "keyfile - ", self.keyfile, "HOST - ", self.HOST, "PORT - ", self.PORT)

class server(connect):
    def __init__(self):
        connect.__init__(self)
        self.server_socket = socket(AF_INET, SOCK_STREAM) 
        self.server_socket.bind((self.HOST, eval(str(self.PORT))))
        self.total_users = int(data['connect']['node_data']['total_users'])
        self.server_socket.listen(self.total_users)
        self.connected_users = 0

    def ssl_wrap_socket(self, sock):
        if self.ssl_version is not None and self.ssl_version in version_dict:
            #создание ssl контекста(принимает версию протокола)
            sslContext = ssl.SSLContext(version_dict[self.ssl_version])
            print("ssl_version OK - ", self.ssl_version)
        else:
            #создание ssl контекста по умолчанию
            sslContext = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
        if self.ciphers is not None:
            #задание шифра
            sslContext.set_ciphers(self.ciphers)
            print("ciphers OK - ", self.ciphers)
        
        sslContext.load_cert_chain(self.certfile, self.keyfile)

        try:
            #создание сокета
            return sslContext.wrap_socket(sock, server_side = True)
        except ssl.SSLError as e:
            print("wrap socket failed")
            print(traceback.format_exc())
    
    def get_message(self, connection_socket):
        if connection_socket != -1:
            connection_socket.sendall('you connected'.encode('utf-8'))

            message = connection_socket.recv(1024)
            user_name = bytes.decode(message, encoding='utf-8')

            print(user_name, 'connected')
            try:
                while True:
                    try:
                        message = connection_socket.recv(1024)
                        print(user_name, " --> ", bytes.decode(message, encoding='utf-8'))
                    except:
                        self.connected_users-=1
                        print(user_name, ' disconnected')
                        break
            except IOError:
                connection_socket.send("404 Not Found")
                connection_socket.shutdown(SHUT_RDWR)
                connection_socket.close()
        else:
            print('connect error')

    def listening(self):
        print ('server is listening...')
        newSocket, addr = self.server_socket.accept()
        connection_socket =  self.ssl_wrap_socket(newSocket)

        

        self.connected_users+=1
        return -1 if not connection_socket else connection_socket

    def shot_down(self):
        self.server_socket.close()
        sys.exit(0)

class client(connect):    
    def __init__(self):
        connect.__init__(self)
        self.certfile = None    
        self.hostname = 'localhost'

        client_socket = socket(AF_INET, SOCK_STREAM)
        self.ssl_socket = self.ssl_wrap_socket(client_socket)
        self.ssl_socket.connect((self.HOST, eval(str(self.PORT))))

        message = self.ssl_socket.recv(1024)
        print(bytes.decode(message, encoding='utf-8'))
        
        message = input('user_name --> ')
        self.ssl_socket.sendall(message.encode('utf-8'))
        

    def send_message(self):
        try:
            message = input('message --> ')
            self.ssl_socket.sendall(message.encode('utf-8'))
        except socket.error:
            print('ERROR: Send failed')
            self.ssl_socket.shutdown(SHUT_RDWR)
            self.ssl_socket.close()
            sys.exit(-1)
        
    def ssl_wrap_socket(self, sock):
        try:
            if self.ssl_version is not None and self.ssl_version in version_dict:
                ssl_context = ssl.SSLContext(version_dict[self.ssl_version])
                print("ssl_version OK - ", self.ssl_version)
            else:
                ssl_context = ssl.create_default_context()
            
            if self.ciphers is not None:
                ssl_context.set_ciphers(self.ciphers)
                print("ciphers OK - ", self.ciphers)
            
            if self.certfile is not None and self.keyfile is not None:
                ssl_context.verify_mode = ssl.CERT_REQUIRED
                ssl_context.check_hostname = True
                ssl_context.load_verify_locations(self.certfile, self.keyfile)
                print("ssl OK certfile - ", self.certfile, "keyfile - ", self.keyfile)
                return ssl_context.wrap_socket(sock, server_hostname = self.hostname)
            else:
                ssl_context.check_hostname = False
                ssl_context.verify_mode = ssl.CERT_NONE
                ssl_context.load_default_certs()
                return ssl_context.wrap_socket(sock)
            
        except ssl.SSLError:
            print("wrap socket failed")
            print(traceback.format_exc())
            self.sock.close()
            sys.exit(-1)
