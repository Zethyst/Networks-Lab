#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

struct sockaddr_in serv, clint;

int main()
{
    serv.sin_family = AF_INET;
    serv.sin_port = htons(5000);
    serv.sin_addr.s_addr = INADDR_ANY;

    // adress family- ip4 or ip6 or what address -- 
    // AF_INET for ipv4
    //  AF_INET6 for ipv6
    //  AF_BTH for bluetooth
    //  AF_IRDA for infrared data association

    // Socket Type
    // SOCK_STREAM for tcp connection
    // SOCK_DGRAM for udp connection

    // Protocol Type
    // IPPROTO_TCP
    // IPPROTO_UDP
    // 0 -- when not explicitly mentioning protocol type

    // socket(address family,socket type,protocol type);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // returns id if successfull or -1 incase of error, para 0 for protocol name
    if (sockfd == -1)
    {
        printf("Socket creation failed");
        exit(1);
    }
    printf("SOCKET CREATED");

    int b = bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    if (b == -1)
    {
        printf("Bind failed");
        exit(1);
    }
    listen(sockfd, 1); //1 is number of client
    int size=sizeof(clint);
    int clintfd=accept(sockfd, (struct sockaddr *)&clint, &size);
    if (clintfd==-1)
    {
        printf("clint acceptance failed");
        exit(1);
    }
    
    return 0;
}