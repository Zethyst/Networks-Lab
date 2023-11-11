#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

struct Product
{
    int productNumber;
    char productName[50];
    float productPrice;
    int quantityInStock;
};

// Client-side functions
void clientWithoutFork();
void clientWithoutThread();
void *clientThread(void *arg);

int main()
{
    int choice;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Using fork()\n");
        printf("2. Using thread()\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Using fork()
            printf("Using fork()\n");
            clientWithoutFork();
            break;

        case 2:
            // Using thread()
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
            printf("Using thread()\n");
            pthread_t clientThreadID;
            pthread_create(&clientThreadID, NULL, clientThread, (void *)&sockfd);
            pthread_join(clientThreadID, NULL);

            break;

        case 3:
            // Exit
            printf("Exiting the client.\n");
            exit(0);

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

// Client-side function without using fork
void clientWithoutFork()
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
        printf("Enter Product Number (or 0 to exit): ");
        scanf("%d", &requestedProductNumber);

        // Sending product number to the server
        send(sockfd, &requestedProductNumber, sizeof(int), 0);

        if (requestedProductNumber == 0)
        {
            break;
        }

        // Receive and display product details from the server
        struct Product receivedProduct;
        recv(sockfd, &receivedProduct, sizeof(struct Product), 0);

        if (receivedProduct.productNumber == -1)
        {
            printf("Product details not found.\n");
        }
        else
        {
            printf("Product Number: %d\n", receivedProduct.productNumber);
            printf("Product Name: %s\n", receivedProduct.productName);
            printf("Product Price: %.2f\n", receivedProduct.productPrice);
            printf("Quantity in Stock: %d\n", receivedProduct.quantityInStock);
        }
    }

    close(sockfd);
}

// Client-side function using thread
void *clientThread(void *arg)
{
    int sockfd = *((int *)arg);

    int requestedProductNumber;
    while (1)
    {
        printf("Enter Product Number (or 0 to exit): ");
        scanf("%d", &requestedProductNumber);

        // Sending product number to the server
        send(sockfd, &requestedProductNumber, sizeof(int), 0);

        if (requestedProductNumber == 0)
        {
            // Exit the loop if 0 is entered            break;
        }

        // Receive and display product details from the server
        struct Product receivedProduct;
        recv(sockfd, &receivedProduct, sizeof(struct Product), 0);

        if (receivedProduct.productNumber == -1)
        {
            printf("Product details not found.\n");
        }
        else
        {
            printf("Product Number: %d\n", receivedProduct.productNumber);
            printf("Product Name: %s\n", receivedProduct.productName);
            printf("Product Price: %.2f\n", receivedProduct.productPrice);
            printf("Quantity in Stock: %d\n", receivedProduct.quantityInStock);
        }
    }

    // Close the socket
    close(sockfd);

    return NULL;
}