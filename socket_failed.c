#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  // Creating a TCP socket

    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Continue with using the socket...

    return 0;
}
