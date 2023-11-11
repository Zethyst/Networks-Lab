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
        printf("Usage in this form: %s <ip_address> <port>\n", argv[0]);
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("[-]Socket Creation Failed.\n");
        exit(1);
    }
    printf("[+]TCP SERVER Socket Created.\n");
    char msg[200];
    char receivedMsg[200];
    char sentMsg[200];
    int port = atoi(argv[2]); //string to integer

    struct sockaddr_in serv, clint;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = inet_addr(argv[1]);

    int b = bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    if (b == -1)
    {
        printf("[-]Bind Failed.\n");
        exit(1);
    }

    printf("[+]Bind to the Port Number: %d\n", port);
    listen(sockfd, 1);
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

        while (1)
        {
            int num_bytes = recv(clintfd, receivedMsg, sizeof(receivedMsg), 0);
            if (num_bytes <= 0)
            {
                printf("[-]Client Disconnected.\n");
                break;
            }

            receivedMsg[num_bytes] = '\0';
            printf("Client (IP: %s, Port: %s): %s\n", inet_ntoa(clint.sin_addr), argv[2], receivedMsg);
            // printf("Client: %s\n", msg);

            if (strcmp(receivedMsg, "exit") == 0)
            {
                printf("[+]Closing connection...\n");
                break;
            }
            
        printf("Enter a message for the client: ");
        fgets(sentMsg, sizeof(sentMsg), stdin);

        if (strcmp(receivedMsg, "EXIT\n") == 0) {
            printf("[+]Client requested to close the connection...\n");
            const char *closingMessage = "Server: Connection closed by request.";
            send(clintfd, closingMessage, strlen(closingMessage), 0);
            break;
        }
        
        send(clintfd, sentMsg, strlen(sentMsg), 0);

            // strcpy(msg, "Hello, This is server.");
            // strcpy(msg, "This is server. Your message was received successfully!");
            // send(clintfd, msg, strlen(msg), 0);
        }

        // close(clintfd);
    }

    close(sockfd);
    return 0;
}
