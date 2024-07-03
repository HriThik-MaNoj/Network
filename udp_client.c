#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>

int main() {
    char buff[100];
    int k;
    int socket_desc;
    struct sockaddr_in server;
    socklen_t len; // Declare len variable

    socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_desc == -1) {
        printf("Error in socket creation");
        exit(EXIT_FAILURE);
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8008);

    while (1) {
        printf("Enter the data to send: ");
        fgets(buff, sizeof(buff), stdin);
        
        sendto(socket_desc, buff, strlen(buff), 0, (struct sockaddr*)&server, sizeof(server));

        if (strcmp(buff, "EXIT\n") == 0) {
            printf("Exiting\n");
            break;
        }

        len = sizeof(server); // Set len before receiving
        k = recvfrom(socket_desc, buff, sizeof(buff), 0, NULL, NULL);
        if (k == -1) {
            printf("Error in receiving\n");
            exit(EXIT_FAILURE);
        }
        printf("Received: %s", buff);
    }

    close(socket_desc); // Close socket outside the loop
    return 0;
}