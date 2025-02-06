/*===================================CPEG222====================================
 * Program:      Project 3 template
 * Authors:     Chengmo Yang and Tommy White
 * Group: 7 -- Martin Olguin and Furdeen Hasan
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
#include "i2c.h"
#include "led.h"
#include "rgbled.h"
#include "ssd.h"
#include "utils.h"
#include "mic.h"
#include "adc.h"



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
char d1; // Variable for SSD
char d2; // Variable for SSD
char d3; // Variable for SSD
char d4; // Variable for SSD
int va1 = 0; 
int va2 = 0; 
int number[4]; // Number array
int count = 10;
int state_led;
int b = 0;
int passWord[8][4]; // passWord array for the randomly genrated 4-digit number
int indx = 0;
int LED = 0b11111111;
int state_led = 0;
int idk_clock = 0;
char match = 0;
char is;
\

int stored_key = 0;

int k = 0;
unsigned char numbr[] = { // Chart that will de called upon to display numbers on SSD
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
    0b1111101, //E
    0b1111111 //clear
};

typedef enum _KEY {
    K0, K1, K2, K3, K4, K5, K6, K7, K8, K9, K_A, K_B, K_C, K_D, K_E, K_F, K_NONE
} eKey;

typedef enum _MODE {
    Initial, Passcode, Carin, Error, Carout, Check
} eModes;

eModes mode = Initial;
char new_press = FALSE;

// subrountines
void CNConfig();
void handle_new_keypad_press(eKey key);
void Timer3_Setup();

int main(void) {
    // d1 to d4 = 90 switches the LEDS off
    d1 = 90; 
    d2 = 90;
    d3 = 90;
    d4 = 90;

    LED_SetGroupValue(LED);
   
    int a = 0;

    /* Initialization of LED, LCD, SSD, etc */
    DDPCONbits.JTAGEN = 0; // Required to use Pin RA0 (connected to LED 0) as IO
    LCD_Init();
    ACL_Init();
    SSD_Init();
    RGBLED_Init();
    // LED_Init();
    TRISA &= 0xFF00;
    /* The following line sets the tristate of Port F bit 0 to 1. BtnC is connected
to that
     pins. When the tristate of a pin is set high, the pin is configured as a
     digital input. */
    TRISBbits.TRISB8 = 1;
    ANSELBbits.ANSB8 = 0;




    Timer3_Setup();

    float rgACLGVals[3];
    ACL_ReadGValues(rgACLGVals);
    int seed = rgACLGVals[0] * 10000;
    srand((unsigned) seed);
    unsigned short num = rand() % 10000;

    
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
    // You need to enable all the rows
    R1 = R2 = R3 = R4 = 0;




    SSD_WriteDigits(d1, d2, d3, d4, 0, 0, 0, 0);

   

    CNConfig();

    int val, max_val;
    MIC_Init();
    /* Other initialization and configuration code */

    while (TRUE) {
     
        switch (mode) {
                //handle_new_keypad_press(key);
            case Initial:


                LCD_WriteStringAtPos("    Group  7    ", 0, 0); //Displays Group on Line 0
                LCD_WriteStringAtPos("    Ready      ", 1, 0); // Displays Ready/Initial Mode on Line 2
                SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0); // Clears SSD
                if (ADC_AnalogRead(4) > 700) {
                    mode = Carin;

                    // for loop below to generate a random 4 digit number
                    for (int i = 0; i < 4; i++) {
                        passWord[indx][i] = rand() % 10;

                    }
                    SSD_WriteDigits(passWord[indx][0], passWord[indx][1], passWord[indx][2], passWord[indx][3], 0, 0, 0, 0);
                    break; //Displays randomly generated number on the SSD
                }
                break;
            case Carin:

                if (state_led == 0) {
                    LCD_WriteStringAtPos(" Car Entering    ", 0, 0); //Displays Car Entering on line 1
                    LCD_WriteStringAtPos(" Park in Spot 0   ", 1, 0); // Displays Parking Spot Number

                }
                if (state_led == 1) {
                    LCD_WriteStringAtPos(" Car Entering    ", 0, 0); //Displays Car Entering on line 1
                    LCD_WriteStringAtPos(" Park in Spot 1   ", 1, 0);// Displays Parking Spot Number

                }
                if (state_led == 2) {
                    LCD_WriteStringAtPos(" Car Entering    ", 0, 0); //Displays Car Entering on line 1
                    LCD_WriteStringAtPos(" Park in Spot 2   ", 1, 0);// Displays Parking Spot Number
                }
                if (state_led == 3) {
                    LCD_WriteStringAtPos(" Car Entering    ", 0, 0); //Displays Car Entering on line 1
                    LCD_WriteStringAtPos(" Park in Spot 3   ", 1, 0);// Displays Parking Spot Number
                }
                if (state_led == 4) {
                    LCD_WriteStringAtPos(" Car Entering    ", 0, 0); //Displays Car Entering on line 1
                    LCD_WriteStringAtPos(" Park in Spot 4   ", 1, 0);// Displays Parking Spot Number
                }
                if (state_led == 5) {
                    LCD_WriteStringAtPos(" Car Entering    ", 0, 0); //Displays Car Entering on line 1
                    LCD_WriteStringAtPos(" Park in Spot 5   ", 1, 0);// Displays Parking Spot Number
                }
                if (state_led == 6) {
                    LCD_WriteStringAtPos(" Car Entering    ", 0, 0); //Displays Car Entering on line 1
                    LCD_WriteStringAtPos(" Park in Spot 6   ", 1, 0);// Displays Parking Spot Number
                }
                if (state_led == 7) {
                    LCD_WriteStringAtPos(" Car Entering    ", 0, 0); //Displays Car Entering on line 1
                    LCD_WriteStringAtPos(" Park in Spot 7   ", 1, 0);// Displays Parking Spot Number
                }
                if (state_led > 8) {
                    mode = Error;
                    b = 0;
                    LCD_WriteStringAtPos("    Error!        ", 0, 0); //Displays  Error! on Line 1
                    LCD_WriteStringAtPos("                  ", 1, 0);
                }




                break;
            case Passcode: //Used for Mode: EnterCode

                LCD_WriteStringAtPos(" Enter Passcode   ", 0, 0); //Displays Passcode Enter request on Line 1
                SSD_WriteDigits(d1, d2, d3, d4, 0, 0, 0, 0); // Used to Display Keypad Entries on SSD
                //               SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0);
                break;
            case Error: //Used to Display all errors; E111,E222,E333,E444,E555
                LCD_WriteStringAtPos("    Error!        ", 0, 0); //Displays Error! on line 1
                LCD_WriteStringAtPos("                  ", 1, 0);

                idk_clock++;
                if (b == 0) { //For car trying to enter when the lot is full
                    if (idk_clock % 10 == 1) { //Used for Error 1; d1 to d3 displays 1 on the SSDs; d4 displays E
                        d1 = 1; 
                        d2 = 1;
                        d3 = 1;
                        d4 = 14; 
                        SSD_WriteDigits(d1, d2, d3, d4, 0, 0, 0, 0);
                    } else if (idk_clock % 10 == 0) { //Timer for displaying error; Ends error display when timer ends
                        SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0);//Clears the SSD Display
                    }
                }
                if (b == 1) { //For passcode timeout in mode 3
                    if (idk_clock % 10 == 1) { //Used for Error 5; d1 to d3 displays 1 on the SSDs; d4 displays E
                        d1 = 5;
                        d2 = 5;
                        d3 = 5;
                        d4 = 14;
                        SSD_WriteDigits(d1, d2, d3, d4, 0, 0, 0, 0);
                    } else if (idk_clock % 10 == 0) { //Timer for displaying error; Ends error display when timer ends
                        SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0);//Clears the SSD Display
                    }
                }
                if (b == 2) { //For Car trying to exit when lot is empty
                    if (idk_clock % 10 == 1) { //Used for Error 2; d1 to d3 displays 2 on the SSDs; d4 displays E
                        d1 = 2;
                        d2 = 2;
                        d3 = 2;
                        d4 = 14;
                        SSD_WriteDigits(d1, d2, d3, d4, 0, 0, 0, 0);
                    } else if (idk_clock % 10 == 0) { //Timer for displaying error; Ends error display when timer ends
                        SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0);//Clears the SSD Display
                    }
                }
                if (va1 == 9) { //For incorrect passcode being entered in mode3
                    if (idk_clock % 10 == 1) { //Used for Error 4; d1 to d3 displays 2 on the SSDs; d4 displays E
                        d1 = 4;
                        d2 = 4;
                        d3 = 4;
                        d4 = 14;
                        SSD_WriteDigits(d1, d2, d3, d4, 0, 0, 0, 0);
                    } else if (idk_clock % 10 == 0) { //Timer for displaying error; Ends error display when timer ends
                        SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0);//Clears the SSD Display
                    }
                }
                if (b == 4) { //For passcode being requested for an empty spot
                    if (idk_clock % 10 == 1) { //Used for Error 3; d1 to d3 displays 2 on the SSDs; d4 displays E
                        d1 = 3;
                        d2 = 3;
                        d3 = 3;
                        d4 = 14;
                        SSD_WriteDigits(d1, d2, d3, d4, 0, 0, 0, 0);
                    } else if (idk_clock % 10 == 0) { //Timer for displaying error; Ends error display when timer ends
                        SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0);//Clears the SSD Display
                    }
                }
                break;
            case Carout: //Used for mode Carout
                LED_SetGroupValue(LED); //Function for setting the Led Values
                if (va1 == 1) {
                    va2 = 1;
                    LCD_WriteStringAtPos(" Car 0 Exiting  ", 0, 0);
                    LCD_WriteStringAtPos("   Thank You!   ", 1, 0);
                    SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0); //SSD Cleared
                    LED = LED | 0b00000001; //Turns LED0 back on after car exits
                }
                if (va1 == 2) {
                    va2 = 2;
                    LCD_WriteStringAtPos(" Car 1 Exiting  ", 0, 0);
                    LCD_WriteStringAtPos("   Thank You!   ", 1, 0); 
                    SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0); //SSD Cleared
                    LED = LED | 0b00000010; //Turns LED1 back on after car exits
                }
                if (va1 == 3) {
                    va2 = 3;
                    LCD_WriteStringAtPos(" Car 2 Exiting  ", 0, 0);
                    LCD_WriteStringAtPos("   Thank You!   ", 1, 0);
                    SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0); //SSD Cleared
                    LED = LED | 0b00000100; //Turns LED2 back on after car exits
                }
                if (va1 == 4) {
                    va2 = 4;
                    LCD_WriteStringAtPos(" Car 3 Exiting  ", 0, 0);
                    LCD_WriteStringAtPos("   Thank You!   ", 1, 0);
                    SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0); //SSD Cleared
                    LED = LED | 0b00001000; //Turns LED3 back on after car exits
                }
                if (va1 == 5) {
                    va2 = 5;
                    LCD_WriteStringAtPos(" Car 4 Exiting  ", 0, 0);
                    LCD_WriteStringAtPos("   Thank You!   ", 1, 0);
                    SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0); //SSD Cleared
                    LED = LED | 0b00010000; //Turns LED4 back on after car exits
                }
                if (va1 == 6) {
                    va2 = 6;
                    LCD_WriteStringAtPos(" Car 5 Exiting  ", 0, 0);
                    LCD_WriteStringAtPos("   Thank You!   ", 1, 0);
                    SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0); //SSD Cleared
                    LED = LED | 0b00100000; //Turns LED5 back on after car exits
                }
                if (va1 == 7) {
                    va2 = 7;
                    LCD_WriteStringAtPos(" Car 6 Exiting  ", 0, 0);
                    LCD_WriteStringAtPos("   Thank You!   ", 1, 0);
                    SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0); //SSD Cleared
                    LED = LED | 0b01000000; //Turns LED6 back on after car exits

                }
                if (va1 == 8) {
                    va2 = 8;
                    LCD_WriteStringAtPos(" Car 7 Exiting  ", 0, 0);
                    LCD_WriteStringAtPos("   Thank You!   ", 1, 0);
                    SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0); //SSD Cleared
                    LED = LED | 0b10000000; //Turns LED7 back on after car exits
                }

                break;
            case Check:

                if (stored_key == 1) {
                    LCD_WriteStringAtPos("Showing Passcode ", 0, 0); 
                    LCD_WriteStringAtPos("   For Car 0    ", 1, 0);
                    SSD_WriteDigits(passWord[0][0], passWord[0][1], passWord[0][2], passWord[0][3], 0, 0, 0, 0);//Displays the stored 4-digit passcode on the SSD
                    if (passWord[0][0] == 0 && passWord[0][1] == 0 && passWord[0][2] == 0 && passWord[0][3] == 0) {//Checks for passcode/ key input for an empty spot; If there is none, displays error
                        mode = Error;
                        b = 4;
                    }
                }
                if (stored_key == 2) {
                    LCD_WriteStringAtPos("Showing Passcode ", 0, 0);
                    LCD_WriteStringAtPos("   For Car 1    ", 1, 0);
                    SSD_WriteDigits(passWord[1][0], passWord[1][1], passWord[1][2], passWord[1][3], 0, 0, 0, 0);//Displays the stored 4-digit passcode on the SSD
                    if (passWord[1][0] == 0 && passWord[1][1] == 0 && passWord[1][2] == 0 && passWord[1][3] == 0) {//Checks for passcode/ key input for an empty spot; If there is none, displays error
                        mode = Error;
                        b = 4;
                    }
                }
                if (stored_key == 3) {
                    LCD_WriteStringAtPos("Showing Passcode ", 0, 0);
                    LCD_WriteStringAtPos("   For Car 2    ", 1, 0);
                    SSD_WriteDigits(passWord[2][0], passWord[2][1], passWord[2][2], passWord[2][3], 0, 0, 0, 0);//Displays the stored 4-digit passcode on the SSD
                    if (passWord[2][0] == 0 && passWord[2][1] == 0 && passWord[2][2] == 0 && passWord[2][3] == 0) {//Checks for passcode/ key input for an empty spot; If there is none, displays error
                        mode = Error;
                        b = 4;
                    }
                }
                if (stored_key == 4) {
                    LCD_WriteStringAtPos("Showing Passcode ", 0, 0);
                    LCD_WriteStringAtPos("   For Car 3    ", 1, 0);
                    SSD_WriteDigits(passWord[3][0], passWord[3][1], passWord[3][2], passWord[3][3], 0, 0, 0, 0);//Displays the stored 4-digit passcode on the SSD
                    if (passWord[3][0] == 0 && passWord[3][1] == 0 && passWord[3][2] == 0 && passWord[3][3] == 0) {//Checks for passcode/ key input for an empty spot; If there is none, displays error
                        mode = Error;
                        b = 4;
                    }
                }
                if (stored_key == 5) {
                    LCD_WriteStringAtPos("Showing Passcode ", 0, 0);
                    LCD_WriteStringAtPos("   For Car 4    ", 1, 0);
                    SSD_WriteDigits(passWord[4][0], passWord[4][1], passWord[4][2], passWord[4][3], 0, 0, 0, 0);//Displays the stored 4-digit passcode on the SSD
                    if (passWord[4][0] == 0 && passWord[4][1] == 0 && passWord[4][2] == 0 && passWord[4][3] == 0) {//Checks for passcode/ key input for an empty spot; If there is none, displays error
                        mode = Error;
                        b = 4;
                    }
                }
                if (stored_key == 6) {
                    LCD_WriteStringAtPos("Showing Passcode ", 0, 0);
                    LCD_WriteStringAtPos("   For Car 5    ", 1, 0);
                    SSD_WriteDigits(passWord[5][0], passWord[5][1], passWord[5][2], passWord[5][3], 0, 0, 0, 0);//Displays the stored 4-digit passcode on the SSD
                    if (passWord[5][0] == 0 && passWord[5][1] == 0 && passWord[5][2] == 0 && passWord[5][3] == 0) {//Checks for passcode/ key input for an empty spot; If there is none, displays error
                        mode = Error;
                        b = 4;
                    }
                }
                if (stored_key == 7) {
                    LCD_WriteStringAtPos("Showing Passcode ", 0, 0);
                    LCD_WriteStringAtPos("   For Car 6    ", 1, 0);
                    SSD_WriteDigits(passWord[6][0], passWord[6][1], passWord[6][2], passWord[6][3], 0, 0, 0, 0);//Displays the stored 4-digit passcode on the SSD
                    if (passWord[6][0] == 0 && passWord[6][1] == 0 && passWord[6][2] == 0 && passWord[6][3] == 0) {//Checks for passcode/ key input for an empty spot; If there is none, displays error
                        mode = Error;
                        b = 4;
                    }
                }
                if (stored_key == 8) {
                    LCD_WriteStringAtPos("Showing Passcode ", 0, 0);
                    LCD_WriteStringAtPos("   For Car 7    ", 1, 0);
                    SSD_WriteDigits(passWord[7][0], passWord[7][1], passWord[7][2], passWord[7][3], 0, 0, 0, 0);//Displays the stored 4-digit passcode on the SSD
                    if (passWord[7][0] == 0 && passWord[7][1] == 0 && passWord[7][2] == 0 && passWord[7][3] == 0) {//Checks for passcode/ key input for an empty spot; If there is none, displays error
                        mode = Error;
                        b = 4;
                    }
                }

        }



    }
}

void __ISR(_TIMER_3_VECTOR)Timer3ISR(void) {
   
    if (mode == Passcode) { //When in mode: Passcode
        char buffer[16]; //Used to set up display for time left
        sprintf(buffer, " %d seconds left ", count); //Decrements time from 10 to 0
        LCD_WriteStringAtPos(buffer, 1, 0);// Displays seconds left to enter passcode on LCD
        count--;// Decrements count

        if (count == 0) { //When 0 seconds left
            mode = Error; //Mode goes to Error
            b = 1; //Goes to Error E555, Passcode Timeout
            count = 10; //Resets count

        }
    }
    if (mode == Carin) {//When in mode: Carin
        count--;// Count decrements

        LED_SetGroupValue(LED);
        if (count < 0) { //For count lower than 0
            count = 10; // Count goes up to 10
        }
        if (count == 8) { 
            mode = Initial;
            count = 10;
            state_led++;
        }
        if (count == 9) {
            LED = LED << 1;
            indx++;
        }
        if (state_led > 9) {
            mode = Error;
            b = 0;
            LED = LED;
        }
    }
    if (mode == Error) {

        count--;

        if (count < 0) {
            count = 10;
        }
        if (count % 2 == 0) {
            if (b == 0) {
                mode = Initial;
                count = 10;
                RGBLED_SetValue(0, 0, 0);
            }
        } else {
            RGBLED_SetValue(1, 1, 1);
        }
        if (count % 2 == 0) {
            if (b == 1) {
                mode = Initial;

                count = 10;


                RGBLED_SetValue(0, 0, 0);
            }
        } else {
            RGBLED_SetValue(1, 1, 1);
        }
        if (count % 2 == 0) {
            if (b == 2) {
                mode = Initial;

                count = 10;


                RGBLED_SetValue(0, 0, 0);
            }
        } else {
            RGBLED_SetValue(1, 1, 1);
        }
        if (count % 2 == 0) {
            if (b == 4) {
                mode = Initial;

                count = 10;


                RGBLED_SetValue(0, 0, 0);
            }
        } else {
            RGBLED_SetValue(1, 1, 1);
        }
        if (va1 == 9) {
            if (count % 2 == 0) {

                mode = Initial;

                count = 10;


                RGBLED_SetValue(0, 0, 0);
            } else {
                RGBLED_SetValue(1, 1, 1);
            }
        }
    }
    if (mode == Carout) {
        count--;

        if (count < 0) {
            count = 10;
        }
        if (count % 2 == 0) {
            mode = Initial;
            count = 10;

        }
    }
    if (mode == Check) {
        count--;
        if (count < 0) {
            count = 10;
        }
        if (count == 8) {
            mode = Initial;
            count = 10;
        }
    }



    IFS0bits.T3IF = 0; // clear interrupt flag
    IEC0bits.T3IE = 1; // enable interrupt
}

void Timer3_Setup() {
    PR3 = (int) (((float) (1 * 10000000) / 256) + 0.5); //set period register, generates one interrupt every 3 ms
    TMR3 = 0; // initialize count to 0
    //PR3 = 0xFFFF; // Set period of Timer3
    //T3CON = 0x8030; // Enable Timer3 Set Priority
    T3CONbits.TCKPS = 7; // 1:64 prescale value
    T3CONbits.TGATE = 0; // not gated input (default)
    T3CONbits.TCS = 0; // PCBLK input (default)
    T3CONbits.ON = 1; // turn on Timer1
    IPC3bits.T3IP = 6; // priority
    IPC3bits.T3IS = 3; // subpriority
    IFS0bits.T3IF = 0; // clear interrupt flag
    IEC0bits.T3IE = 1; // enable interrupt
    macro_enable_interrupts(); // enable interrupts at CPU
}

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
    IEC1bits.CNDIE = 0;

    // 2. Debounce keys for 10ms
    for (int i = 0; i < 1426; i++) {
    }

    // 3. Handle "button locking" logic

    unsigned char key_is_pressed = (!C1 || !C2 || !C3 || !C4);
    // If a key is already pressed, don't execute the rest second time to eliminate double pressing
    if (!key_is_pressed) {
        new_press = FALSE;
    } else if (!new_press) {
        new_press = TRUE;

        // 4. Decode which key was pressed

        // check first row 
        R1 = 0; //R1 is set to 0
        R2 = R3 = R4 = 1; //Other rows set to 1
        if (C1 == 0) { 
            key = K1; //R1 C1 is 1 on the Keypad
        }// first column
        else if (C2 == 0) {
            key = K2; //R1 C2 is 2 on the Keypad
        }// second column
        else if (C3 == 0) {
            key = K3; //R1 C3 is 3 on the Keypad
        }// third column
        else if (C4 == 0) {
            key = K_A; //R1 C3 is A on the Keypad
        } // fourth column

        // check second row 
        R2 = 0; //R2 is set to 0
        R1 = R3 = R4 = 1; //Other rows set to 1
        if (C1 == 0) {
            key = K4; //R2 C1 is 4 on the Keypad
        } else if (C2 == 0) {
            key = K5; //R2 C2 is 5 on the Keypad
        } else if (C3 == 0) {
            key = K6; //R2 C3 is 6 on the Keypad
        } else if (C4 == 0) {
            key = K_B; //R2 C4 is B on the Keypad
        }

        // check third row 
        R3 = 0; //R3 is set to 0
        R1 = R2 = R4 = 1; //Other rows set to 1
        if (C1 == 0) {
            key = K7; //R3 C1 is 7 on the Keypad
        } else if (C2 == 0) {
            key = K8; //R3 C2 is 8 on the Keypad
        } else if (C3 == 0) {
            key = K9; //R3 C3 is 9 on the Keypad
        } else if (C4 == 0) {
            key = K_C; //R3 C4 is C on the Keypad
        }

        // check fourth row 
        R4 = 0; //R4 is set to 0
        R1 = R2 = R3 = 1; //Other rows set to 1
        if (C1 == 0) {
            key = K0; //R4 C1 is 0 on the Keypad
        } else if (C2 == 0) {
            key = K_F; //R4 C2 is F on the Keypad
        } else if (C3 == 0) {
            key = K_E; //R4 C3 is E on the Keypad
        } else if (C4 == 0) {
            key = K_D; //R4 C4 is D on the Keypad
        }

        // re-enable all the rows for the next round
        R1 = R2 = R3 = R4 = 0;

    }

    // If any key has been pressed, update next state and outputs
    if (key != K_NONE) {
        handle_new_keypad_press(key);
    }


    int j = PORTD; //read port to clear mismatch on CN pints

    // 5. Clear the interrupt flag
    IFS1bits.CNDIF = 0;

    // 6. Reenable CN interrupts
    IEC1bits.CNDIE = 1;
}

void handle_new_keypad_press(eKey key) {

    switch (mode) {
        case Initial: //For Intial/REady mode

            if (key == K_E) { //When E is pressed we go to Mode EnterCode/ Passcode

                mode = Passcode;
                //Update SSD/ cleared 
                d1 = 90;
                d2 = 90;
                d3 = 90;
                d4 = 90;
            }
            
            //If statements below only execute for numerical values
            if (key == K0) { //For car 0 when 0 is pressed on the keypad

                mode = Check;//Mode: Check entered
                stored_key = 1; //First key/ random 4 digit password stored is now used in 'Check' mode to display value on SSD

            }
            if (key == K1) { //For car 1 when 1 is pressed on the keypad

                mode = Check;
                stored_key = 2; //Second key/ random 4 digit password stored is now used in 'Check' mode to display value on SSD

            }
            if (key == K2) { //For car 2 when 2 is pressed on the keypad
                mode = Check;
                stored_key = 3; //Third key/ random 4 digit password stored is now used in 'Check' mode to display value on SSD

            }
            if (key == K3) { //For car 3 when 3 is pressed on the keypad
                mode = Check;
                stored_key = 4; //Fourth key/ random 4 digit password stored is now used in 'Check' mode to display value on SSD

            }
            if (key == K4) { //For car 4 when 4 is pressed on the keypad
                mode = Check;
                stored_key = 5; //Fifth key/ random 4 digit password stored is now used in 'Check' mode to display value on SSD

            }
            if (key == K5) { //For car 5 when 5 is pressed on the keypad
                mode = Check;
                stored_key = 6; //Sixth key/ random 4 digit password stored is now used in 'Check' mode to display value on SSD

            }
            if (key == K6) { //For car 6 when 6 is pressed on the keypad
                mode = Check;
                stored_key = 7; //Seventh key/ random 4 digit password stored is now used in 'Check' mode to display value on SSD
            }
            if (key == K7) { //For car 7 when 7 is pressed on the keypad
                mode = Check;
                stored_key = 8; //Eighth key/ random 4 digit password stored is now used in 'Check' mode to display value on SSD
            }

            break;

        case Passcode: //For entering 4 digit passcode
            //do not print LCD, SSD     
            //Start

            if (key >= 0 && key <= 9) { //Only numerical values in keypad would work
               // Assignments for d4 to d1 represent left shifts by 1 each time keypad is pressed. 
               //d4 receives most recently entered keypad value
                d4 = d3; 
                d3 = d2; 
                d2 = d1; 
                d1 = key; 
            }
            if (key == K_C) { //Clears the SSD when C is pressed on the keypad
                d4 = 90;
                d3 = 90;
                d2 = 90;
                d1 = 90;
            }
            if (key == K_B) { //Right shift by one, clearing rightmost value or d4 when B is pressed on the Keypad
                d1 = d2;
                d2 = d3;
                d3 = d4;
                d4 = 90;
            }
            if (key == K_NONE) {//When no Keys are pressed on the keypad, we are in Ready/ Initial mode
                mode = Initial;
            }
            if (key == K_E) { //For when Keypad entry is E, prompts passcode entry from the user
                mode == Passcode; //When mode is passcode
                //SSD_WriteDigits(d1, d2, d3, d4, 0, 0, 0, 0);
                for (is = 0; is < 8; is++) {
                    
                    //Checks whether value stored in array passWord[8][4] matches entered value from the Keypad
                    if (passWord[0][0] == d1 && passWord[0][1] == d2 && passWord[0][2] == d3 && passWord[0][3] == d4 && key == K_E) {
                        match = 1; //if true, we get a match between entry and stored value
                        
                    } 
                    //Checks whether value stored in array passWord[8][4] matches entered value from the Keypad
                    if (passWord[1][0] == d1 && passWord[1][1] == d2 && passWord[1][2] == d3 && passWord[1][3] == d4 && key == K_E) {
                        match = 1; //if true, we get a match between entry and stored value
                        

                    }
                    //Checks whether value stored in array passWord[8][4] matches entered value from the Keypad
                    if (passWord[2][0] == d1 && passWord[2][1] == d2 && passWord[2][2] == d3 && passWord[3][3] == d4 && key == K_E) {
                        match = 1; //if true, we get a match between entry and stored value
                        

                    }
                    //Checks whether value stored in array passWord[8][4] matches entered value from the Keypad
                    if (passWord[3][0] == d1 && passWord[3][1] == d2 && passWord[3][2] == d3 && passWord[3][3] == d4 && key == K_E) {
                        match = 1; //if true, we get a match between entry and stored value
                        

                    }
                    //Checks whether value stored in array passWord[8][4] matches entered value from the Keypad
                    if (passWord[4][0] == d1 && passWord[4][1] == d2 && passWord[4][2] == d3 && passWord[4][3] == d4 && key == K_E) {
                        match = 1; //if true, we get a match between entry and stored value
                        

                    }
                    //Checks whether value stored in array passWord[8][4] matches entered value from the Keypad
                    if (passWord[5][0] == d1 && passWord[5][1] == d2 && passWord[5][2] == d3 && passWord[5][3] == d4 && key == K_E) {
                        match = 1; //if true, we get a match between entry and stored value
                        

                    }
                    //Checks whether value stored in array passWord[8][4] matches entered value from the Keypad
                    if (passWord[6][0] == d1 && passWord[6][1] == d2 && passWord[6][2] == d3 && passWord[6][3] == d4 && key == K_E) {
                        match = 1; //if true, we get a match between entry and stored value
                        

                    }
                    //Checks whether value stored in array passWord[8][4] matches entered value from the Keypad
                    if (passWord[7][0] == d1 && passWord[7][1] == d2 && passWord[7][2] == d3 && passWord[7][3] == d4 && key == K_E) {
                        match = 1;

                    } else {
                        mode = Error;
                        va1 = 9;
                    }
                    break;

                }
                if (match == 1) { //When match = 1 for the above statements
                    //                     LED_SetGroupValue(LED);
                    mode = Carout; // Mode: Carout is entered
                    if (passWord[0][0] == d1 && passWord[0][1] == d2 && passWord[0][2] == d3 && passWord[0][3] == d4) {//if password is for Car 0
                        va1 = 1; //LED 0 turned back on
                        if (va2 == 1) { 
                            mode = Error;
                            b = 2;
                        }
                    }
                    if (passWord[1][0] == d1 && passWord[1][1] == d2 && passWord[1][2] == d3 && passWord[1][3] == d4) {//if password is for Car 1
                        va1 = 2;
                        if (va2 == 2) {
                            mode = Error;
                            b = 2;
                        }
                    }


                    if (passWord[2][0] == d1 && passWord[2][1] == d2 && passWord[2][2] == d3 && passWord[2][3] == d4) {//if password is for Car 2
                        va1 = 3;
                        if (va2 == 3) {
                            mode = Error;
                            b = 2;
                        }
                    }

                    if (passWord[3][0] == d1 && passWord[3][1] == d2 && passWord[3][2] == d3 && passWord[3][3] == d4) {//if password is for Car 3
                        va1 = 4;
                        if (va2 == 4) {
                            mode = Error;
                            b = 2;
                        }
                    }

                    if (passWord[4][0] == d1 && passWord[4][1] == d2 && passWord[4][2] == d3 && passWord[4][3] == d4) {//if password is for Car 4
                        va1 = 5;
                        if (va2 == 5) {
                            mode = Error;
                            b = 2;
                        }
                    }

                    if (passWord[5][0] == d1 && passWord[5][1] == d2 && passWord[5][2] == d3 && passWord[5][3] == d4) {//if password is for Car 5
                        va1 = 6;
                        if (va2 == 6) {
                            mode = Error;
                            b = 2;
                        }
                    }

                    if (passWord[6][0] == d1 && passWord[6][1] == d2 && passWord[6][2] == d3 && passWord[6][3] == d4) {//if password is for Car 6
                        va1 = 7;
                        if (va2 == 7) {
                            mode = Error;
                            b = 2;
                        }
                    }

                    if (passWord[7][0] == d1 && passWord[7][1] == d2 && passWord[7][2] == d3 && passWord[7][3] == d4) {//if password is for Car 7

                        va1 = 8;
                        if (va2 == 8) {
                            mode = Error;
                            b = 2;
                        }
                    }

                }

                SSD_WriteDigits(d1, d2, d3, d4, 0, 0, 0, 0);


                break;
     
            }
    }
}
