#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7000
#define MAX_MESSAGE_SIZE 200

int main() {
    int clientfd;
    struct sockaddr_in server_address;
    char message[MAX_MESSAGE_SIZE];

    clientfd = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientfd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("[-]Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("[+]Connected to the server on port %d...\n", PORT);

    while (1) {
        printf("Client: ");
        fgets(message, sizeof(message), stdin);

        send(clientfd, message, strlen(message), 0);

        if (strcmp(message, "bye\n") == 0) {
            printf("[-]Disconnected from the server.\n");
            break;
        }

        memset(message, 0, sizeof(message));
        recv(clientfd, message, sizeof(message), 0);

        printf("Server: %s", message);
    }

    close(clientfd);

    return 0;
}
