/*
 * File:   MASTERR_I2C.c
 * Author: CHARLIE
 *
 * Created on 26 de febrero de 2020, 22:03
 */



// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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
#include "PANTALLALCD.h"
#include "I2C.h"
#define _XTAL_FREQ  8000000
void LOOP(void);
uint8_t analogic_digital_a;
uint8_t CONTADOR;
uint8_t analogic_digital_b;
float voltage;
float luz;
int DC2;
int LUZ_1_A;
int LUZ_1_B;
int LUZ_A;
char LUZA_CHARA[5];
char LUZB_CHARB[5];
char LUZC_CHARC[5];
char POINTERB[5];
int CONTD;
char CONTD_CHAR[5];
int CONTU;
char CONTU_CHAR[5];
float voltage;
int DC1;
int ADC_1_A;
int ADC_1_B;
int ADC_A;
char ADCA_CHARA[5];
char ADCB_CHARB[5];
char ADCC_CHARC[5];
char POINTERA[5];


void SETUP(void);
void main(void) {
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
    inicializacion();
    LOOP();

}

void LOOP(void){
        lcd_msg("ADC  CONT.  LUZ");
    while(1){
        I2C_Master_Start();         //Start condition
        I2C_Master_Write(0x21);     //7 bit address + Read
        analogic_digital_a = I2C_Master_Read(0); //Read + Acknowledge
        I2C_Master_Stop();          //Stop condition
        __delay_ms(200);
         voltage = (analogic_digital_a*5.0)/255.0;
        DC1 = (voltage)*100;
        ADC_1_A = DC1%10;
        itoa(ADCA_CHARA,ADC_1_A,10);
        ADC_1_B = (DC1/10)%10;
        itoa(ADCB_CHARB,ADC_1_B,10);
        ADC_A = (DC1/100)%10;
        itoa(ADCC_CHARC,ADC_A,10);
        strcat(ADCB_CHARB,ADCA_CHARA);
        strcpy(POINTERA,".");
        strcat(POINTERA,ADCB_CHARB);
        strcat(ADCC_CHARC,POINTERA);
        lcd_cmd(0xC0); 
        
        
        I2C_Master_RepeatedStart();
        I2C_Master_Start();         //Start condition
        I2C_Master_Write(0x11);     //7 bit address + Read
        CONTADOR = I2C_Master_Read(0); //Read + Acknowledge
        I2C_Master_Stop();          //Stop condition
        __delay_ms(200);
        
        CONTD = CONTADOR/10;
        itoa(CONTD_CHAR,CONTD,10);
        CONTU = CONTADOR%10;
        itoa(CONTU_CHAR,CONTU,10);
        strcat(CONTD_CHAR,CONTU_CHAR);
        
     
        I2C_Master_RepeatedStart();
     
                
        I2C_Master_Start();         //Start condition
        I2C_Master_Write(0x31);     //7 bit address + Read
        analogic_digital_b = I2C_Master_Read(0); //Read + Acknowledge
        I2C_Master_Stop();          //Stop condition
        __delay_ms(200);
        luz = (analogic_digital_b*5.0)/255.0;
        DC2 = (luz)*100;
        LUZ_1_A = DC2%10;
        itoa(LUZA_CHARA,LUZ_1_A,10);
        LUZ_1_B = (DC2/10)%10;
        itoa(LUZB_CHARB,LUZ_1_B,10);
        LUZ_A = (DC2/100)%10;
        itoa(LUZC_CHARC,LUZ_A,10);
        strcat(LUZB_CHARB,LUZA_CHARA);
        strcpy(POINTERB,".");
        strcat(POINTERB,LUZB_CHARB);
        strcat(LUZC_CHARC,POINTERB);
        

        
        
        
        lcd_msg(ADCC_CHARC);
        lcd_msg("V  ");
        lcd_msg(CONTD_CHAR);
        lcd_msg("  ");
        lcd_msg(LUZC_CHARC);
        lcd_msg("V");

        I2C_Master_RepeatedStart();
//        __delay_ms(200);
//        I2C_Master_Start();         //Start condition
//        I2C_Master_Write(0x31);     //7 bit address + Read
//        ADC = I2C_Master_Read(0); //Read + Acknowledge
//        I2C_Master_Stop();          //Stop condition
//        __delay_ms(200);
    }
}