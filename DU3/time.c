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

/**
 * return days in month
 * @param[in] 
 * @return number of day in month
*/
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

void calculation (int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2, long long *b1, long long *b2){
    

    long long int days1= (numberDaysByYear(y1)+ numberDayByMonth(m1,y1)+d1);
    long long int days2= (numberDaysByYear(y2)+ numberDayByMonth(m2,y2)+d2);
    //sundays until the day
    long long int sunday2=((days2-1)/7);
    long long int sunday1 =((days1-1)/7);

    long long int plusHour= (days2-1)*156 + nullHour(h2)-sunday2*156;
    long long int plusMinutes= (days2 -1)*240 +(h2)*10 + nullMinute(i2)-sunday2*240;
    if(days2%7==0){
        plusHour=(days2-1)*156 -sunday2*156;
        plusMinutes=(days2 -1)*240 - sunday2*240;
    } 
    int hour=h1%12;
    if(hour==0)
        hour=12;
    if(i1!=0)
        hour=0;
    long long  int minusHour = nullHour(h1)-sunday1*156-hour;
    
    int minute=i1/15;
    if(minute==0)
        minute=4;
    if(i1%15!=0)
        minute=0;
    long long int minusMinutes=(h1)*10 + nullMinute(i1)-sunday1*240 - minute;
    if(days1%7==0){
        minusHour=-sunday1*156;
        minusMinutes=-sunday1*240;
    }
    *b2=plusHour - ((days1-1)*156 +minusHour);
    *b1=plusMinutes -((days1-1)*240 + minusMinutes);
    return;
}

/**
 * @todo function for sum the bells
 * 
*/
int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 ){
    if(control(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0){
        return 0;
    }
    calculation(y1, m1, d1, h1,i1,
            y2,m2, d2,h2, i2,
            b1, b2 );
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
  assert ( bells ( 2000, 12, 28, 0, 0, 2000, 12, 28, 0, 0, &b1, &b2 )==1 
            && b1==4
            &&b2==12);
  assert(bells ( 1929, 1, 8, 13, 19, 2079845, 9, 23, 15, 21, &b1, &b2 )==1 
            && b1==156125411780
            && b2==101481517649);
    
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */