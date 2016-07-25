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
  int sockfd; /* socket */
  int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE]; /* message buf */
  char *hostaddrp; /* dotted decimal host addr string */
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
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
	     (const void *)&optval , sizeof(int));

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


  while (1) {

    /*
     * recvfrom: receive a UDP datagram from a client
     */
    bzero(buf, BUFSIZE);
    n = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr *) &clientInfo, &clientInfo_len);
    if (n < 0)
      error("ERROR in recvfrom");

    int rv = getnameinfo((struct sockaddr *)&clientInfo, clientInfo_len, inetAddress, sizeof(inetAddress), 0, 0, NI_NUMERICHOST);
    if(rv == 0)
    {
      printf("Client address %s\n", inetAddress);
      printf("Recv buffer: %s\n", buf);
    }

    /*
      Game Logic
    */

    /*
      Update the X and Y values of the character on the server based on the direction
      they have moved. The direction is received by the characters w, a, s, d
    */

    /* Player One */
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

    /* Player Two */
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

    // Prepare result string for game client
    sprintf(buf, "{uid:001,value:w}");

    /*
     * Send the updated position of the character to the game client
     */
    n = sendto(sockfd, buf, strlen(buf), 0,
	       (struct sockaddr *) &clientInfo, clientInfo_len);
    if (n < 0)
      error("ERROR in sendto");
  }
}
