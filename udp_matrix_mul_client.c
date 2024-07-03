#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>

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
    struct sockaddr_in server;
    int matrix1[10][10],matrix2[10][10],result[10][10];
    
    char buff[1024];

    socket_desc = socket(AF_INET,SOCK_DGRAM,0);
    if(socket_desc < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    
    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("Socket created successfully\n");

    printf("Enter the dimension of the matrix1: ");
    scanf("%d%d",&matrix1[0][0],&matrix1[0][1]);
    printf("Enter the dimension of the matrix2: ");
    scanf("%d%d",&matrix2[0][0],&matrix2[0][1]);

    printf("Enter the elements of the matrix1: ");
    for(int i = 0; i < matrix1[0][0]; ++i){
        for(int j = 0; j < matrix1[0][1]; ++j){
            scanf("%d",&matrix1[i+1][j]);
        }
    }

    printf("Enter the elements of the matrix2: ");
    for(int i = 0; i < matrix2[0][0]; ++i){
        for(int j = 0; j < matrix2[0][1]; ++j){
            scanf("%d",&matrix2[i+1][j]);
        }
    }

    sendto(socket_desc,matrix1,sizeof(matrix1),0,(struct sockaddr*)&server,sizeof(server));
    sendto(socket_desc,matrix2,sizeof(matrix2),0,(struct sockaddr*)&server,sizeof(server));

    ssize_t data_size = recvfrom(socket_desc,result,sizeof(result),0,NULL,NULL);
    printf("\n Matrix 1 :\n");
    print_matrix(matrix1+1,matrix1[0][0],matrix1[0][1]);
    printf("\n Matrix 2 :\n");
    print_matrix(matrix2+1,matrix2[0][0],matrix2[0][1]);
    printf("\n Result :\n");
    print_matrix(result,matrix1[0][0],matrix2[0][1]);
    printf("\n......................................\n");
    close(socket_desc);
    return 0;
}