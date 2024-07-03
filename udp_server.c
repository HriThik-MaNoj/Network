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
    struct sockaddr_in server, client;
    socklen_t len; // Declare len variable

    socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_desc == -1) {
        printf("Error in socket creation");
        exit(EXIT_FAILURE);
    }
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8008);

    k = bind(socket_desc, (struct sockaddr*)&server, sizeof(server));
    if (k == -1) {
        printf("Error in binding\n");
        exit(EXIT_FAILURE);
    }

    len = sizeof(client);
    while (1) {
        k = recvfrom(socket_desc, buff, sizeof(buff), 0, (struct sockaddr*)&client, &len);
        if (k == -1) {
            printf("Error in receiving\n");
            exit(EXIT_FAILURE);
        }

        if (strcmp(buff, "EXIT\n") == 0) {
            printf("Exiting\n");
            break;
        }

        printf("Received: %s", buff);

        printf("Enter the data to send: ");
        fgets(buff, sizeof(buff), stdin);
        k = sendto(socket_desc, buff, strlen(buff), 0, (struct sockaddr*)&client, len);
        if (k == -1) {
            printf("Error in sending\n");
            exit(EXIT_FAILURE);
        }
    }

    close(socket_desc); // Close socket outside the loop
    return 0;
}