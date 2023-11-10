#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <ip_address> <port>\n", argv[0]);
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("[-]Socket Creation Failed.\n");
        exit(1);
    }
    printf("[+]TCP CLIENT Socket Created.\n");
    char msg[200];
    int port = atoi(argv[2]);

    struct sockaddr_in serv;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) == -1)
    {
        printf("[-]Connection Failed.\n");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    while (1)
    {
        printf("Enter a message: ");
        fgets(msg, sizeof(msg), stdin);
        send(sockfd, msg, strlen(msg), 0);

        if (strcmp(msg, "exit\n") == 0)
        {
            printf("[+]Exiting...\n");
            break;
        }

        int num_bytes = recv(sockfd, msg, sizeof(msg), 0);
        if (num_bytes <= 0)
        {
            printf("[-]Server disconnected.\n");
            break;
        }

        msg[num_bytes] = '\0';
        printf("Server: %s\n", msg);
    }

    close(sockfd);
    return 0;
}
