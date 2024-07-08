#include <stdio.h>

int main(){

    int i,j,k,nodes,count;
    int costmat[i][j];
    struct node{

        unsigned dist[20];
        unsigned from[20];
    }rt[20];

    printf("Enter the number of nodes : ");
    scanf("%d",&nodes);

    printf("Enter the elements for the cost matrix : ");
    for(i = 0; i < nodes; i++){

        for(j = 0; j < nodes; j++){

            scanf("%d",&costmat[i][j]);
            costmat[i][i] = 0;
            rt[i].dist[j] = costmat[i][j];
            rt[i].from[j] = j;
        }
    }

    do{
        count = 0;
        for(i = 0; i < nodes; i++){

            for(j = 0; j < nodes; j++){

                for(k = 0; k < nodes; k++){

                    if(rt[i].dist[j] > costmat[i][k] + rt[k].dist[j]){

                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    }while(count != 0);

    for(i = 0; i < nodes;i++){
        printf("\n\nFor router %d\n",i+1);

            for(j = 0 ; j < nodes;j++){

                printf("from %d via %d Distance %d",j+1,rt[i].from[j]+1,rt[i].dist[j]);
            }
        
    }
    printf("\n");
    return 0;
}