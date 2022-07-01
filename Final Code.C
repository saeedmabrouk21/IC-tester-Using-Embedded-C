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
int flag=0;





// Declare your global variables here
unsigned char UART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0);/* Wait till data is received */
	return(UDR);			/* Return the byte*/
}

void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
	UDR = ch ;
}

void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_TxChar(str[j]);	
		j++;
	}
}

void ic_7430(){
    char i;
    flag = 0;

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
        UART_SendString("7430");  
        //delay_ms(1000);

    }
        

}



void ic_7432(){
    int i;
    flag = 0;

    DDRA = 0b01100011 ;
    DDRB = 0b00000110 ; 
    DDRD = 0b00110000 ;
    DDRC = 0b11000000 ;    
    
    D2=1;
    
    /*delay_ms(300);
    for (;PIND.2 == 1;);*/ 
    delay_ms(100);
    
    for(i=0;i<=3;i++){ 
        A5=(int)i%2;
        A6=(int)i/2;  
        D4=(int)i%2;
        D5=(int)i/2; 
        C6=(int)i%2;
        C7=(int)i/2;
        B1=(int)i%2;
        B2=(int)i/2;  
        
        delay_ms(100);    
        
        if( PINA.7!=(PINA.5|PINA.6)){ 
           flag=1;  
           break; 
        }   
        if(PIND.6 != (PIND.4||PIND.5)){  
          flag = 1 ;
          break; 
       }
        if(PINB.0 != (PINC.6|PINC.7)){  
          flag = 1 ;
          break;
        }
        if(PINB.3 != (PINB.2|PINB.1)){  
          flag = 1 ; 
          break;
        }        
    }  
        

    if (!flag){       
      A1=1;
      A0=0;   
      UART_SendString("7432");
      //delay_ms(1000);
    } 
}



void ic_7433(){
    int i;
    flag = 0;

    // prepare output pins  

    DDRA = 0b11000011 ;
    DDRD = 0b01100000 ;
    DDRC = 0b10000000 ;
    DDRB = 0b00001101 ;
    D2=1;
    A5=D4=C6=B1=1;

    //delay_ms(300);
    //for (;PIND.2 == 1;);
    delay_ms(100);

    for(i=0;i<=3;i++){
        //
        A6=(int)i%2;
        A7=(int)i/2;
        D5=(int)i%2;
        D6=(int)i/2;
        C7=(int)i%2;
        B0=(int)i/2;
        B2=(int)i%2;
        B3=(int)i/2;
        delay_ms(100);

        if(PINA.5 == (PINA.7||PINA.6)){
            flag=1;
            break;
        }
        if(PIND.4 == (PIND.6||PIND.5)){
            flag=1;
            break;
        }
        if(PINC.6 == (PINC.7||PINB.0)){
            flag=1;
            break;
        }
        if(PINB.1 == (PINB.2||PINB.3)){
            flag=1;
            break;
        }

    }
    if((PINA.5 | PIND.4 |PINC.6 |PINB.1 ) == 1){
        flag=1;
    }
    if(!flag){
        A1=1;
        A0=0;  
        UART_SendString("7433");
        //delay_ms(1000);
    }
}



void ic_7434()
{
  flag = 0;

  // prepare output pins
  DDRA = 0b10100011 ;
  DDRB = 0b00000101 ;
  DDRC = 0b01000000 ;
  DDRD = 0b00100000 ;


  D2 = 1;
  //delay_ms(300);
  //for (; PIND.2 == 1;);      
  delay_ms(100);

    //   
    A5=A7=D5=C6=B0=B2=1;
    delay_ms(100);
    //
    if ((PINA.6 == 0) | (PIND.4 == 0) | (PIND.6 == 0) | (PINC.7 == 0) | (PINB.3 == 0) | (PINB.1 ==0) )
        {
            A0 = 1;
            A1 = 0;
            delay_ms(500); 
            //A0=0;
            flag = 1;
        }
    A5=A7=D5=C6=B0=B2=0;
    delay_ms(100);
                
    if ((!flag) && ( (PINA.6 ==1) | (PIND.4 ==1) | (PIND.6 ==1) | (PINC.7 ==1) | (PINB.3 ==1) | (PINB.1 ==1) ))
        {
                    
            A0 = 1;
            A1 = 0;
            delay_ms(500); 
            //A0=0;
            flag = 1;
        }
    delay_ms(100);       
    if(!flag)
        {
            A1 = 1;
            A0 = 0;
            //delay_ms(1000);
            UART_SendString("7434");

        }
}


void ic_7437(){
    int i;
    flag = 0;

    // prepare output pins
    DDRA=0b01100011 ;
    DDRB=0b00000110 ;
    DDRC=0b11000000 ;
    DDRD=0b00110000 ;

    // prepare input pins     
    D2=1;
    delay_ms(300);
    for (;PIND.2 == 1;);
    delay_ms(300);    
    
    for(i=0;i<=3;i++){
        A5=(int)i%2;
        A6=(int)i/2;
        D4=(int)i%2;
        D5=(int)i/2;
        C6=(int)i%2;
        C7=(int)i/2;
        B1=(int)i%2;
        B2=(int)i/2;
        delay_ms(100);
        if(PINA.7 != (~PINA.5|~PINA.6)){
            /*A0=1;
            A1=0;
            delay_ms(500); 
            A0=0;*/
            flag=1;
            break;
        }
        if(PIND.6 != (~PIND.4|~PIND.5)){
            /*A0=1;
            A1=0;
            delay_ms(500);  
            A0=0;  */
            flag=1;
            break;
        }
        if(PINB.0 != (~PINC.7|~PINC.6)){
           /* A0=1;
            A1=0;
            delay_ms(500);   
            A0=0;*/
            flag=1;
            break;
        }
        if(PINB.3 != (~PINB.2|~PINB.1)){
            /*A0=1;
            A1=0;
            delay_ms(500); */
            flag=1;  
            //A0=0;
            break;
        }
    }
    if(!flag){
        A1=1;
        A0=0;
        //delay_ms(1000); 
        UART_SendString("7437");

    }

}



void ic_7438(){
    int i;
    flag = 0;

    // prepare output pins
    DDRA=0b01100011 ;
    DDRB=0b00000110 ;
    DDRC=0b11000000 ;
    DDRD=0b00110000 ;
    A7=D6=B3=B0=1;


    D2=1;
    //delay_ms(300);
    //for (;PIND.2 == 1;);
    delay_ms(100);  
    
    for(i=0;i<=3;i++){

        A5=(int)i%2;
        A6=(int)i/2;
        D4=(int)i%2;
        D5=(int)i/2;
        C6=(int)i%2;
        C7=(int)i/2;
        B1=(int)i%2;
        B2=(int)i/2;
        delay_ms(100);

        if(PINA.7 != (~PINA.5|~PINA.6)){
            /*A0=1;
            A1=0;
            delay_ms(500);  
            A0=0;*/
            flag=1;
            break;
        }
        if(PIND.6 != (~PIND.4|~PIND.5)){
            /*A0=1;
            A1=0;
            delay_ms(500);  
            A0=0;*/
            flag=1;
            break;
        }
        if(PINB.0 != (~PINC.7|~PINC.6)){
            /*A0=1;
            A1=0;
            delay_ms(500);  
            A0=0;*/
            flag=1;
            break;
        }
        if(PINB.3 != (~PINB.2|~PINB.1)){
            /*A0=1;
            A1=0;
            delay_ms(500);*/
            flag=1;
            //A0=0;
            break;
        }


    }
    A7=D6=B3=B0=0;
    if(PINA.7==1 | PIND.6==1 | PINB.0==1 | PINB.3 ==1){
        /*A0=1;
        A1=0;
        delay_ms(500);  
        A0=0;*/
        flag=1;

    }
    if(!flag){
        A1=1;
        A0=0;     
        UART_SendString("7438");
        //delay_ms(1000);

    }
}


void main() {

          
    UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
    UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
    UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
    UBRRH=0x00;
    UBRRL=0x47;

    // Analog Comparator initialization
    // Analog Comparator: Off
    // The Analog Comparator's positive input is
    // connected to the AIN0 pin
    // The Analog Comparator's negative input is
    // connected to the AIN1 pin
    ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
    SFIOR=(0<<ACME);

    // ADC initialization
    // ADC disabled
    ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

    // SPI initialization
    // SPI disabled
    SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

    // TWI initialization
    // TWI disabled
    TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);
               
       
    ic_7437();
    if(flag==1)
       ic_7438();  
    if(flag==1)
       ic_7430();
    if(flag==1)
       ic_7432(); 
    if(flag==1)
       ic_7433();   
    if(flag==1)
       ic_7434();
       
    if (flag==1)
        UART_SendString("Not Found");
}
