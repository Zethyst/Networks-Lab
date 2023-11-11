#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

struct Product
{
    int productNumber;
    char productName[50];
    float productPrice;
    int quantityInStock;
};

struct Product findProductByNumber(int productNumber)
{
    struct Product products[] = {
        {101, "Laptop", 899.99, 15},
        {102, "Smartphone", 499.99, 30},
        {103, "Headphones", 79.99, 50},
        {104, "Watch", 49.99, 70},
    };

    for (int i = 0; i < sizeof(products) / sizeof(products[0]); i++)
    {
        if (products[i].productNumber == productNumber)
        {
            return products[i];
        }
    }
    printf("[-] Product Not Found");
    return;
}

int main()
{
    int sockfd, new_socket, valread;
    struct sockaddr_in serv, clint;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("[-]Socket Creation Failed.\n");
        exit(1);
    }
    printf("[+]TCP SERVER Socket Created.\n");

    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) == -1)
    {
        printf("[-]Bind Failed.\n");
        exit(1);
    }
    printf("[+]Bind to the Port Number: 8080\n");

    if (listen(sockfd, 5) == -1)
    {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("[+] Server listening on port 8080...\nWaiting for any incoming product requests...\n");

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

            int requestedProductNumber;
            // Receing product number from the client
            recv(clintfd, &requestedProductNumber, sizeof(int), 0);

            struct Product requestedProduct = findProductByNumber(requestedProductNumber);

            // Sending the product details to the client
            send(clintfd, &requestedProduct, sizeof(struct Product), 0);
        }
        close(clintfd);
    }

    close(sockfd);

    return 0;
}
