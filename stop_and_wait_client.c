#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void) {
    int socket_desc;
    int timer, frame;
    struct sockaddr_in server;
    char server_message[2000], client_message[2000];

    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP the same as server-side:
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // Send connection request to server:
    if (connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Unable to connect\n");
        return -1;
    }
    printf("Connected with server successfully\n");

    printf("Enter the total frames: ");
    scanf("%d", &frame);

    while (frame > 0) {
        // Get input from the user:
        memset(server_message, '\0', sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));
        printf("\nEnter frame message: ");
        scanf("%s", client_message);

        // Send the message to server:
    x:
        timer = 10;
        if (send(socket_desc, client_message, strlen(client_message), 0) < 0) {
            printf("Unable to send message\n");
            return -1;
        }

        // Receive the server's response:
    y:
        if (timer > 0) {
            if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0) {
                printf("Error while receiving server's msg\n");
                timer--;
                goto y;
            }
            if (strcmp(server_message, "N") == 0 || strcmp(server_message, "n") == 0) {
                printf("\nWaiting...");
                timer--;
                goto y;
            }
            if (strcmp(server_message, "Y") == 0 || strcmp(server_message, "y") == 0) {
                printf("\nServer acknowledged");
                timer = 0;
                frame--;
            }
        } else {
            printf("\nServer did not acknowledge\nResending....");
            goto x;
        }
    }

    // Close the socket:
    close(socket_desc);

    return 0;
}