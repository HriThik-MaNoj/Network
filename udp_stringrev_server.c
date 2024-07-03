#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void reverseString(char* str){

    int length = strlen(str);
    int start = 0;
    int end  = length - 1;
    
    while(start < end){

        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

int main(){

    int socket_desc;
    char buff[1024];
    struct sockaddr_in server,client;

    socket_desc = socket(AF_INET,SOCK_DGRAM,0);
    if(socket_desc == -1){

        printf("Error creating socket");
        return 1;
    }

    memset(&server,0,sizeof(server));
    memset(&client,0,sizeof(client));

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port= htons(8080);


    if(bind(socket_desc,(const struct sockaddr*)&server,sizeof(server)) < 0){

        printf("Bind failed");


    }

    int n,len;
    len = sizeof(client);
    n = recvfrom(socket_desc,(char*)buff,sizeof(buff),MSG_WAITALL,(struct sockaddr*)&client,&len);

    buff[n] = '\0';

    printf("Original string from client : %s\n",buff);

    reverseString(buff);

    sendto(socket_desc,(const char*)buff,strlen(buff),MSG_CONFIRM,(const struct sockaddr*)&client,len);
    printf("Reversed string send to client \n");

    return 0;


    
}
