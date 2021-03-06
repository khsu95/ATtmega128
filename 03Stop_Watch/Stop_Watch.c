#define L_Control PORTA
#define L_Byte PORTC
#define Interrupt PORTD

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include<util/delay.h>
#include<stdio.h>

volatile unsigned char start=0, pause=0;
unsigned int cnt=0,msec=0,sec=0,min=0;

void Init_Timer2(void);
void Init_Switch();
void Init_LCD();
void getTime(char* str);
void L_Cmd(int command);
void L_Data(char str);
void L_Str(char* str);

int main(){
    char _Time[16]={0};
    DDRA=0xff;
    DDRB=0xff;

    SREG=0x00;
    Init_Timer2();
    Init_Switch();
    Init_LCD();
    SREG=0x80;

    while(1){
        if(start==1){
            getTime(_Time);
            L_Str(_Time);
            _delay_ms(1);
        }
    }
}

void Init_Timer2(void){
   TCCR2|=(1<<WGM21)|(1<<COM20)|(1<<CS20);//CTC, 8prescale
   OCR2=100;//100us
   TIMSK=(1<<OCIE2);
}

void Init_Switch(){
    EICRA=0xff;
    EIMSK=0x0f;
}

void Init_LCD(){
    L_Cmd(0x30);//Set 1line 8bit 5*7dots 
    L_Cmd(0x01);//Clear
    L_Cmd(0x80);//Set DDRAM Address or Coursor Poisition on display
    L_Cmd(0x0c);//Display on, Coursor off
    L_Cmd(0x06);//Entry Mode
}

ISR(TIMER2_COMP_vect){
    cnt++;
    if(cnt==10){//50us*20=1ms
        cnt=0;
        msec+=1;
        if(msec>=999){
            sec++;
            msec=0;
        }
        if(sec>=60){
            min++;
            sec=0;
        }
        if(min>9)
            min=0;
    }    
}

ISR(INT0_vect){
    if(start==0){
        start=1;
        pause=0;
    }
    else{
        if(pause==1){
            pause=0;
            TIMSK&=~(1<<OCIE2);
        }
        else{
            pause=1;
            TIMSK|=(1<<OCIE2);
        }
    }
}

ISR(INT1_vect){
    L_Cmd(0x01);
    start=0;
    min=0;sec=0;msec=0;
}

void getTime(char* str){
    sprintf(str,"%d:%02d.%03d",min,sec,msec);
}

void L_Cmd(int command){
    L_Byte=command;
    L_Control=0x04;//0100
    _delay_ms(1);
    L_Control=0x00;
}

void L_Data(char str){
    L_Byte=str;
    L_Control=0x05;//0101
    _delay_ms(1);
    L_Control=0x01;//0001
}

void L_Str(char* str){
    L_Cmd(0x80);
    int i=0;
    while(str[i]!='\0')
        L_Data(str[i++]);
}


