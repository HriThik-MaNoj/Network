#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc,char *argv[]){

	int socket_desc,new_socket,c;
	char message[2000],filename[2000];
	struct sockaddr_in server,client;
	FILE *fp;
	
	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1){
		printf("Error creating socket");
		return 1;
	}
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	if(bind(socket_desc,(struct sockaddr*)&server,sizeof(server)) < 0){

		perror("Bind failed");
		return 1;
	}
	puts("Binding succesfull");
	
	listen(socket_desc,3);
	
	puts("waiting for incoming connection");
	c = sizeof(struct sockaddr_in);
	new_socket = accept(socket_desc,(struct sockaddr*)&client,(socklen_t*)&c);
	
	if(new_socket < 0){

		perror("Accept failed");
		return 1;
	}
	puts("Accept succesfull");

	recv(new_socket,filename,2000,0);
	filename[strlen(filename)] = '\0';
	strcpy(filename,"sample.txt");
	printf("Filename is %s with %lu",filename,strlen(filename));
	
	fp = fopen(filename,"r");
	if(fp == NULL){

		strcpy(message,"FILE NOT FOUND!");
		printf("%s",message);
		send(new_socket,message,strlen(message),0);
	}
	else{

		while(fgets(message,2000,fp)!= NULL){
			printf("%s",message);
			send(new_socket,message,strlen(message),0);
		}
	fclose(fp);
	}
	strcpy(message,"EOF");
	send(new_socket,message,strlen(message),0);
	close(socket_desc);
	return 0;
}
	
