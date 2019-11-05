/**
* file : lcd12864.case
* description:displayy some characters and numbers in the lcd12864
*/

#include<stdio.h>
#include<wiringPi.h>


// signal port
#define     CS
#define     RS
#define     RD
#define     WD
#define     RES

// 8bit data port
#define     D0
#define     D1
#define     D2
#define     D3
#define     D4
#define     D5
#define     D6
#define     D7


/*
* 8bit bus write
*/
void bus_write(uchar data)
{
    char array[10];
    int i=0;
    for(i=0;i<8;i++)
    {
        array[i] = data%2;
        data = data>>1;
    }
    digitalWrite(D0,array[0]);
    digitalWrite(D1,array[1]);
    digitalWrite(D2,array[2]);
    digitalWrite(D3,array[3]);
    digitalWrite(D4,array[4]);
    digitalWrite(D5,array[5]);
    digitalWrite(D6,array[6]);
    digitalWrite(D7,array[7]);
}

/*
* LCD12864 write command
*/
void lcd12864_write_com(uchar com)
{
    digitalWrite(RS,0); // write command
    digitalWrite(RD,1);
    digitalWrite(WD,0); // write operator
    delay(5);
    bus_write(com);
    delay(5);
    digitalWrite(WD,1);
}

/*
* LCD12864 write data
*/
void lcd12864_write_data(uchar data)
{
    digitalWrite(RS,1); // write date
    digitalWrite(RD,1);
    digitalWrite(WD,0);
    delay(5);
    bus_write(data);
    delay(5);
    digitalWrite(WD,1);
}

/**
* LCD12864 init configuration
*/
void lcd12864_init()
{
    digitalWrite(RES,0);   // set res low
    delay(10);
    digitalWrite(RES,1);  // set res high
    delay(5);
    digitalWrite(CS,0);  // chipselect enable

    // set register

}

/*
* main function
*/
int mian()
{
    // set gpio mode is wringpi
    wiringPiSetup();
    // set gpio is OUTPUT
    pinMode(RES,OUTPUT);
    pinMode(RS,OUTPUT);
    pinMode(CS,OUTPUT);
    pinMode(RD,OUTPUT);
    pinMode(WD,OUTPUT);

    pinMode(D0,OUTPUT);
    pinMode(D1,OUTPUT);
    pinMode(D2,OUTPUT);
    pinMode(D3,OUTPUT);
    pinMode(D4,OUTPUT);
    pinMode(D5,OUTPUT);
    pinMode(D6,OUTPUT);
    pinMode(D7,OUTPUT);

    lcd12864_init();
    
    return 0;
}
