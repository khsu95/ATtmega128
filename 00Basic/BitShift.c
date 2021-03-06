#define LED PORTB

#include<avr/io.h>
#include<util/delay.h>


typedef unsigned char Byte;
Byte SetBit(unsigned char REG, unsigned char Bit);
Byte ClrBit(unsigned char REG, unsigned char Bit);

int PB_LShift();
int PB_RShift();
int PB_LEDOnOff();
int PB_LEDSwitch();

void main(void){
    unsigned char key;
    DDRB=0xff;
    DDRD=0x0f;

    while(1){
        key=(PIND&0xf0);
        switch(key){
                case 0xe0:
                PB_LShift();
                LED=0x00;
                _delay_ms(500);
                break;
            case 0xd0:
                PB_RShift();
                LED=0x00;
                _delay_ms(500);
                break;
            case 0xb0:
                PB_LEDOnOff();
                LED=0x00;
                _delay_ms(500);
                break;
            case 0x70:
                PB_LEDSwitch();
                LED=0x00;
                _delay_ms(500);
                break;
            default:
                break;
        }
    }
}

Byte SetBit(unsigned char REG, unsigned char Bit){
    LED=(REG|(0x01<<Bit));
	return (REG|(0x01<<Bit));
}
Byte ClrBit(unsigned char REG, unsigned char Bit){
    LED=(REG&=~(0x01<<Bit));
	return (REG&=~(0x01<<Bit));
}

int PB_LShift(){
    LED=0x00;
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            SetBit(LED,j);
            _delay_ms(500);
        }
        _delay_ms(100);
        for(int j=0;j<4;j++){
            ClrBit(LED,j);
            _delay_ms(500);
        }
        _delay_ms(100);
    }
    return 0;
}

int PB_RShift(){
    LED=0x00;
   for(int i=0;i<4;i++){
        for(int j=0;j<4;j--){
            SetBit(LED,j);
            _delay_ms(500);
        }
        _delay_ms(100);
        for(int j=4;j<0;j--){
            ClrBit(LED,j);
            _delay_ms(500);
        }
        _delay_ms(100);
    }
    return 0;
}

int PB_LEDOnOff(){
    LED=0x00;
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            SetBit(LED,j);
        }
        _delay_ms(500);
        for(int j=0;j<4;j++){
            ClrBit(LED,j);
        }
        _delay_ms(500);
    }
    return 0;
}

int PB_LEDSwitch(){
    LED=0x00;
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            SetBit(LED,j+6);
        }
        _delay_ms(500);
        for(int j=0;j<2;j++){
            ClrBit(LED,j+6);
        }
        _delay_ms(500);
		for(int j=0;j<2;j++){
            SetBit(LED,j+6);
        }
        _delay_ms(500);
        for(int j=0;j<2;j++){
            ClrBit(LED,j+6);
        }
        _delay_ms(500);
    }
}
