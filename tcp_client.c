#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
// client code

int main(){

	int socket_desc;
	int k;
	char buff[100];
	

	struct sockaddr_in server;
	
	
	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1){
		
		printf("Error creating socket ");
		return 1;
	}
	
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(3003);

	k = connect(socket_desc,(struct sockaddr*)&server,sizeof(server));
	if(k < 0){
		
		printf("Error connecting");
		return 1;
	}
	puts("connected");
	
	while(1){
		
		printf("Enter the message to be sent to the server,(enter exit to quit)");
		fgets(buff,sizeof(buff),stdin);
		if(send(socket_desc,buff,strlen(buff) ,0) < 0){
			printf("Error sending");
			return 1;
		}
		if(strcmp(buff,"exit") == 0){

			printf("Exiting the program ");
			break;
		}
		if(recv(socket_desc,buff,sizeof(buff),0) < 0){

			printf("Error in recieving");
			return 1;
		}
		printf("message recieved from server :%s",buff);
	}
	close(socket_desc);
	return 0;
}

