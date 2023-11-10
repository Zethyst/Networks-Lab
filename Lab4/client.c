#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        printf("[-]Socket Creation Failed.\n");
        exit(1);
    }
    printf("[+]UDP CLIENT Socket Created.\n");
    char msg[200];
    int port = 5000;

    struct sockaddr_in serv;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = INADDR_ANY;

    while (1)
    {
        printf("Enter a message: ");
        fgets(msg, sizeof(msg), stdin);
        sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&serv, sizeof(serv));

        struct sockaddr_in from;
        int size = sizeof(from);
        int num_bytes = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&from, &size);
        if (num_bytes <= 0)
        {
            printf("[-]Receive Failed.\n");
            exit(1);
        }

        msg[num_bytes] = '\0';
        printf("Server (IP: %s, Port: %d): %s\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port), msg);
    }

    close(sockfd);
    return 0;
}
