#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define StartMax 8


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

int input(FLY **flyed,int *counter){
    int max=StartMax;
    while (1)
    {
        if(max==*counter){
            max=max*2;
            *flyed=(FLY *)realloc(*flyed,max*sizeof(FLY));
        }
        int r= scanf("%lf , %lf : %199s",&flyed[0][*counter].x,&flyed[0][*counter].y,flyed[0][*counter].plane);
        if(r!=3)
            return 1;
        if(r==EOF)
            return 0;
        *counter+=1;
    }
    
    return 0;
}

int main(void){
    int counter=0;
    FLY *flyed=(FLY*)malloc(sizeof(FLY)*StartMax);
    DISTANCE *dist=(DISTANCE *)malloc(sizeof(DISTANCE)*StartMax*StartMax);
    
    if(input(&flyed,&counter) || counter<2);


    free(flyed);
    free(dist);
    return 0;
}