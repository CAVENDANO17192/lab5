/*
 * File:   ADC_I2C.c
 * Author: CHARLIE
 *
 * Created on 26 de febrero de 2020, 15:55
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.



#include <xc.h>
#include <pic16f887.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LCD.h"
#include "I2C_MASTER.h"
#include "OSCILADOR.h"

uint8_t ADC;
float voltaje;
int V1;
int POT1A;
int POT1B;
int POT1C;
char POT1SA[5];
char POT1SB[5];
char POT1SC[5];
char PUNTO1[5];

void SETUP(void);
void main(void) {
    SETUP();
    initOsc(6);
    lcd_init();
    
    lcd_msg("ADC  CONT.  FOTO.");
    while(1){
        I2C_Master_Start();         //Start condition
        I2C_Master_Write(0x21);     //7 bit address + Read
        ADC = I2C_Master_Read(0); //Read + Acknowledge
        I2C_Master_Stop();          //Stop condition
        __delay_ms(200);
        voltaje = (ADC*5.0)/255.0;
        V1 = (voltaje)*100;
        POT1A = V1%10;
        itoa(POT1SA,POT1A,10);
        POT1B = (V1/10)%10;
        itoa(POT1SB,POT1B,10);
        POT1C = (V1/100)%10;
        itoa(POT1SC,POT1C,10);
        strcat(POT1SB,POT1SA);
        strcpy(PUNTO1,".");
        strcat(PUNTO1,POT1SB);
        strcat(POT1SC,PUNTO1);
        lcd_cmd(0xC0); 
        lcd_msg(POT1SC);
        
        
        
//        __delay_ms(200);
//        I2C_Master_Start();         //Start condition
//        I2C_Master_Write(0x31);     //7 bit address + Read
//        ADC = I2C_Master_Read(0); //Read + Acknowledge
//        I2C_Master_Stop();          //Stop condition
//        __delay_ms(200);
    }
}
void SETUP (void){
    TRISA=0;
    TRISB=0;
    TRISC=0b000011000;
    TRISD=0;
    TRISE=0;
    PORTA=0;
    PORTB=0;
    PORTC=0;
    PORTD=0;
    PORTE=0;
    I2C_INIT(100000);
}