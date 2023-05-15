#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define F_CU 16000000UL
#define UBRR_VAL 103
void init_uart(uint16_t ubrr);
void uart_tx(uint8_t data);
uint8_t uart_rx();
int main(void){

uint8_t rx=0;
DDRB=0xff;
PORTB &=~(1<<0);
 init_uart(UBRR_VAL);
 
 uart_tx('%');
 while(1){
rx=  uart_rx();
switch (rx)
{
case '1':
  //turn on led
  PORTB|=(1<<0);
  PORTB &=~(1<<1);

  break;
case '0':
  //turn off led
  PORTB &=~(1<<0);
  PORTB|=(1<<1);

  break;
default:
  break;
}
 }
}





void init_uart(uint16_t ubrr){
  UBRRH=(uint8_t)(ubrr>>8); //casting 8 bits 
  UBRRL=(uint8_t) ubrr;
  UCSRB=(1<<RXEN|(1<<TXEN)); // to activate transmit and receiveing moods
  UCSRC= (1<<UCSZ0)|(1<<UCSZ1); //8 bit serial communication

}

void uart_tx(uint8_t data){

  while(!(UCSRA&(1<<UDRE)));  // UDRE is a flag if it is 1 it means the reg is empty but the condition says :loop as long as udr is not empty
  UDR=data;//udr holds the data to be transmitted
}

uint8_t uart_rx(){
  while(!(UCSRA&(1<<RXC)));
  return UDR;
}


