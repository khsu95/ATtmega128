#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

unsigned char count;
unsigned char port;

void Init_Timer2(void){
   TCCR2=(1<<WGM21)|(1<<CS21);//CTC,
   OCR2=10;//5.5kHz
   TIMSK|=(1<<OCIE2);
   DDRA=0xff;
   SREG|=0x80;
}

void Init_Timer0(void){
    TIMSK&=(~(1<<OCIE0)|(1<<TOIE0));//Activate Interrupt for T/C0
    ASSR=1<<AS0;//External Clk
    OCR0=204;//80% Duty
    TCCR0=(1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS01);//PWM, OC2 Toggle, clk/8 prescalor
    while(!((TCCR0)&(1<<WGM21)))//Delay
    TIMSK|=(1<<OCIE0);
    DDRB=0xff;

}

ISR(TIMER2_COMP_vect){
    if(count==5){//5.5kHz->1.1kHz
        if(port==0x00)   port=0xff;
        else port=0x00;
        count=0;
    }
    count++;
}

int main(){
    count=0;
    port=0x00;
    Init_Timer2();
    Init_Timer0();
    while (1)   PORTA=port;
   return 0;
 }
