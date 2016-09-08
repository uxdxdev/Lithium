#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <uuid/uuid.h>

#include "server/Server.h"

#define BUFSIZE 1024

int Server::TestFunction(int x)
{
    return x + 1;
}

void Server::Init(int port)
{
    int sockfd; /* socket */
    int clientlen; /* byte size of client's address */
    struct sockaddr_in serveraddr; /* server's addr */
    struct sockaddr_in clientaddr; /* client addr */
    char sendBuffer[BUFSIZE];
    sendBuffer[0] = '\0';
    char recvBuffer[BUFSIZE];
    recvBuffer[0] = '\0';
    int optval; /* flag value for setsockopt */
    int n; /* message byte size */
    
    // Player One
    int playerOneX, playerOneY;
    playerOneX = 0;
    playerOneY = 0;
    
    // Player Two
    int playerTwoX, playerTwoY;
    playerTwoX = 0;
    playerTwoY = 0;
    
    printf("Creating socket");
    
    /*
     * socket: create the parent socket
     */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        
    /* setsockopt: Handy debugging trick that lets
     * us rerun the server immediately after we kill it;
     * otherwise we have to wait about 20 secs.
     * Eliminates "ERROR on binding: Address already in use" error.
     */
        optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
    
    /*
     * build the server's Internet address
     */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port);
    
    /*
     * bind: associate the parent socket with a port
     */
    if (bind(sockfd, (struct sockaddr *) &serveraddr,
             sizeof(serveraddr)) < 0)
        
    /*
     * main loop: wait for a datagram, then echo it
     */
        clientlen = sizeof(clientaddr);
    
    /*
     * gethostbyaddr: determine who sent the datagram
     */
    struct sockaddr_storage clientInfo;
    socklen_t clientInfo_len = sizeof(clientInfo);
    char inetAddress[INET6_ADDRSTRLEN];
    
    printf("Server starting");
    
    while (1) {
        
        /*
         * recvfrom: receive a UDP datagram from a client
         */
        bzero(recvBuffer, BUFSIZE);
        n = recvfrom(sockfd, recvBuffer, BUFSIZE, 0, (struct sockaddr *) &clientInfo, &clientInfo_len);
        if (n < 0)
        {
            std::cout << "Error receiving";
        }
        
        int rv = getnameinfo((struct sockaddr *)&clientInfo, clientInfo_len, inetAddress, sizeof(inetAddress), 0, 0, NI_NUMERICHOST);
        if(rv == 0)
        {
            printf("Client address %s\n", inetAddress);
            printf("Message: %s\n", recvBuffer);
        }
        
        /*
         Game Logic
         */
        
        // Client messages
        
        int processResult = ProcessBuffer(recvBuffer);
        if(processResult < 0)
        {
            printf("Error processing buffer");
        }
        
        // FireballA
        if(strcmp(recvBuffer, "{uid:001,value:w}") == 0)
        {
            // If fireballA moves, move fireballB
            sprintf(sendBuffer, "{uid:002,value:w}");
            printf("Sending message to the client: %s\n", sendBuffer);
            
            /*
             * Send the updated position of the character to the game client
             */
            n = sendto(sockfd, sendBuffer, strlen(sendBuffer), 0,
                       (struct sockaddr *) &clientInfo, clientInfo_len);
            if (n < 0)
            {
                std::cout << "Error sending";
            }
        }
    }
}

int Server::ProcessBuffer(const char *buffer)
{
    int success = -1;
    
    
    return success;
}