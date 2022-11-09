#include <stdio.h>
#include <math.h>

int prime(long int num);
long int proper(long int num); 
long int cal(char c, long int start, long int end);

int main(void){
    printf("Intervaly:\n");
    long int start, end;
    char c;

    while (1)
    {
        int r = scanf(" %c %ld %ld",&c,&start,&end);
        
        if(r==EOF){
            break;
        }
        if((start<1 || start>end  || r!=3) || (c!='#' && c!='?')){
            printf("Nespravny vstup.\n");
            return 0;
        }

        printf("Celkem: %ld\n",cal(c,start,end));
    }
    
}

long int proper(long int num){
    long int result = 0;
    if(num == 1){
        return result;
    }
    for(long int i = 2; i <= sqrt(num);i++){
        if(num % i == 0){
            if(i == (num / i)){
                result += i;
            }
            else{
                result += (i + num/i);
            }
        }
    }
    return (result + 1);
}

int prime(long num){
    if(num==1){
        return 0;
    }
    if(num%2==0){
        return 0;
    }
    for (long int i = 3; i <= sqrt(num); i+=2)
    {
        if(num%i==0){
            return 0;
        }
    }
    return 1;
}

long int cal(char c, long int start, long int end){
    long int counter=0;
    for(long int i=start; i<=end;i++){
        if(prime(proper(i))==1 && i!=1){
            if(c=='?')
                printf("%ld\n", i);
            counter+=1;
        }
    }
    return counter;
}