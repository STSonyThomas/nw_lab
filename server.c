#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // Server IP address
#define SERVER_PORT 12345     // Server port number

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;
    char buffer[1024];

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");

    while (1) {
        // Receive message from client
        memset(buffer, 0, sizeof(buffer));
        addr_size = sizeof(clientAddr);
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &addr_size);

        // Display the received message and client details
        printf("Received message from client: %s", buffer);
        printf("Client address: %s\n", inet_ntoa(clientAddr.sin_addr));
        printf("Client port: %d\n", ntohs(clientAddr.sin_port));

        // Prepare response message
        strcpy(buffer, "Hello, client!");

        // Send response to the client
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    }

    // Close the socket
    close(sockfd);

    return 0;
}