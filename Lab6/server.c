#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7000
#define MAX_CLIENTS 5

void handle_client(int client_socket) {
    char message[200];

    while (1) {
        memset(message, 0, sizeof(message));
        recv(client_socket, message, sizeof(message), 0);

        printf("Client: %s", message);

        if (strcmp(message, "bye\n") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Server: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);
    }

    close(client_socket);
}

int main() {
    int sockfd, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("[-]Socket Creation Failed.\n");
        exit(1);
    }

    printf("[+]TCP SERVER Socket Created.\n");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int b = bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address));
    if (b == -1)
    {
        printf("[-]Bind Failed.\n");
        exit(1);
    }

    printf("[+]Bind to the Port Number: %d\n", PORT);

    listen(sockfd, MAX_CLIENTS);

    printf("[+]Server listening on port %d...\n", PORT);

    while (1) {
        addr_size = sizeof(client_address);
        client_socket = accept(sockfd, (struct sockaddr*)&client_address, &addr_size);

        printf("[+]Connection accepted from Client [%s:%d]\n",
               inet_ntoa(client_address.sin_addr),
               ntohs(client_address.sin_port));

        handle_client(client_socket);
    }

    close(sockfd);

    return 0;
}
