/**
* file : lcd12864.case
* description:displayy some characters and numbers in the lcd12864
*/

#include<stdio.h>
#include<wiringPi.h>


// signal port
#define     CS  24
#define     RS  7
#define     RD  6
#define     WD  0
#define     RES 25

// 8bit data port
#define     D0  1
#define     D1  2
#define     D2  3
#define     D3  4
#define     D4  5
#define     D5  21
#define     D6  22
#define     D7  23


/*
* 8bit bus write
*/
void bus_write(unsigned char data)
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
void lcd12864_write_com(unsigned char com)
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
void lcd12864_write_data(unsigned char data)
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
    lcd12864_write_com(0xe2);//internal reset
    lcd12864_write_com(0xa0); //ADC select normal mode
    lcd12864_write_com(0xa6); //Display normal
    lcd12864_write_com(0xa0); //LCD bias set :1/9 bias
    lcd12864_write_com(0xc0); // Common output mode select :normal
    lcd12864_write_com(0x2f); //Power control set
    lcd12864_write_com(0x27);//V0 voltage regulator internal resistor ratio
    lcd12864_write_com(0x81);
    lcd12864_write_com(0x0f); // set the V0 output voltage electronic volume
    lcd12864_write_com(0xac); //close static indicator
    lcd12864_write_com(0xf8); // booster ratio select mode set
    lcd12864_write_com(0x01); // booster ratio register set 5X
    // set display location
    lcd12864_write_com(0x01); // line 1
    lcd12864_write_com(0xb0); // page 0
    lcd12864_write_com(0x10); // column address : High 4 bits
    lcd12864_write_com(0x00); // column address : low 4 bits

    lcd12864_write_com(0xaf);// display on
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

    while(1)
    {
        lcd12864_write_data("a");
    }

    return 0;
}
