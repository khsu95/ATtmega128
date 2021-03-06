#define LCD_WDATA PORTA
#define LCD_WINST PORTA
#define LCD_RDATA PINA

#define LCD_CTRL PORTG
#define LCD_EN 0
#define LCD_RW 1
#define LCD_RS 2

#include<avr/io.h>
#include<util/delay.h>

void LCD_PORT_Init(void);
void Init_Lcd(void);
void LCD_Comm(unsigned char command);
void LCD_Data(unsigned char ch);
void LCD_Delay(int ms);
void LCD_Char(unsigned char ch);
void LCD_Str(unsigned char* str);
void LCD_Pos(unsigned char row, unsigned char col);
void delay_ms(int ms);

int main(){
    unsigned char str[]="LCD Test..";
    Init_Lcd();
    LCD_Pos(0,0);
    LCD_Str(str);
    while(1);

}

void LCD_PORT_Init(void){
    DDRA=0xFF;
    DDRG=0xFF;
}

void Init_Lcd(void){
    LCD_PORT_Init();
    LCD_Comm(0x38);
    LCD_Delay(2);
    LCD_Comm(0x38);
    LCD_Delay(2);
    LCD_Comm(0x38);
    LCD_Delay(2);
    LCD_Comm(0x0e);
    LCD_Delay(2);
    LCD_Comm(0x01);
    LCD_Delay(30);
    LCD_Comm(0x06);
    LCD_Delay(2);
}

void LCD_Comm(unsigned char command){
    LCD_CTRL &=~(1<<LCD_RS);
    LCD_CTRL &=~(1<<LCD_RW);
    LCD_CTRL |=(1<<LCD_EN);
    delay_ms(1);
    LCD_WINST=command;
    delay_ms(1);
    LCD_CTRL &=~(1<<LCD_EN);
}

void LCD_Data(unsigned char ch){
    LCD_CTRL |=(1<<LCD_RS);
    LCD_CTRL &=~(1<<LCD_RW);
    LCD_CTRL |=(1<<LCD_EN);
    delay_ms(1);
    LCD_WDATA=ch;
    delay_ms(1);
    LCD_CTRL &=~(1<<LCD_EN);
}

void LCD_Delay(int ms){
    delay_ms(ms);
}

void LCD_Char(unsigned char ch){
    LCD_Delay(1);
    LCD_Data(ch);
}

void LCD_Str(unsigned char* str){
    while(*str!=0){
        LCD_Char(*str);
        str++;
    }
}

void LCD_Pos(unsigned char row, unsigned char col){
    LCD_Comm(0x80|(row*0x40+col));
}

void delay_ms(int ms){
    while(ms-- != 0)
    _delay_ms(1.0);
}
