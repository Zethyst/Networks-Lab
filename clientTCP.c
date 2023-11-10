// Client Program ============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char msg[2000];
    char *ip = "127.0.0.1";
    int port = 5000;
    if (sockfd == -1)
    {
        printf("[-]Socket Creation Failed\n");
        exit(1);
    }
    printf("[+]TCP SERVER Socket Created.\n");
    struct sockaddr_in serv;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = INADDR_ANY;

    int servfd = connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    if (servfd == -1)
    {
        printf("[-]Connection Failed.\n");
        exit(1);
    }
    printf("[+]Connected to the Server.\n");
    strcpy(msg, "Hi");
    msg[strlen(msg)] = '\0';
    send(sockfd, msg, 200, 0);
    printf("\n[+]Data send\n");

    msg[strlen(msg)] = '\0';
    recv(sockfd, msg, 200, 0);
    printf("Server: %s\n", msg);

    // close(sockfd);
    printf("[+]Disconnected from the Server.\n");

    /*
    [+]TCP SERVER Socket Created.
    [+]Connected to the Server.
    [+]Data send
    Server: Hi, This is server. Have a nice day!!!
    [+]Disconnected from the Server.
    */

    return 0;
}
