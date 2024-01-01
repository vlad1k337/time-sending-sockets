#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_LENGTH 4096

void exit_failed(const char* s)
{
    perror(s);
    exit(-1);
}

int main()
{
    int     sockfd, n;
    char    recvline[MAX_LENGTH];
    struct  sockaddr_in addr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        exit_failed("socket creation failed");

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(13);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        exit_failed("connection error");
    while((n = read(sockfd, recvline, MAX_LENGTH)) > 0)
    {
        recvline[n] = '\0';
        if(fputs(recvline, stdout) == EOF)
        {
            exit_failed("fputs error");    
        }
    }
    if(n < 0)
    {
        exit_failed("read error");
    }
}
