/*
 * udpserver.c - A simple UDP echo server
 * usage: udpserver <port>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

/*
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {
    printf("Main");

    int sockfd; /* socket */
    int portno; /* port to listen on */
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
    
    /*
     * check command line arguments
     */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    portno = atoi(argv[1]);
    
    printf("Creating socket");

    /*
     * socket: create the parent socket
     */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    error("ERROR opening socket");
    
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
    serveraddr.sin_port = htons((unsigned short)portno);
    
    /*
     * bind: associate the parent socket with a port
     */
    if (bind(sockfd, (struct sockaddr *) &serveraddr,
             sizeof(serveraddr)) < 0)
    error("ERROR on binding");
    
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
        error("ERROR in recvfrom");
        
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
            error("ERROR in sendto");
        }
        
        
        /*
         if(strcmp(buf, "{uid:001,value:w}") == 0)
         {
         playerOneY++;
         }
         else if(strcmp(buf, "{uid:001,value:a}\n") == 0)
         {
         playerOneX--;
         }
         else if(strcmp(buf, "{uid:001,value:s}\n") == 0)
         {
         playerOneY--;
         }
         else if(strcmp(buf, "{uid:001,value:d}\n") == 0)
         {
         playerOneX++;
         }
         
         if(strcmp(buf, "{uid:002,value:w}\n") == 0)
         {
         playerTwoY++;
         }
         else if(strcmp(buf, "{uid:002,value:a}\n") == 0)
         {
         playerTwoX--;
         }
         else if(strcmp(buf, "{uid:002,value:s}\n") == 0)
         {
         playerTwoY--;
         }
         else if(strcmp(buf, "{uid:002,value:d}\n") == 0)
         {
         playerTwoX++;
         }
         */
        
        
    }
}
