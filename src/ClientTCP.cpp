#include <arpa/inet.h>
#include <chrono>
#include <cstring>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <iostream>

int main()
{
    int sockfd = -1;
    struct sockaddr_in server_addr;
    char send_buffer[1024];
    char recv_buffer[1024];
    time_t ticks;

    memset(recv_buffer, 0, sizeof(recv_buffer));
    memset(&server_addr, 0, sizeof(server_addr));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000);

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0)
    {
        int i = 0;
        while(i++ < 10)
        {
            //read(sockfd, recv_buffer, sizeof(recv_buffer));
            //std::cout << recv_buffer << std::endl;
            std::strcpy(send_buffer, std::strcat( std::to_string(i).data(), " Hello server \n"));

            write(sockfd, send_buffer, strlen(send_buffer));

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

}
