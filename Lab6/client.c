#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_MESSAGE_SIZE 200

int main()
{
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client!";
    char buffer[MAX_MESSAGE_SIZE] = {0};


    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("[-]Socket creation Failed");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("[-]Invalid address/ Address not supported");
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("[-]Connection failed");
        exit(1);
    }

    printf("[+]Connected to the server on port %d...\n", PORT);
    while (1)
    {
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(sockfd, buffer, strlen(buffer), 0);
        printf("Message sent\n");
        recv(sockfd, buffer, sizeof(buffer), 0);
        printf("Received: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
