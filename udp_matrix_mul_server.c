#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>


void matrix_mul(int result[10][10],int matrix1[10][10],int matrix2[10][10],int rows1,int cols1,int rows2,int cols2){
   for(int i = 0; i < rows1; ++i){
        for(int j = 0; j < cols2; ++j){

            result[i][j] = 0;
            for(int k = 0; k < cols1; ++k){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }

    
   }
}

void print_matrix(int matrix[10][10],int rows,int cols){
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){

    int socket_desc;
    struct sockaddr_in server,client;
    int matrix1[10][10],matrix2[10][10],result[10][10];
    char buff[1024];

    socket_desc = socket(AF_INET,SOCK_DGRAM,0);
    if(socket_desc < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

   if( bind(socket_desc,(struct sockaddr*)&server,sizeof(server)) < 0){
    printf("Couldn't bind to the port\n");
    return -1;
   }
   printf("Done with binding\n");

   while(1){

    socklen_t len = sizeof(client);
    ssize_t data_size = recvfrom(socket_desc,matrix1,sizeof(matrix1),0,(struct sockaddr*)&client,&len);
    if(data_size < 0){
        printf("Couldn't receive\n");
        return -1;
    }
    data_size = recvfrom(socket_desc,matrix2,sizeof(matrix2),0,(struct sockaddr*)&client,&len);
    if(data_size < 0){
        printf("Couldn't receive\n");
        return -1;
    }

    int rows1 = matrix1[0][0];
    int cols1 = matrix1[0][1];
    int rows2 = matrix2[0][0];
    int cols2 = matrix2[0][1];

    matrix_mul(result,matrix1+1,matrix2+1,rows1,cols1,rows2,cols2);
    sendto(socket_desc,result,sizeof(result),0,(struct sockaddr*)&client,len);

    printf("matrix1 :\n");
    print_matrix(matrix1+1,rows1,cols1);
    printf("matrix2 :\n");
    print_matrix(matrix2+1,rows2,cols2);
    printf("result :\n");
    print_matrix(result,rows1,cols2);

    printf("\n......................................\n");
   }
   close(socket_desc);
   return 0;
}