#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){

    int socket_desc;
    char buff[1024];
    struct sockaddr_in server;

    socket_desc=socket(AF_INET,SOCK_DGRAM,0);
    if(socket_desc == -1){

        printf("Socket creation failed");
        return 1;
    }

    memset(&server,0,sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

   

    printf("Enter a string to reverse : ");
    fgets(buff,sizeof(buff),stdin);

    sendto(socket_desc,(const char*)buff,strlen(buff),MSG_CONFIRM,(const struct sockaddr*)&server,sizeof(server));

    printf("String send to server");

    int n;
    n = recvfrom(socket_desc,(char*)buff,sizeof(buff),MSG_WAITALL,NULL,NULL);

    buff[n] = '\0';

    printf("Reversed string from server %s \n",buff);

    close(socket_desc);
    return 0;


}
