/*===================================CPEG222====================================
 * Program:      Project 3 template
 * Authors:     Martin Olguin and Furdeen Hasan
 * Date:        10/19/2022
 * This is a template that you can use to write your project 3 code, for mid-stage and final demo.
==============================================================================*/
/*-------------- Board system settings. PLEASE DO NOT MODIFY THIS PART ----------*/
#ifndef _SUPPRESS_PLIB_WARNING          //suppress the plib warning during compiling
#define _SUPPRESS_PLIB_WARNING
#endif
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config POSCMOD = XT             // Primary Oscillator Configuration (XT osc mode)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
/*----------------------------------------------------------------------------*/

#include <xc.h>   //Microchip XC processor header which links to the PIC32MX370512L header
#include <stdio.h>  // need this for sprintf
#include <sys/attribs.h>
#include "config.h" // Basys MX3 configuration header
#include "lcd.h"    // Digilent Library for using the on-board LCD
#include "acl.h"    // Digilent Library for using the on-board accelerometer
#include "ssd.h"
#include "utils.h"
#include "adc.h"
#include "i2c.h"
#include "rgbled.h"
#include "led.h"
#include "mic.h"

/* --------------------------- Forward Declarations-------------------------- */
void initialize_ports(); // function that configures SSD
void delay_ms(int milliseconds); //function to control delay
void initialize_output_states();
void CNConfig();
void handle_new_keypad_press();
//void Timer3_Setup();
//void __ISR(_TIMER_3_VECTOR, ipl7) Timer3ISR(void);


/* ------------------------ Constant Definitions ---------------------------- */
#define SYS_FREQ (80000000L) // 80MHz system clock
#define _80Mhz_ (80000000L)
#define LOOPS_NEEDED_TO_DELAY_ONE_MS_AT_80MHz 1426
#define LOOPS_NEEDED_TO_DELAY_ONE_MS (LOOPS_NEEDED_TO_DELAY_ONE_MS_AT_80MHz * (SYS_FREQ / _80Mhz_))




/* -------------------------------------------------------------------------- */
#define TRUE 1
#define FALSE 0

// below are keypad row and column definitions based on the assumption that JB will be used and columns are CN pins
// If you want to use JA or use rows as CN pins, modify this part
#define R4 LATCbits.LATC14
#define R3 LATDbits.LATD0
#define R2 LATDbits.LATD1
#define R1 LATCbits.LATC13
#define C4 PORTDbits.RD9
#define C3 PORTDbits.RD11
#define C2 PORTDbits.RD10
#define C1 PORTDbits.RD8
char d1;
char d2;
char d3;
char d4;
int state = 0;
int count = 10;
int state_led = 0b00000000;



unsigned char number[] = {
    0b1000000, // 0
    0b1111001, // 1
    0b0100100, // 2
    0b0110000, // 3
    0b0011001, // 4
    0b0010010, // 5
    0b0000010, // 6
    0b1111000, // 7
    0b0000000, // 8
    0b0010000, // 9
    0b1111111 //clear
};








typedef enum _KEY {K0, K1, K2, K3, K4, K5, K6, K7, K8, K9, K_A, K_B, K_C, K_D, K_E, K_F, K_NONE} eKey ;
typedef enum _MODE {READY} eModes ;

eModes mode = READY ;

char new_press = FALSE;

/* subrountines
void CNConfig();

void handle_new_keypad_press(eKey key) ;
void SSD_Timer1Setup();
void __ISR(_TIMER_3_VECTOR, ipl7) Timer3ISR(void); */
/* -------------------------------------------------------------------------- */

int main(void) {
    d1 = 90;
    d2 = 90;
    d3 = 90;
    d4 = 90;
    /* Initialization of LED, LCD, SSD, etc */
    DDPCONbits.JTAGEN = 0; // Required to use Pin RA0 (connected to LED 0) as IO
    LCD_Init();
    ACL_Init();
//    Timer3_Setup();
    MIC_Init();
    float rgACLGVals[3];
    ACL_ReadGValues(rgACLGVals);
    int seed = rgACLGVals[0] * 10000;
    srand((unsigned) seed);
    // below are keypad row and column configurations based on the assumption that JB will be used and columns are CN pins
    // If you want to use JA or use rows as CN pins, modify this part

    // keypad rows as outputs
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    ANSELDbits.ANSD1 = 0;
    TRISCbits.TRISC14 = 0;
    TRISCbits.TRISC13 = 0;

    // keypad columns as inputs
    TRISDbits.TRISD8 = 1;
    TRISDbits.TRISD9 = 1;
    TRISDbits.TRISD10 = 1;
    TRISDbits.TRISD11 = 1;

    TRISBbits.TRISB12 = 0; //RB12 set as output 
    ANSELBbits.ANSB12 = 0; //RB12 analog functionality disabled 
    TRISBbits.TRISB13 = 0; //RB13 set as output 
    ANSELBbits.ANSB13 = 0; //RB13 analog functionality disabled 
    TRISAbits.TRISA9 = 0; //RA9 set as output 
    TRISAbits.TRISA10 = 0; //RA10 set as output 
    TRISGbits.TRISG12 = 0; //RG12 set as output 
    TRISAbits.TRISA14 = 0; //RA14 set as output 
    TRISDbits.TRISD6 = 0; //RD6 set as output 
    TRISGbits.TRISG13 = 0; //RG13 set as output 
    TRISGbits.TRISG15 = 0; //RG15 set as output 
    TRISDbits.TRISD7 = 0; //RD7 set as output 
    TRISDbits.TRISD13 = 0; //RD13 set as output 
    TRISGbits.TRISG14 = 0; //RG14 set as output
    LCD_Init(); // A library function provided by Digilent
    SSD_Init(); //SSD Init
    
    //Mic
    TRISBbits.TRISB4 = 1; //RB12 set as output 
    ANSELBbits.ANSB4 = 1; //RB12 analog functionality disabled 
    
    
    
    // You need to enable all the rows
    R1 = R2 = R3 = R4 = 0;

    //LCD_WriteStringAtPos("    Group  7    ", 0, 0);
    LCD_WriteStringAtPos("     Ready     ", 1, 0);
    SSD_WriteDigits(100, 100, 100, 100, 0, 0, 0, 0);


    


    CNConfig();

    /* Other initialization and configuration code */
    int val,  max_val = 0;
    while (TRUE) {
        //You can put key-pad indepenent mode transition here, such as countdown-driven mode trasition, monitoring of microphone or update of RGB.
        /*if (!K_NONE) {
            mode = READY;
            SSD_WriteDigits(d4, d3, d2, d1, 0, 0, 0, 0);
          
         }
           */

        val = ADC_AnalogRead(4);

        max_val = val;
        char buffr[16];
        sprintf(buffr, " %d ", max_val);
        LCD_WriteStringAtPos(buffr, 0, 0);
    }
}


/*
void __ISR(_TIMER_3_VECTOR, ipl7) Timer3ISR(void)
{
    static unsigned char idxCurrDigit = 0; 
    unsigned char currDigit, idx; 
    idx = (idxCurrDigit++) & 3; // The next digit becomes the current digit, in a circular approach 
    currDigit = digits[idx]; 
    
    // 1. deactivate all digits (anodes)
    lat_SSD_AN1 = 1; // deactivate digit 1; 
    lat_SSD_AN2 = 1; // deactivate digit 2; 
    lat_SSD_AN3 = 1; // deactivate digit 3; 
    lat_SSD_AN0 = 1; // deactivate digit 0; 
    
    // 2. drive all the segments (cathodes)
    lat_SSD_CA = currDigit & 0x01; 
    lat_SSD_CB = (currDigit & 0x02) >> 1; 
    lat_SSD_CC = (currDigit & 0x04) >> 2; 
    lat_SSD_CD = (currDigit & 0x08) >> 3; 
    lat_SSD_CE = (currDigit & 0x10) >> 4; 
    lat_SSD_CF = (currDigit & 0x20) >> 5; 
    lat_SSD_CG = (currDigit & 0x40) >> 6; 
    lat_SSD_DP = (currDigit & 0x80) >> 7; 
 
    // 3. activate the current digit (anodes)
    switch(idx) 
    {case 0: 
    lat_SSD_AN0 = 0; // activate digit 0; 
    break; case 1: 
    lat_SSD_AN1 = 0; // activate digit 1; break; 
    case 2:lat_SSD_AN2 = 0; // activate digit 2; 
    break; case 3: 
    lat_SSD_AN3 = 0; // activate digit 3; 
    break; 
    }
    IFS0bits.T3IF = 0; // clear interrupt flag 
    // This is the same as mT3ClearIntFlag();
    
}
*/
/*
void __ISR(_TIMER_3_VECTOR, ipl6)Timer3ISR(void) {
        //static unsigned char idxCurrDigit = 0;
        //unsigned char currDigit, idx;
        //idx = (idxCurrDigit++) & 3; // The next digit becomes the current digit, in a circular approach 
        //currDigit = digits[idx];
        count--;
        if (count < 0) {
            count = 10;
        }
        char buffer[16];
        
        sprintf(buffer, " %d seconds left", count);
        LCD_WriteStringAtPos(buffer, 1, 0);
        IFS0bits.T3IF = 0; // clear interrupt flag
        IEC0bits.T3IE = 1; // enable interrupt
}





void Timer3_Setup() 
{
    PR3 = (int) (((float) (1 * 80000000) / 256) + 0.5); //set period register, generates one interrupt every 3 ms
    TMR3 = 0;                    // initialize count to 0
    PR3 = 0xFFFF;                // Set period of Timer3
    T3CON = 0x8030;              // Enable Timer3 Set Priority
    T3CONbits.TCKPS = 7;         // 1:64 prescale value
    T3CONbits.TGATE = 0;         // not gated input (default)
    T3CONbits.TCS = 0;           // PCBLK input (default)
    T3CONbits.ON = 1;            // turn on Timer1
    IPC3bits.T3IP = 6;           // priority
    IPC3bits.T3IS = 3;           // subpriority
    IFS0bits.T3IF = 0;           // clear interrupt flag
    IEC0bits.T3IE = 1;           // enable interrupt
    macro_enable_interrupts();   // enable interrupts at CPU
}

*/

/*
void SSD_WriteDigits(unsigned char d1, unsigned char d2, 
        unsigned char d3, unsigned char d4, unsigned char dp1, \
         unsigned char dp2, unsigned char dp3, unsigned char dp4) 
{
    T3CONbits.ON = 0;                       // turn off Timer3 
    digits[0] = SSD_GetDigitSegments(d1);
    digits[1] = SSD_GetDigitSegments(d2);
    digits[2] = SSD_GetDigitSegments(d3); 
    digits[3] = SSD_GetDigitSegments(d4);
    
    if(!dp1) {
        digits[0] |= 0x80;
    } if(!dp2) { 
        digits[1] |= 0x80;
    }
    if(!dp3) {
        digits[2] |= 0x80;
    } if(!dp4) { 
        digits[3] |= 0x80;
    }
    T3CONbits.ON = 1;                       // turn of Timer3             

}*/




















void CNConfig() {
    /* Make sure vector interrupts is disabled prior to configuration */
    macro_disable_interrupts;

    // Complete the following configuration of CN interrupts, then uncomment them
    CNCONDbits.ON = 1; //all port D pins to trigger CN interrupts
    CNEND = 0xf00; //configure PORTD pins 8-11 as CN pins
    CNPUD = 0xf00; //enable pullups on PORTD pins 8-11

    IPC8bits.CNIP = 6; // set CN priority to  6
    IPC8bits.CNIS = 3; // set CN sub-priority to 3

    IFS1bits.CNDIF = 0; //Clear interrupt flag status bit
    IEC1bits.CNDIE = 1; //Enable CN interrupt on port D


    int j = PORTD; //read port to clear mismatch on CN pins
    macro_enable_interrupts(); // re-enable interrupts
}








void __ISR(_CHANGE_NOTICE_VECTOR) CN_Handler(void) {
    eKey key = K_NONE;
    
    // 1. Disable CN interrupts   
    IEC1bits.CNDIE = 0; //Disable change notice interrupt on port D 
   
    

    // 2. Debounce keys for 10ms
    for (int i=0; i<1426; i++) {}

    // 3. Handle "button locking" logic

    unsigned char key_is_pressed = (!C1 || !C2 || !C3 || !C4);
    // If a key is already pressed, don't execute the rest second time to eliminate double pressing
    if (!key_is_pressed)
    {
        new_press = FALSE;
    }
    else if (!new_press)
    {
        new_press = TRUE;

        // 4. Decode which key was pressed
        
        // check first row 
        R1 = 0; R2 = R3 = R4 = 1;
        if(C1 == 0){key = K1;}    // first column
        else if(C2 == 0){key = K2; } // second column
        else if (C3 == 0) { key = K3; } // third column
        else if (C4 == 0) { key = K_A; } // fourth column

        // check second row 
        R2 = 0; R1 = R3 = R4 = 1;
        if (C1 == 0) { key = K4; }
        else if (C2 == 0) { key = K5; }
        else if (C3 == 0) { key = K6; }
        else if (C4 == 0) { key = K_B; }

        // check third row 
        R3 = 0; R1 = R2 = R4 = 1;
        if (C1 == 0) { key = K7; }
        else if (C2 == 0) { key = K8; }
        else if (C3 == 0) { key = K9; }
        else if (C4 == 0) { K_C; }

        // check fourth row 
        R4 = 0; R1 = R2 = R3 = 1;
        if (C1 == 0) { key = K0; }
        else if (C2 == 0) { key = K_F; }
        else if (C3 == 0) { key = K_E; }
        else if (C4 == 0) { key = K_D; }

        // re-enable all the rows for the next round
        R1 = R2 = R3 = R4 = 0;
    
    }
    
    // if any key has been pressed, update next state and outputs
    if (key != K_NONE) {
       handle_new_keypad_press(key) ;
    }
    
    
    int j = PORTD;              //read port to clear mismatch on CN pints
    
    // 5. Clear the interrupt flag
    IFS1bits.CNDIF = 0;     

    // 6. Reenable CN interrupts
    IEC1bits.CNDIE = 1; 
}



void handle_new_keypad_press(eKey key) {
    int a,b,c,d;
    switch (mode) {
        case READY:
            d1 = 90;
            d2 = 90;
            d3 = 90;
            d4 = 90;
            state = 0;
            LCD_WriteStringAtPos(" Enter Passcode   ", 0, 0);
            LCD_WriteStringAtPos(" # Seconds Left", 1, 0);
            if(key){
            if (state = 0) {
                d1 = key;
                state = 1;
            }
            if (state == 1){
                d2 = d1;
                d1 = key;
                
                state = 2;
                
            }
            }
                
               
             SSD_WriteDigits(d1,d2, d3, d4, 0,0,0,0);   
            
            
            break;
            //more modes
    }
}




