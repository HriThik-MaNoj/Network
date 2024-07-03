//server
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>

int main(){
	int socket_desc,new_socket_desc;
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[100];
	
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc==-1)
	{
		printf("error in creating socket");
		return 1;
	}
	
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_family=AF_INET;
	server.sin_port=3003;
	
	if(bind(socket_desc,(struct sockaddr*)&server,sizeof(server))<0)
	{
		printf("connection failed");
		return 1;
	}
	
	if(listen(socket_desc,5)<0)
	{
		printf("error in listening");
		return 1;
	}
	
	len=sizeof(client);
	new_socket_desc=accept(socket_desc,(struct sockaddr*)&client,&len);
	if(new_socket_desc==-1)
	{
		printf("accept failed");
		return 1;
	}
	
	while(1)
	{
	if(recv(new_socket_desc,buff,sizeof(buff),0)<0)
	{
	printf("error in recieving");
	return 1;
	}
	printf("message from client is %s",buff);
	
	if(strcmp(buff,"exit\n")==0)
	{
		printf("exit from the program");
		break;
	}
	
	printf("enter data to client(enter exit to quit)");
	fgets(buff,sizeof(buff),stdin);
	
	if(send(new_socket_desc,buff,strlen(buff),0)<0)
	{
		printf("error in sending");
		return 1;
	}
	
	}
	close(socket_desc);
	close(new_socket_desc);
	return 0;
}					
