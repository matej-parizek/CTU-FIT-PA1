#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define StartMax 10


typedef struct{
    double x;
    double y;
    char plane[201];
}FLY;
typedef struct{
    double lenght;
    char plane1[201];
    char plane2[201];
}DISTANCE;

void addDis(DISTANCE *dist, const char name1[], const char name2[], double size){
    strcpy(dist->plane1,name1);
    strcpy(dist->plane2,name2);
    
    dist->lenght=size;
}

double sizeDis(FLY number1, FLY number2){
    double n1 = (pow(number1.x - number2.x,2));
    double n2 = (pow(number1.y - number2.y,2));
    return n1+n2;
}

int findMin(FLY flyed[],DISTANCE dist[],int counter){
    double min = sizeDis(flyed[0], flyed[1]);
    int count=0, max = StartMax*StartMax;
    for (int i = 0; i < counter-1; i++){
        for (int j = i+1; j < counter; j++)
        {
            double lenght = sizeDis(flyed[i],flyed[j]);
            if(count==max){
                max=max*20;
                dist=(DISTANCE *)realloc(dist,sizeof(DISTANCE)*max);
            } 
            if(lenght == min){
                addDis(&dist[count],flyed[i].plane, flyed[j].plane,min);
                count++;
            }
            if(lenght<min){
                min=lenght;
                count =0;
                free(dist);
                dist=(DISTANCE *)malloc(sizeof(DISTANCE)*StartMax*StartMax);
            }
        }
    }
    return count;    
}

int input(FLY flyed[ ],int *counter){
    long int max=StartMax;
    while (1)
    {
        if(*counter == max){
            max=max*20;
            flyed=(FLY *)realloc(flyed,sizeof(FLY)*max);
        }
        int r=scanf("%lf , %lf : %199s", &(flyed[*counter].x), &(flyed[*counter].y),flyed[*counter].plane);
        if (r==EOF)
            break;
        if(r!=3){
            return 1;   
        }
        *counter+=1;
    }
    return 0;
}

int main(void){
    int counter=0;
    FLY *flyed=(FLY *)malloc(sizeof(FLY)*StartMax);
    DISTANCE *dist=(DISTANCE *)malloc(sizeof(DISTANCE)*StartMax*StartMax);
    printf("Pozice letadel:\n");
    if(input(flyed,&counter)){
        printf("Nespravny vstup.\n");
        free(flyed);
        free(dist);
        return 0;
    }
    int count =findMin(flyed,dist, counter);
    printf("Vzdalenost nejblizsich letadel: %lf\n",dist[0].lenght);
    printf("Nalezenych dvojic: %d\n", count);
    for (int i = 0; i < count; i++)
    {
        printf("%s - %s", dist[i].plane1, dist[i].plane2);
    }
    free(flyed);
    free(dist);
    return count;
}