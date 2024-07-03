#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int socket_desc, new_socket_desc, client_size, frame;
    struct sockaddr_in server, client;
    char server_message[2000], client_message[2000];

    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind to the set port and IP:
    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");

    // Listen for clients:
    if (listen(socket_desc, 1) < 0) {
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections.....\n");

    // Accept an incoming connection:
    client_size = sizeof(client);
    new_socket_desc = accept(socket_desc, (struct sockaddr*)&client, &client_size);

    if (new_socket_desc < 0) {
        printf("Can't accept\n");
        return -1;
    }
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    while (1) {
        // Receive client's message:
        if (recv(new_socket_desc, client_message, sizeof(client_message), 0) < 0) {
            printf("Couldn't receive\n");
            return -1;
        }
        printf("Msg from client: %s\n", client_message);

        // Respond to client:
        memset(server_message, '\0', sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));

        printf("\nServer Acknowledges or not:? Ack-Y or y, NACK- N or n");
    z:
        memset(server_message, '\0', sizeof(server_message));
        scanf("%s", server_message);

        if (send(new_socket_desc, server_message, strlen(server_message), 0) < 0) {
            printf("Can't send\n");
            return -1;
        }
        if (strcmp(server_message, "N") == 0 || strcmp(server_message, "n") == 0) {
            printf("Acknowledgement not received by client");
            goto z;
        }
    }

    // Closing the socket:
    close(new_socket_desc);
    close(socket_desc);

    return 0;
}