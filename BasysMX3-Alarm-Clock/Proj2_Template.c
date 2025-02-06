/*===================================CPEG222====================================
 * Program: Project 2: Alarm Clock
 * Authors:  Martin Olguin and Furdeen Hasan
 * Date:  10/08/2022
 * Description: This code uses all 5 on-board BTNs to control
 * the alarm, the alarm starts in mode 1 where it asks the user to set time,
 * Buttons U will increase the time within the range of 00:00 to 23:59 and button D will
 * decrease the time within the same range. Also button L will change between minutes 
 * and hours. Button C changes between modes, once clock is set user will press the
 *  btn C and go to the set alarm mode where they will 
 * set the alarm the same way that we set the time, but the only difference is that
 * the time starts at 12:00. Once again button C will be pressed and the SSD will
 * display time. once the time reaches the alarm time it will turn on for 10 seconds
 * and will go off on its own after 10 seconds or after user presses buttons C and R 
 * at the same time. Button R will return the user back to mode 1.
 * Output: Time is displayed on SSD.
==============================================================================*/
/*---- Board system settings. PLEASE DO NOT MODIFY THIS PART FOR PROJECT 1 ---*/
#ifndef _SUPPRESS_PLIB_WARNING //suppress the plib warning during compiling
#define _SUPPRESS_PLIB_WARNING
#endif
#pragma config FPLLIDIV = DIV_2 // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20 // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_1 // System PLL Output Clock Divider 
//(PLL Divide by 1)
#pragma config FNOSC = PRIPLL   // Oscillator Selection Bits (Primary Osc w/PLL 
//(XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF    // Secondary Oscillator Enable (Disabled)
#pragma config POSCMOD = XT     // Primary Oscillator Configuration (XT osc mode)
#pragma config FPBDIV = DIV_8   // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
/*----------------------------------------------------------------------------*/
#include <xc.h>     //Microchip XC processor header which links to the 
//PIC32MX370512L header
#include <sys/attribs.h>
#include "config.h" // Basys MX3 configuration header
#include "lcd.h"    // NOTE: utils.c and utils.h must also be in your project 
//to use lcd.c
#include"ssd.h"
#include <stdio.h>
#include <xc.h>
/* --------------------------- Forward Declarations-------------------------- */
void initialize_ports(); // function that configures SSD
void handle_button_presses(); //function that controls buttons
void delay_ms(int milliseconds); //function to control delay
void turnOnAlarm(); // function to turn on alarm
void turnOffAlarm(); // function to turn alarm off
/* ------------------------ Constant Definitions ---------------------------- */
#define SYS_FREQ (80000000L) // 80MHz system clock
#define _80Mhz_ (80000000L)
#define LOOPS_NEEDED_TO_DELAY_ONE_MS_AT_80MHz 1426
#define LOOPS_NEEDED_TO_DELAY_ONE_MS (LOOPS_NEEDED_TO_DELAY_ONE_MS_AT_80MHz * (SYS_FREQ / _80Mhz_))
/* The Basys reference manual shows to which pin of the processor every IO 
connects. 
 BtnC connects to Port F pin 0. PORTF reads output values from Port F pins.
 LATF would be used to read input values on Port F pins and TRISF would be used to
 set tristate values of Port F pins. We will see LAT and TRIS later. */
#define BtnC_RAW PORTFbits.RF0  //set variable to button C port
#define BtnU_RAW PORTBbits.RB1  // sets variable to button U port
#define BtnL_RAW PORTBbits.RB0  // sets variable to button L port
#define BtnD_RAW PORTAbits.RA15  // sets variable to button D port
#define BtnR_RAW PORTBbits.RB8  // sets variable to button R port
#define TRUE 1                  // sets true to 1
#define FALSE 0                 // sets flase to 0
#define BUTTON_DEBOUNCE_DELAY_MS 20  // sets variable to 20 ms


/***** This section contains variables for the speaker ******/
#define TMR_FREQ_SINE   48000 // 48 kHz
// This array contains the values that implement one syne period, over 25 samples. 
// They are generated using this site: 
// http://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml
unsigned short rgSinSamples [] = {
    256, 320, 379, 431, 472, 499, 511, 507, 488, 453,
    406, 350, 288, 224, 162, 106, 59, 24, 5, 1,
    13, 40, 81, 133, 192
};

#define RGSIN_SIZE  (sizeof(rgSinSamples) / sizeof(rgSinSamples[0]))

// the array of samples, to be stored when recording (Mode 2) and to be played when playing back (Mode 3).
unsigned short *pAudioSamples;

// global variables that store audio buffer position and size
int cntAudioBuf, idxAudioBuf;

/***** End of speaker declarations  ******/

typedef enum {
    ALARM_ON, ALARM_OFF
} eModes;
/* -------------------- Global Variable Declarations ------------------------ */
char buttonsLockedC = FALSE; // variable that will help in debounce of button 
char pressedUnlockedBtnC = FALSE; // variable that will help in debounce of button 
char buttonsLockedU = FALSE; // variable that will help in debounce of button 
char pressedUnlockedBtnU = FALSE; // variable that will help in debounce of button 
char buttonsLockedL = FALSE; // variable that will help in debounce of button 
char pressedUnlockedBtnL = FALSE; // variable that will help in debounce of button 
char buttonsLockedD = FALSE; // variable that will help in debounce of button 
char pressedUnlockedBtnD = FALSE; // variable that will help in debounce of button
char buttonsLockedR = FALSE; // variable that will help in debounce of button 
char pressedUnlockedBtnR = FALSE; // variable that will help in debounce of button 
char buttonsLockedCandR = FALSE; // variable that will help in debounce of button 
char pressedUnlockedBtnCandR = FALSE; // variable that will help in pressing two buttons at the same time
eModes mode = ALARM_OFF;
char state = 0; //variable for modes
char min1 = 0; // variable for minutes (ones)
char min10 = 0; // variable for minutes (tens)
char hr1 = 0; // variable for hours
char hr10 = 0; // variable for hours
int Ls = 0; // variable to help with button L
int sec = 0; // variable to help with button response
char X1; // alarm variable for hrs
char X2; // alarm variable for hrs
char Y1; // alarm variable for mins
char Y2; //alarm variable for mins
int i = 0; // variable to help with alarm length
char dp1; // variable to aid with ssd display
char dp2; // variable to aid with ssd display
char dp3; // variable to aid with ssd display
char dp4; // variable to aid with ssd display
unsigned char number [] = {// chart that will de called upon to display numbers on SSD
    0b1000000, //0
    0b1111001, //1
    0b0100100, //2
    0b0110000, //3
    0b0011001, //4
    0b0010010, //5
    0b0000010, //6
    0b1111000, //7
    0b0000000, //8
    0b0010000, //9
    0b1111111, // clear
};

/* ----------------------------- Main --------------------------------------- */

int main(void) {
    /*-------------------- Port and State Initialization -------------------------
     */
    initialize_ports(); // calls all defined ports
    LCD_WriteStringAtPos("    Group 7     ", 0, 0); // will display group number on LCD

    while (TRUE) {


        /*-------------------- Main logic and actions start 
--------------------------*/
        handle_button_presses(); // calls for function that controls button presses
        if (pressedUnlockedBtnL) { // function that will change the variable each time Btn L is pressed
            Ls = !Ls;
        }
        // will increase time on the background so even when you are on alarm time will be passing
        if (state != 0) { // works only when state is not 0
            if (sec++ > 50) { // will check for button press multiple time to have a more sensitive button
                sec = 0;
                if (min1 == 9) { //  checks once the first min digit reaches 9
                    if (min10 == 5) { // checks once second min digit reaches 5
                        if (hr10 == 2 && hr1 == 3) { //  checks if hrs equal 23
                            hr10 = 0; // will reset all digits back to 0 when its 23:59
                            hr1 = 0;
                            min10 = 0;
                            min1 = 0;
                        } else if (hr1 == 9) { //checks ones the hour digit reaches 9
                            hr10++; // will update the second hrs digit and will reset the other hr and 2 min digits back to 0
                            hr1 = 0;
                            min10 = 0;
                            min1 = 0;

                        } else { // if not it will continue to raise the first hr digit by one once minutes reach 59
                            hr1++;
                            min10 = 0;
                            min1 = 0;
                        }
                    } else { // once the first minute digit reaches 9 it will go back to 0 and increase the second min digit by one
                        min1 = 0;
                        min10++;
                    }
                } else { // if the first minute digit is not 9 it will continue to increase by 1
                    min1++;

                }
            }
        }
        switch (state) { //function that helps set and change between states

            case 0: // state 0


                LCD_WriteStringAtPos("   Set  Clock   ", 1, 0); // LCD will display set clock

                if (pressedUnlockedBtnR) { // if button R is pressed the SSD will reset to 00:00
                    min1 = 0;
                    min10 = 0;
                    hr1 = 0;
                    hr10 = 0;
                } else if (pressedUnlockedBtnC) { // checks if button C is pressed and if so it will move to state 1 (Set Alarm) and set SSD to 12:00
                    state = 1;
                    X1 = 1;
                    X2 = 2;
                    Y1 = 0;
                    Y2 = 0;
                }
                if (!Ls) { // checks if button L is not pressed and if its not pressed it will update minutes
                    dp1 = 1; // will aid user by telling them they are changing minutes
                    dp2 = 1; // will aid user by telling them they are changing minutes
                    dp3 = 0;
                    dp4 = 0;
                    if (pressedUnlockedBtnU) { // will check if button U is pressed and if so it will increase the value of minutes by one for each button press
                        if (min1 == 9) {
                            if (min10 == 5) {
                                min1 = 0;
                                min10 = 0;

                            } else {
                                min1 = 0;
                                min10++;
                            }
                        } else {
                            min1++;

                        }
                    }
                    if (pressedUnlockedBtnD) { // will check if button D is pressed and if so it will decrease the value of minutes by one for each button press
                        if (min1 == 0) {
                            if (min10 == 0) {
                                min1 = 9;
                                min10 = 5;
                            } else {
                                min1 = 9;
                                min10--;
                            }
                        } else {
                            min1--;
                        }
                    }

                } else { // checks if button L is pressed
                    dp3 = 1; // will help show that user is editing Hrs
                    dp4 = 1; // will help show that user is editing Hrs
                    dp1 = 0;
                    dp2 = 0;
                    if (pressedUnlockedBtnU) { //will check if button U is pressed and if so it will increase the value of hours by one for each button press
                        if (hr10 == 2 && hr1 == 3) {
                            hr10 = 0;
                            hr1 = 0;

                        } else if (hr1 == 9) {
                            hr10++;
                            hr1 = 0;


                        } else {
                            hr1++;

                        }

                    }
                    if (pressedUnlockedBtnD) { //will check if button U is pressed and if so it will decrease the value of hrs by one for each button press
                        if (hr1 == 0) {
                            if (hr10 == 0) {
                                hr1 = 3;
                                hr10 = 2;
                            } else {
                                hr1 = 9;
                                hr10--;
                            }
                        } else {
                            hr1--;
                        }
                    }
                }

                break; //ends state 0

            case 2: // state 2 Display time ( out of order due to mid-stage demo)

                if (pressedUnlockedBtnR) { // will check if button R is pressed is so it will reset time to 00:00 and go back to state 0
                    state = 0;
                    hr10 = 0;
                    hr1 = 0;
                    min10 = 0;
                    min1 = 0;
                } else if (pressedUnlockedBtnC) { // checks if button C is pressed and if it is it will go back to state 1
                    state = 1;

                }

                if ((X1 == hr10) && (X2 == hr1) && (Y1 == min10) && (Y2 == min1)) { // checks if alarm time is equal to set time,if so it will go into state 3
                    state = 3;
                    
                    SSD_WriteDigits(min1, min10, hr1, hr10, dp1, dp2, dp3, dp4); // allows us to display alarm time on SSD
                    
                }
                LCD_WriteStringAtPos("  Display Time   ", 1, 0); // will display time on LCD


                break; // ends state 2

            case 1: // state 1 setting alarm

                LCD_WriteStringAtPos("   Set Alarm   ", 1, 0); // will display set alarm on SSD
                if (pressedUnlockedBtnR) { // will check if button R is pressed and if so will go to state 0 and reset time to 00:00
                    state = 0;
                    hr10 = 0;
                    hr1 = 0;
                    min10 = 0;
                    min1 = 0;
                } else if (pressedUnlockedBtnC) { // will check if button C is pressed if so it will move state 2
                    state = 2;

                }

                if (!Ls) { // checks if button L is not pressed and if its not pressed it will update minutes
                    dp1 = 1; // will aid user by telling them they are changing minutes
                    dp2 = 1; // will aid user by telling them they are changing minutes
                    dp3 = 0;
                    dp4 = 0;
                    if (pressedUnlockedBtnU) { // will check if button U is pressed and if so it will increase the value of minutes by one for each button press
                        if (Y2 == 9) {
                            if (Y1 == 5) {
                                Y2 = 0;
                                Y1 = 0;

                            } else {
                                Y2 = 0;
                                Y1++;
                            }
                        } else {
                            Y2++;

                        }
                    }
                    if (pressedUnlockedBtnD) { // will check if button D is pressed and if so it will decrease the value of minutes by one for each button press
                        if (Y2 == 0) {
                            if (Y1 == 0) {
                                Y2 = 9;
                                Y1 = 5;
                            } else {
                                Y2 = 9;
                                Y1--;
                            }
                        } else {
                            Y2--;
                        }
                    }

                } else { // checks if button L is pressed
                    dp3 = 1; // will help show that user is editing Hrs
                    dp4 = 1; // will help show that user is editing Hrs
                    dp1 = 0;
                    dp2 = 0;
                    if (pressedUnlockedBtnU) { //will check if button U is pressed and if so it will increase the value of hours by one for each button press
                        if (X1 == 2 && X2 == 3) {
                            X1 = 0;
                            X2 = 0;

                        } else if (X2 == 9) {
                            X1++;
                            X2 = 0;


                        } else {
                            X2++;

                        }

                    }
                    if (pressedUnlockedBtnD) { //will check if button U is pressed and if so it will decrease the value of hrs by one for each button press
                        if (X2 == 0) {
                            if (X1 == 0) {
                                X2 = 3;
                                X1 = 2;
                            } else {
                                X2 = 9;
                                X1--;
                            }
                        } else {
                            X2--;
                        }
                    }

                }


                break; //ends state 1

            case 3: //state 3 alarming


                if (i == 560) { // alarm will go off for 10 seconds once the 10 seconds pass it will go to state 2 and turn off alarm
                    turnOffAlarm();
                    state = 2;
                    
                } 
                
                else { // alarm and counter will continue going
                    if( i% 5 == 1){
                    SSD_WriteDigits(90, 90, 90, 90, 0, 0, 0, 0);
                    }
                    else if( i% 5 == 0){
                       SSD_WriteDigits(Y2, Y1, X2, X1, dp1, dp2, dp3, dp4); 
                    }
                    turnOnAlarm();
                    i++;
                }



                LCD_WriteStringAtPos("   Alarming   ", 1, 0); // the LCD will display Alarming


                if (pressedUnlockedBtnCandR) { // checks if both button C and R are pressed which will turn off the alarm and go to state 2
                    turnOffAlarm();
                    LCD_WriteStringAtPos("   Alarming   ", 1, 0);
                    state = 2;
                }

                break; // end of state 3

        }



        if (state == 0 || state == 2) { // will display normal SSD in state 0 and 2

            SSD_WriteDigits(min1, min10, hr1, hr10, dp1, dp2, dp3, dp4); // displays digits on SSD
        } else if (state == 1) { // will display alarm digits in state 1

            SSD_WriteDigits(Y2, Y1, X2, X1, dp1, dp2, dp3, dp4); // displays alarm digits on SSD
        }
        delay_ms(10); // delays code for 15ms for debounce and SSD flickering
        /*--------------------- Action and logic end 
        ---------------------------------*/
    }
}

/* -------------------------- Function Definitions 
---------------------------------- */
void initialize_ports() {
    DDPCONbits.JTAGEN = 0; // Required to use Pin RA0 (connected to LED 0) as IO

    /* The following line sets the tristate of Port F bit 0 to 1.
     *  BtnC is connected to that pins. When the tristate of a pin is set high,
     *  the pin is configured as a digital input. */
    TRISFbits.TRISF0 = 1;
    TRISBbits. TRISB1 = 1; //Configure PortB bit 1 (BTNU) as inputs
    ANSELBbits.ANSB1 = 0;
    TRISBbits.TRISB0 = 1; // RB1 (BTNL) configured as input 
    ANSELBbits.ANSB0 = 0; // RB1 (BTNL) disabled analog 
    TRISFbits.TRISF4 = 1; // RF0 (BTNC) configured as input  
    TRISBbits.TRISB8 = 1; // RB8 (BTNR) configured as input 
    ANSELBbits.ANSB8 = 0; // RB8 (BTNR) disabled analog 
    TRISAbits.TRISA15 = 1; // RA15 (BTND) configured as input

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
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSB1 = 0;
    LCD_Init(); // A library function provided by Digilent
    SSD_Init(); //SSD Init

    // the following lines configure interrupts to control the speaker
    T3CONbits.ON = 0; // turn off Timer3
    OC1CONbits.ON = 0; // Turn off OC1
    /* The following code sets up the alarm timer and interrupts */
    tris_A_OUT = 0;
    rp_A_OUT = 0x0C; // 1100 = OC1
    // disable analog (set pins as digital)
    ansel_A_OUT = 0;

    T3CONbits.TCKPS = 0; //1:1 prescale value
    T3CONbits.TGATE = 0; //not gated input (the default)
    T3CONbits.TCS = 0; //PCBLK input (the default)

    OC1CONbits.ON = 0; // Turn off OC1 while doing setup.
    OC1CONbits.OCM = 6; // PWM mode on OC1; Fault pin is disabled
    OC1CONbits.OCTSEL = 1; // Timer3 is the clock source for this Output Compare module

    IPC3bits.T3IP = 7; // interrupt priority
    IPC3bits.T3IS = 3; // interrupt subpriority

    macro_enable_interrupts(); // enable interrupts at CPU

}

/* This below function turns on the alarm*/
void turnOnAlarm() {
    //set up alarm
    PR3 = (int) ((float) ((float) PB_FRQ / TMR_FREQ_SINE) + 0.5);
    idxAudioBuf = 0;
    cntAudioBuf = RGSIN_SIZE;
    pAudioSamples = rgSinSamples;

    // load first value
    OC1RS = pAudioSamples[0];
    TMR3 = 0;

    T3CONbits.ON = 1; //turn on Timer3
    OC1CONbits.ON = 1; // Start the OC1 module  
    IEC0bits.T3IE = 1; // enable Timer3 interrupt    
    IFS0bits.T3IF = 0; // clear Timer3 interrupt flag
}

/* This below function turns off the alarm*/
void turnOffAlarm() {
    T3CONbits.ON = 0; // turn off Timer3
    OC1CONbits.ON = 0; // Turn off OC1
}

/* The below function only handles BtnC presses. Think about how it could be
 expanded to handle all button presses.*/
void handle_button_presses() {
    pressedUnlockedBtnC = FALSE; // sets that button is not unlocked
    if (BtnC_RAW && !buttonsLockedC) { // checks if the button is pressed and if button is locked (true instead of false)
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce  will help prevent the noise that the button causes until it settles
        buttonsLockedC = TRUE; // changes the state of buttonLocked to true
        pressedUnlockedBtnC = TRUE; // changes the state of buttonunlocked to true
    } else if (!BtnC_RAW && buttonsLockedC) { // checks if button was not pressed and if button is locked
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce helps with the noise the button causes when pressed
        buttonsLockedC = FALSE; // keeps button locked
    }
    pressedUnlockedBtnU = FALSE; // sets that button is not unlocked
    if (BtnU_RAW && !buttonsLockedU) { // checks if the button is pressed and if button is locked(true instead of false)
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce  will help prevent the noise that the button causes until it settles
        buttonsLockedU = TRUE; // changes the state of buttonLocked to true
        pressedUnlockedBtnU = TRUE; // changes the state of buttonunlocked to true
    } else if (!BtnU_RAW && buttonsLockedU) { // checks if button was not pressed and if button is locked
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce helps with the noise the button causes when pressed
        buttonsLockedU = FALSE; // keeps button locked
    }
    pressedUnlockedBtnL = FALSE; // sets that button is not unlocked
    if (BtnL_RAW && !buttonsLockedL) { // checks if the button is pressed and if button is locked(true instead of false)
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce will help prevent the noise that the button causes until it settles
        buttonsLockedL = TRUE; // changes the state of buttonLocked to true
        pressedUnlockedBtnL = TRUE; // changes the state of buttonunlocked to true
    } else if (!BtnL_RAW && buttonsLockedL) { // checks if button was not pressed and if button is locked
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce helps with the noise the button causes when pressed
        buttonsLockedL = FALSE; // keeps button locked
    }
    pressedUnlockedBtnD = FALSE; // sets that button is not unlocked
    if (BtnD_RAW && !buttonsLockedD) { // checks if the button is pressed and if button is locked(true instead of false)
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce will help prevent the noise that the button causes until it settles
        buttonsLockedD = TRUE; // changes the state of buttonLocked to true
        pressedUnlockedBtnD = TRUE; // changes the state of buttonunlocked to true
    } else if (!BtnD_RAW && buttonsLockedD) { // checks if button was not pressed and if button is locked
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce helps with the noise the button causes when pressed
        buttonsLockedD = FALSE; // keeps button locked
    }
    pressedUnlockedBtnR = FALSE; // sets that button is not unlocked
    if (BtnR_RAW && !buttonsLockedR) { // checks if the button is pressed and if button is locked(true instead of false)
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce will help prevent the noise that the button causes until it settles
        buttonsLockedR = TRUE; // changes the state of buttonLocked to true
        pressedUnlockedBtnR = TRUE; // changes the state of buttonunlocked to true
    } else if (!BtnR_RAW && buttonsLockedR) { // checks if button was not pressed and if button is locked
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce  helps with the noise the button causes when pressed
        buttonsLockedR = FALSE; // keeps button locked
    }
    pressedUnlockedBtnCandR = FALSE; // sets that button is not unlocked
    if ((BtnR_RAW && BtnC_RAW && !buttonsLockedCandR)) { // checks if the button is pressed and if button is locked(true instead of false)
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce will help prevent the noise that the button causes until it settles
        buttonsLockedCandR = TRUE; // changes the state of buttonLocked to true
        pressedUnlockedBtnCandR = TRUE; // changes the state of buttonunlocked to true
    } else if ((!BtnR_RAW && !BtnC_RAW && buttonsLockedCandR)) { // checks if button was not pressed and if button is locked
        delay_ms(BUTTON_DEBOUNCE_DELAY_MS); // debounce  helps with the noise the button causes when pressed
        buttonsLockedCandR = FALSE; // keeps button locked
    }
}

void delay_ms(int milliseconds) { // function to help with debounce
    int i;
    for (i = 0; i < milliseconds * LOOPS_NEEDED_TO_DELAY_ONE_MS; i++) {
    }
}

/* ------------------------------------------------------------ */

/***	Timer3ISR
 **
 **	Description:
 **		This is the interrupt handler for Timer3. According to each mode, it is called at specific frequencies, as initialized in AUDIO_Init.
    Mode 0 (Generate sound using sine) - Advance current index in the sine definition buffer, initialize OC1 with the current sine definition value.
 **          
 */
void __ISR(_TIMER_3_VECTOR, IPL7AUTO) Timer3ISR(void) {
    // play sine
    // load sine value into OC register
    OC1RS = 4 * pAudioSamples[(++idxAudioBuf) % cntAudioBuf];

    IFS0bits.T3IF = 0; // clear Timer3 interrupt flag
}
