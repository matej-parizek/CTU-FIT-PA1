#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

//return 1 is leap year
//return 0 isnt leap year
int isLeapYear(int y){
    int leap=0;
    if(y%4==0 )
        leap=1;
    if(y%100==0)
        leap=0;
    if(y%400==0)
        leap=1;
    if(y%4000==0)
        leap=0;
    return leap;
}

/*return days in month
@isLeapYear() return 1 if is leap year */
int monthDays(int m,int y){
    if (m==2){
        if(isLeapYear(y)==0)
            return 28;
        else
            return 29;
    }
    if ((m <=7 && m%2==0 && m!=2 && m>0)|| (m>7 && m<=12 &&m%2!=0)){
        return 30;
    }
    if ((m <=7 && m%2!=0 && m!=2 && m>0)|| (m>7 && m<=12 && m%2==0)){
        return 31;
    }
    return 0;
}

/*return number of days until start of year
using @isLeapYear for number of days in leap year*/
long int numberDaysByYear(int y){
    long int days=0;
    for (long int i = 1; i <y ; i++)
    {
        if(isLeapYear(i)==1)
            days+=366;
        else
            days+=365;
    }
    return days;    
}

/*return number of days in the every month int the year
usiing @monthDays returning number of days in the month*/
int numberDayByMonth(int m, int y){
    int days=0;
    for(int i=1; i<m;i++){
        days+=monthDays(i,y);
    }
    return days;
}

//null time for hour
int nullHour(int h){
    int bell = 0;
    for(int i=0;i<=h; i++){
        if(i%12==0)
            bell+=12;
        else
            bell+=i%12;
    }
    return bell;
}
int nullMinute(int m){
    int bell = 4;
    for(int i=0; i<=m; i+=15){
        bell+=i/15;
    }
    return bell;
}
//null time for minutes

//control inputs
int control(int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2){ 
    if(y1>y2|| (m1>m2 && y1==y2) || (m1==m2 && y1==y2 && d1>d2) ||
        (m1==m2 && y1==y2 && d1==d2 && h1>h2) ||
        (m1==m2 && y1==y2 && d1==d2 && i1>i2)){
        return 0;
        }
    if(y1<1600 || y2<1600 || m1<1 || m1>12 || m2<1 || m2>12 ||
        d1<1 || d2<1 || h1>23 || h1<0 || h2>23 || h2<0 
        || i1<0 || i2<0 || i1>59 || i2>59){
        return 0;
    }
    if(d1>monthDays(m1,y1) ||d2>monthDays(m2,y2)){
        return 0;
    }
    return 1;   
}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 ){
    if(control(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0){
        return 0;
    }
    long int days1= (numberDaysByYear(y1)+ numberDayByMonth(m1,y1)+d1);
    long int days2= (numberDaysByYear(y2)+ numberDayByMonth(m2,y2)+d2);
    //number of Sunday in interval
    long long int sunday2=(long long int)(days2/7);
    long long int sunday1 =(long long int)(days1/7);

    long long int bellh1= days1*156 +nullHour(h1) - sunday1*156;
    long long int bellh2= days2*156 + nullHour(h2) - sunday2*156;
    int min=i1/15;
    if (min==0)
    {
        min=4;
    }
    
    long long int bellm1 = days1*240 + h1*10 + nullMinute(i1)-sunday1*240-min ;
    long long int bellm2 = days2*240 + h2*10 + nullMinute(i2)-sunday2*240;
    if(days1%7==0){
        bellm1=days1*240 - (sunday1-1)*240;
        bellh1=days1*156  - (sunday1-1)*156;
    }
    if(days2%7==0){
        bellm2=days2*240 - (sunday2-1)*240;
        bellh2=days2*156  - (sunday2-1)*156;
    }
    if((h1==0 && i1==0)){
        bellh1-=12;
    }
    if((h1==h2 && i1==i2) && days1%7!=0 && days2%7!=0 ){
        bellh1-=12;
    }
    *b1=bellm2 - bellm1;
    *b2=bellh2 - bellh1;
    return 1 ;
  
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2; 
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  1, 18, 45, &b1, &b2 ) == 1
           && b1 == 56
           && b2 == 20 );
  assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  2, 11, 20, &b1, &b2 ) == 1
           && b1 == 106
           && b2 == 65 );
  assert ( bells ( 2022, 10,  2, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 115
           && b2 == 78 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022,  1,  1, 13, 15,
                   2022, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 56861
           && b2 == 36959 );
  assert ( bells ( 2019,  1,  1, 13, 15,
                   2019, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2024,  1,  1, 13, 15,
                   2024, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57341
           && b2 == 37271 );
  assert ( bells ( 1900,  1,  1, 13, 15,
                   1900, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2022, 10,  1,  0,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 124
           && b2 == 90 );
  assert ( bells ( 2022, 10,  1,  0, 15,
                   2022, 10,  1,  0, 25, &b1, &b2 ) == 1
           && b1 == 1
           && b2 == 0 );
  assert ( bells ( 2022, 10,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 11,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 10, 32, 12,  0,
                   2022, 11, 10, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2100,  2, 29, 12,  0,
                   2100,  2, 29, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2000,  2, 29, 12,  0,
                   2000,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2004,  2, 29, 12,  0,
                   2004,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 0
           && b2 == 0 );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */