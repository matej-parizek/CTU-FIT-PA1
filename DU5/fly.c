#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define StartMax 6


typedef struct{
    double x;
    double y;
    char plane[200];
}FLY;

typedef struct{
    double minimum;
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
        if(r==EOF)
            return 0;
        if(r!=3)
            return 1;
        *counter+=1;
    }
    
    return 0;
}

void addDis(DISTANCE * disc, FLY  name1, FLY name2){
    strcpy(disc->plane1,name1.plane);
    strcpy(disc->plane2,name2.plane);
    double n1 = (pow(name1.x - name2.x,2));
    double n2 = (pow(name1.y - name2.y,2));
    disc->minimum=sqrt(n1+n2);
    return;
}
double sizeDis(FLY number1, FLY number2){
    double n1 = (pow(number1.x - number2.x,2));
    double n2 = (pow(number1.y - number2.y,2));
    return sqrt(n1+n2);
}

int findMin(FLY *flyed,DISTANCE **dist,int counter){
    double min = sizeDis(flyed[0],flyed[1]);
    int max=StartMax;
    int count=0;
    
    for(int i=0; i<counter-1; i++){
        for(int j = i+1; j < counter; j++)
        {
            long int lenght=sizeDis(flyed[i],flyed[j]);
            if(max==count){
                max*=2;
                *dist=(DISTANCE*)realloc(*dist,sizeof(DISTANCE)*max);
            }
            if(lenght < min){
                count=0;
                min=lenght;
            }
            if(min==lenght){
                addDis(&dist[0][count],flyed[i],flyed[j]);
                count+=1;
            }
        }
        
    }
    return count;
}

void print(DISTANCE *flyed,int counter){
    for (int i = 0; i < counter; i++){
        printf("%s - %s\n",flyed[i].plane1,flyed[i].plane2);    
    }
    return;
}

int main(void){
    int counter=0;
    FLY *flyed=(FLY*)malloc(sizeof(FLY)*StartMax);
    DISTANCE *dist=(DISTANCE *)malloc(sizeof(DISTANCE)*StartMax);
    printf("Pozice letadel:\n");
    if(input(&flyed,&counter)==1 || counter<2){
        printf("Nespravny vstup.\n");
        free(flyed);
        free(dist);
        return 0;
    }
    int count = findMin(flyed,&dist,counter);
    printf("Vzdalenost nejblizsich letadel: %lf\n",dist[0].minimum);
    printf("Nalezenych dvojic: %d\n",count);
    print(dist,count);
    free(flyed);
    free(dist);
    return 0;
}