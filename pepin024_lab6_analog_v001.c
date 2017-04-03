#include <p24Fxxxx.h>
#include <xc.h>

#define SAMPLE_PERIOD 15625               //Period to take analog samples
#define BUFFERMASK 0b1111111111

int buffer[1024];
int bufferFront = 0;


void __attribute__((__interrupt__)) _ADC1Interrupt(void){
    _AD1IF = 0;
    bufferFront = ((bufferFront + 1) & BUFFERMASK);
    buffer[bufferFront] = ADC1BUF0;
}


void analog_init(void){
    T3CON = 0;                              //Using TMR3 to take samples
    TMR3 = 0;
    T3CONbits.TCKPS = 0b10;                 //For 16 samples per second we need a prescalor of 1:64
    PR3 = SAMPLE_PERIOD;
   
    
    
    AD1PCFGbits.PCFG0 = 0;                  //Sets AN0 as analog
    TRISAbits.TRISA0 = 1;                   //Sets RA0/AN0 as input
    
    AD1CON1 = 0;                            //Reset configuration registrers
    AD1CON2 = 0;
    AD1CON3 = 0;
    AD1CHS = 0;                             //Use AN0 
    
    AD1CON1bits.ASAM = 1;
    AD1CON1bits.SSRC = 0b010;                //Use tmr3 to start conversion proccess   
    
    AD1CON3bits.ADCS = 2;
    AD1CON3bits.SAMC = 3;
    
    _AD1IF = 0;
    _AD1IE = 1;
    
    T3CONbits.TON = 1;
    AD1CON1bits.ADON = 1;
    
}

int getBuffer(void){
    return buffer[bufferFront];
}