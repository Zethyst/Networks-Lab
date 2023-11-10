#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 5

int main()
{
    int sockfd, new_socket, valread;
    struct sockaddr_in serv;
    int opt = 1;
    int addrlen = sizeof(serv);

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("[-]Socket Creation Failed.\n");
        exit(1);
    }
    printf("[+]TCP SERVER Socket Created.\n");

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = INADDR_ANY;

    // Forcefully attaching socket to the port 8080
    if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        printf("[-]Bind Failed.\n");
        exit(1);
    }

    printf("[+]Bind to the Port Number: %d\n", PORT);
    if (listen(sockfd, MAX_CLIENTS) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Listening...\n");

    while (1)
    {
        if ((new_socket = accept(sockfd, (struct sockaddr *)&serv,
                                 (socklen_t *)&addrlen)) < 0)
        {
            printf("[-]Client Acceptance Failed.\n");
            exit(1);
        }

        int child_pid = fork();

        if (child_pid < 0)
        {
            printf("[-]Fort Failed.\n");
            exit(1);
        }

        if (child_pid == 0)
        {                  // This is the child process
            close(sockfd); // Child doesn't need the listener

            // Handle communication with the client here
            while (1)
            {
                char buffer[1024] = {0};
                valread = read(new_socket, buffer, sizeof(buffer));
                printf("Received: %s\n", buffer);
                const char *response = "Hello from server!";
                send(new_socket, response, strlen(response), 0);
                printf("Response sent\n");
            }
            close(new_socket); // Close the connection in the child process
            exit(0);           // Exit the child process
        }
        else
        {                      // This is the parent process
            close(new_socket); // Parent doesn't need the new socket
        }
    }

    return 0;
}
