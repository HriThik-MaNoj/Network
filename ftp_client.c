#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){

	int socket_desc;
	char message[200],filename[200];
	struct sockaddr_in server;
	
	FILE *fp;
	
	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1){
		printf("Error creating socket");
		return 1;
	}
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	if(connect(socket_desc,(struct sockaddr*)&server,sizeof(server)) < 0){
		
		puts("Error connecting ");
		return 1;
	}
	puts("Connected");
	
	strcpy(filename,"sample.txt");
	printf("File name is %s with %lu",filename,strlen(filename));
	
	fp = fopen("backup","w");
	
	if(fp == NULL){
		printf("Error in opening file");
		return 1;
	}
	while(recv(socket_desc,message,2000,0)){

		if(strcmp(filename,"EOF") == 0){

			break;
		}
		else{

			fprintf(fp,"%s",message);
		memset(message,0,sizeof(message));
		}
	}
	fclose(fp);
	close(socket_desc);
	return 0;



}
