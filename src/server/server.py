import socket
import select

def Main():
    print ("Game server up")

    host = "127.0.0.1"
    port = 5000

    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSocket.bind((host, port))

    while (True):
        print ("Listening")
        recvData, addr = serverSocket.recvfrom(2048)
        data = recvData.decode()
        print (data)
        serverSocket.sendto(data.encode(), addr)


if __name__ == '__main__':
    Main()
