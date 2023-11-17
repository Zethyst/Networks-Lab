#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

struct Product
{
    int productNumber;
    char productName[50];
    float productPrice;
    int quantityInStock;
};

// Server-side function using fork
void serverFork(void);

// Server-side function using thread
void *serverThread(void *arg);

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
            printf("Using fork()\n");
            serverFork();
            break;

        case 2:
            // Using thread()
            printf("Using thread()\n");
            pthread_t serverThreadID;
            pthread_create(&serverThreadID, NULL, serverThread, NULL);
            pthread_join(serverThreadID, NULL);
            break;

        case 3:
            // Exit
            printf("Exiting the server.\n");
            exit(0);

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

// Server-side function using fork
void serverFork()
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

        int child_pid = fork();

        if (child_pid < 0)
        {
            printf("[-]Fort Failed.\n");
            exit(1);
        }

        if (child_pid == 0)
        {
            close(sockfd);

            printf("[+]Client Connected.\n");

            while (1)
            {
                int requestedProductNumber;
                // Receiving product number from the client
                recv(clintfd, &requestedProductNumber, sizeof(int), 0);

                // struct Product requestedProduct = {
                //     .productNumber = requestedProductNumber,
                // };
                struct Product requestedProduct;

                requestedProduct.productNumber = requestedProductNumber;

                switch (requestedProductNumber)
                {
                case 101:
                    strcpy(requestedProduct.productName, "Laptop");
                    requestedProduct.productPrice = 899.99;
                    requestedProduct.quantityInStock = 15;
                    break;

                case 102:
                    strcpy(requestedProduct.productName, "Smartphone");
                    requestedProduct.productPrice = 499.99;
                    requestedProduct.quantityInStock = 30;
                    break;

                case 103:
                    strcpy(requestedProduct.productName, "Headphones");
                    requestedProduct.productPrice = 79.99;
                    requestedProduct.quantityInStock = 50;
                    break;

                case 104:
                    strcpy(requestedProduct.productName, "Watch");
                    requestedProduct.productPrice = 49.99;
                    requestedProduct.quantityInStock = 70;
                    break;

                default:
                    printf("[-] Product Not Found\n");
                    // If the product is not found, create a default product with productNumber = -1
                    requestedProduct.productNumber = -1;
                    break;
                }

                // Sending the product details to the client
                send(clintfd, &requestedProduct, sizeof(struct Product), 0);
            }

            close(clintfd);
            exit(0);
        }
        else
        {
            close(clintfd);
        }
    }

    close(sockfd);
}

// Server-side function using thread
void *serverThread(void *arg)
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
        // Receiving product number from the client
        recv(clintfd, &requestedProductNumber, sizeof(struct Product), 0);

        struct Product requestedProduct;

        requestedProduct.productNumber = requestedProductNumber;

        switch (requestedProductNumber)
        {
        case 101:
            strcpy(requestedProduct.productName, "Laptop");
            requestedProduct.productPrice = 899.99;
            requestedProduct.quantityInStock = 15;
            break;

        case 102:
            strcpy(requestedProduct.productName, "Smartphone");
            requestedProduct.productPrice = 499.99;
            requestedProduct.quantityInStock = 30;
            break;

        case 103:
            strcpy(requestedProduct.productName, "Headphones");
            requestedProduct.productPrice = 79.99;
            requestedProduct.quantityInStock = 50;
            break;

        case 104:
            strcpy(requestedProduct.productName, "Watch");
            requestedProduct.productPrice = 49.99;
            requestedProduct.quantityInStock = 70;
            break;

        default:
            printf("[-] Product Not Found\n");
            // If the product is not found, create a default product with productNumber = -1
            requestedProduct.productNumber = -1;
            break;
        }

        // Sending the product details to the client
        send(clintfd, &requestedProduct, sizeof(struct Product), 0);
    }

    close(clintfd);
    close(sockfd);
    return NULL;
}
