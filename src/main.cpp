/*
 
 Lithium Game Server
 @author David Morton
 
 */
#include "server/Server.h"
#include "util/Util.h"
#include <stdio.h>
#include <stdlib.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char **argv)
{
    std::string ret = Util::GenerateUuid();
    printf("Generated uuid=%s\n", ret.c_str());
    
    /*
     * check command line arguments
     */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    int portno = atoi(argv[1]);
    
    Server server;
    server.Init(portno);
    
    return 0;
}
