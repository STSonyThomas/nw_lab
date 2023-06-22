#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // Server IP address
#define SERVER_PORT 12345     // Server port number

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
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

    // Input message from user
    printf("Enter a message: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Send the message to the server
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Receive response from the server
    memset(buffer, 0, sizeof(buffer));
    addr_size = sizeof(serverAddr);
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, &addr_size);

    // Display the received message
    printf("Server response: %s", buffer);

    // Close the socket
    close(sockfd);

    return 0;
}