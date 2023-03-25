#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    while(1) {
        printf("Enter message: ");
        fgets(buffer, 1024, stdin);
        send(sock, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
     memset(buffer, 0, sizeof(buffer));



    //    printf("\nCOMMAND FOR EXECUTION ... ");
    //     fgets(buffer, sizeof(buffer), stdin);
    //     sendto(serverDescriptor, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, serverLength);
    //     printf("\nData Sent !");
    //     recvfrom(serverDescriptor, message, sizeof(message), 0, (struct sockaddr *)&serverAddress, &serverLength);
    //     printf("UDP SERVER : %s", message);
    }
    return 0;
}