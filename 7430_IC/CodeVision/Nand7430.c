#define F_CPU 11000000UL
#include <mega16a.h>
#include <io.h>
#include <stdint.h>
#include <delay.h>
#include <stdio.h>

#define A0  PORTA.0
#define A1  PORTA.1
#define A5  PORTA.5
#define A6  PORTA.6
#define A7  PORTA.7
#define D2  PORTD.2
#define D4  PORTD.4
#define D5  PORTD.5
#define D6  PORTD.6
#define C6  PORTC.6
#define C7  PORTC.7
#define B0  PORTB.0
#define B1  PORTB.1
#define B2  PORTB.2
#define B3  PORTB.3




void main(){


    char i;
    int flag = 0; 
    D2=1;
    for (;PIND.2 ==1;);

    // prepare output pins
    DDRA=0b11100011 ;
    DDRB=0b00000001 ;
    DDRC=0b10000000 ;
    DDRD=0b01110000 ;
    D2=1;
    A0=0;
    A1=0;
    /*delay_ms(300);
    for (;PIND.2 ==1;);*/
    delay_ms(100);
    // prepare input pins     
    PORTA &= 0b00011111;
    PORTB &= 0b11111110;
    PORTC &= 0b01111111;
    PORTD &= 0b10001111;
    B3=0;
    //B1=1; 
    //B2=1;
    if ( (PINB & 0b00001000) == 0){
        flag = 1;      
    }  
    
    for (i = 0 ; !flag && i < 8 ; i++){
        if (i==0){
            PORTB |= 0b00000001;
            PORTA &= 0b00011111;
            PORTC &= 0b01111111;
            PORTD &= 0b10001111;
            delay_ms(200);
        }

        else if (i==1){
            PORTA &= 0b00011111;
            PORTB &= 0b11111110;
            PORTC |= 0b10000000;
            PORTD &= 0b10001111;
            delay_ms(200);
        }
        else if (i < 5) {
            PORTA &= 0b00011111;
            PORTA |= 1 << 5 + i - 2 ;
            PORTB &= 0b11111110;
            PORTC &= 0b01111111;
            PORTD &= 0b10001111;
            delay_ms(200);
        }
        else{
            PORTA &= 0b00011111;
            PORTB &= 0b11111110;
            PORTC &= 0b01111111;
            PORTD &= 0b10001111;
            PORTD |= 1 << 4 + i - 2 ;
            delay_ms(200);
        }
        delay_ms(50);
        if ( (PINB & 0b00001000) == 0x00)
        {
            flag =1;
            break;
        }

    }
    PORTA |= 0b11100000;
    PORTB |= 0b00000001;
    PORTC |= 0b10000000;
    PORTD |= 0b01110000;
    delay_ms(100);

    if( (PINB.3 ==1 && flag==0 )){
        flag =1;  
    }   

    if(!flag){
        A1=1;
        A0=0; 

    }else{
      A1=0;
      A0=1;
    } 
    while (1);        
}