/*
 * File:   TEMP_PIC.c
 * Author: CHARLIE
 *
 * Created on 22 de febrero de 2020, 15:55
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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "PANTALLALCD.h"
#include <stdlib.h>
#include "TEMPSENSOR.h"

#define _XTAL_FREQ  8000000
// ENTRADAS Y SALIDAS SENSOR DE TEMPERATURA
#define TRIS_DHT TRISDbits.TRISD2
#define PORT_DHT PORTDbits.RD2

void LOOP(void);
 void START_DHT11(void);
void CHECK_RESPONSE(void);
char ReadData();
unsigned char check;


unsigned char T_byte1;
unsigned char T_byte2;
unsigned char RH_byte1;
unsigned char RH_byte2;

int uniT;
int decT;
int uniHR;
int decHR;

int uniT_int;
int decT_int;
int uniHR_int;
int decHR_int;

char uniT_char[5];
char decT_char[5];
char uniHR_char[5];
char decHR_char[5];

unsigned sum; 

void main(void) {
   
          //entradas, salidas, entradas digitales o analogicas
    ANSEL = 0b00000000;
    ANSELH= 0b00000000;
    TRISA = 0b00000000;
    TRISB = 0b00000000; 
    TRISD = 0b00000000;
    TRISC = 0b00000000;
    TRISE = 0;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
 
    
    check = 0;
    inicializacion();
   
//    START_DHT11();
    LOOP();

    return;
}

void LOOP(void){
    while(1){
        START_DHT11();
        CHECK_RESPONSE();
        
        if(check == 1){
        
            RH_byte1 = ReadData();
            RH_byte2 = ReadData();
            T_byte1 = ReadData();
            T_byte2 = ReadData();
            sum = ReadData();
            if(sum == ((RH_byte1+RH_byte2+T_byte1+T_byte2) & 0xFF)){
              decHR = RH_byte1/10;
              itoa(decHR_char,decHR,10);
              uniHR = RH_byte1%10;
              itoa(uniHR_char,uniHR,10);
              decT = T_byte1/10;
              itoa(decT_char,decT,10);
              uniT = T_byte1%10;
              itoa(uniT_char,uniT ,10);
              strcat(decHR_char,uniHR_char);
              strcat(decT_char,uniT_char);
              
   

              lcd_cmd(0x01);
              lcd_msg("TEMP = ");
              lcd_msg(decT_char);
              lcd_msg(" grados   ");
              __delay_ms(3);
              lcd_cmd(0xC0);
              lcd_msg("Humedad = ");
              lcd_msg(decHR_char);
              lcd_msg("%        ");
              
              
              
              
              
            }
        }
      
        
    }
}



 void START_DHT11(void){  // inicia el sensor de temperatura
     TRIS_DHT = 0;
     PORT_DHT = 0;
     __delay_ms(18);
     PORT_DHT = 1;
     __delay_us(30);
     TRIS_DHT=1;
     
     
 }
 
 void CHECK_RESPONSE(void){
   check = 0;
   __delay_us(40);
   if(PORT_DHT == 0){
       __delay_us(80);
       if(PORT_DHT == 1){         // mantener el ojo en este if
           check = 1;
           __delay_us(40);
       }
   }
 }
 char ReadData(){
     char i, j;
     for(j = 0; j<8; j++){
         while(!PORT_DHT);
         __delay_us(30);
         if(PORT_DHT == 0)
             i&= ~(1<<(7-j));
         else{
             i|= (1<< (7-j));
         while(PORT_DHT);
         }  
     }
     return i;
 }
 
 
 
 

        