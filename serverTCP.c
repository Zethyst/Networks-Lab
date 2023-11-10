// Server program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h> //Defines Internet constants and structures
#include <sys/socket.h> //Contains data definitions and socket structures, addressing parts
#include <sys/types.h> //Contains data type definitions
#include <arpa/inet.h> //Network manipulation

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket file descriptor, identity 
    //! (Internet Domain,Type of Connection, Protocol value)
    char msg[200];
    char *ip = "127.0.0.1";
    int port = 5000;
    if (sockfd == -1)
    {
        printf("[-]Socket Creation Failed.\n");
        exit(1);
    }
    printf("[+]TCP SERVER Socket Created.\n");
    struct sockaddr_in serv, clint;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port); //correct network byte-order
    // serv.sin_addr.s_addr = inet_addr(ip);
    serv.sin_addr.s_addr = INADDR_ANY; //Local Address

    int b = bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)); 
    if (b == -1)
    {
        printf("[-]Bind Failed.\n");
        exit(1);
    }
    printf("[+]Bind to the Port Number: %d\n", port);
    listen(sockfd, 1); //!Not used for UDP
    printf("Listening...\n");

    while (1)
    {
        int size = sizeof(clint);
        int clintfd = accept(sockfd, (struct sockaddr *)&clint, &size);
        if (clintfd == -1)
        {
            printf("[-]Client Acceptance Failed.\n");
            exit(1);
        }
        printf("[+]Client Connected.\n");
        recv(clintfd, msg, 200, 0);
        printf("\nData reveived => \n");
        printf("Client: %s\n", msg);

        msg[strlen(msg)] = '\0';
        strcpy(msg, "Hi, This is server. Have a nice day!!!");
        // printf("Server: %s\n", msg);
        send(clintfd, msg, 200, 0);
        // close(clintfd);
        // printf("[+]Client Disconnected.\n\n");
    }

    /*
    [+]TCP SERVER Socket Created.
    [+]Bind to the Port Number: 5000
    Listening...
    [+]Client Connected.

    Data reveived => 
    Client: Hi

    */

    return 0;
}