#include <algorithm>
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <iostream>
#include 
int main()
{
    int listenfd = -1;
    int connfd = -1;
    struct sockaddr_in server_addr;
    char send_buffer[1024];
    char recv_buffer[1024];
    time_t ticks;

    memset(send_buffer, 0, sizeof(send_buffer));
    memset(&server_addr, 0, sizeof(server_addr));

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(listenfd, 10);
   
    while(true)
    {
        std::cout<< "Dang cho nhan tin hieu tu sever" << std::endl;
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        ticks = time(NULL);
        std::strcpy(send_buffer, "Hello client");
        std::cout << "Gui client: " << send_buffer << std::endl;
        write(connfd, send_buffer, strlen(send_buffer));
        read(connfd, recv_buffer, sizeof(recv_buffer));
        std::cout << recv_buffer << std::endl;
        close(connfd);
    }
    close(listenfd);
    
}
