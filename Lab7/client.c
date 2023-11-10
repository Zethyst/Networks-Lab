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

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("[-]Socket Creation Failed.\n");
        exit(1);
    }
    printf("[+]TCP CLIENT Socket Created.\n");

    struct sockaddr_in serv;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(8080);
    serv.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) == -1)
    {
        printf("[-]Connection Failed.\n");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    int requestedProductNumber;
    while (1)
    {
        printf("Enter Product Number: ");
        scanf("%d", &requestedProductNumber);

        send(sockfd, &requestedProductNumber, sizeof(int), 0);

        // Receive and display product details from the server
        struct Product receivedProduct;
        recv(sockfd, &receivedProduct, sizeof(struct Product), 0);

        printf("Product Number: %d\n", receivedProduct.productNumber);
        printf("Product Name: %s\n", receivedProduct.productName);
        printf("Product Price: %.2f\n", receivedProduct.productPrice);
        printf("Quantity in Stock: %d\n", receivedProduct.quantityInStock);
    }
    close(sockfd);

    return 0;
}
