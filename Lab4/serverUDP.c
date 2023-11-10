#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("[-]Socket Creation Failed.\n");
        exit(1);
    }
    printf("[+]UDP SERVER Socket Created.\n");

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(5000);
    serv.sin_addr.s_addr = INADDR_ANY;

    int b = bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    if (b == -1) {
        printf("[-]Bind Failed.\n");
        exit(1);
    }

    printf("[+]Bind to the Port Number: %d\n", ntohs(serv.sin_port));

    while (1) {
        struct sockaddr_in clint;
        int size = sizeof(clint);
        char receivedMsg[200];
        char sentMsg[200];

        int num_bytes = recvfrom(sockfd, receivedMsg, sizeof(receivedMsg), 0, (struct sockaddr *)&clint, &size);
        if (num_bytes <= 0) {
            printf("[-]Receive Failed.\n");
            exit(1);
        }

        receivedMsg[num_bytes] = '\0';

        printf("Client (IP: %s, Port: %d): %s\n", inet_ntoa(clint.sin_addr), ntohs(clint.sin_port), receivedMsg);


        printf("Enter a message for the client: ");
        fgets(sentMsg, sizeof(sentMsg), stdin);

        if (strcmp(receivedMsg, "EXIT\n") == 0) {
            printf("[+]Client requested to close the connection...\n");
            const char *closingMessage = "Server: Connection closed by request.";
            sendto(sockfd, closingMessage, strlen(closingMessage), 0, (struct sockaddr *)&clint, sizeof(clint));
            break;
        }
        
        sendto(sockfd, sentMsg, strlen(sentMsg), 0, (struct sockaddr *)&clint, sizeof(clint));
    }

    close(sockfd);
    return 0;
}
