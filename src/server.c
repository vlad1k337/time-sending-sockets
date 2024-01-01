#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 4096
int main()
{
    char write_buf[MAX_LENGTH];
    int server_fd, write_fd;
    struct sockaddr_in addr;
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(-1);
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(13);
    addr.sin_addr.s_addr    = htonl(INADDR_ANY);

    if(bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind error");
        exit(-1);
    }
    listen(server_fd, 1);

    for(;;)
    {
        write_fd = accept(server_fd, NULL, NULL);
        time_t ticks = time(NULL);

        snprintf(write_buf, sizeof(write_buf), "%.24s\er\en", ctime(&ticks));
        write(write_fd, write_buf, strlen(write_buf));
        
        close(write_fd);
    }
    
}
