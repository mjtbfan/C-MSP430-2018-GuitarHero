#include <msp430.h> 
#include <stdlib.h>
#include "peripherals.h"

int beat512 = 0;
int arrayPoint = 0;
int noteCheck = 0;
int quadNote = 0;
int correcNotes = 0;
uint8_t welcomeCount = 3;
uint8_t currNoteCheck = 0;
uint8_t introTimer = 8;
uint8_t lastNote = 0;
static uint8_t song[1536] = {0,0,0,0,0,0,0,0,6,6,6,0,6,6,6,0,6,6,6,6,6,6,6,0,6,6,6,0,
                            6,6,6,0,6,6,6,6,6,6,6,0,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,
                            6,6,6,0,6,6,6,0,6,6,6,6,6,6,6,0,6,6,6,0,6,6,6,0,6,6,6,6,
                            6,6,6,0,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,0,
                            13,13,13,13,13,13,13,0,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,
                            6,6,6,0,6,6,6,0,6,6,6,6,6,6,6,0,6,6,6,0,6,6,6,0,6,6,6,6,
                            6,6,6,0,4,4,4,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,0,0,0,0,0,
                            0,0,0,0,13,13,13,13,13,13,13,0,0,0,0,0,0,0,0,0,14,14,14,
                            14,14,14,14,0,0,0,0,0,0,0,0,0,13,13,13,13,13,13,13,0,0,0,
                            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,6,6,6,0,
                            6,6,6,6,6,6,6,0,6,6,6,0,6,6,6,0,6,6,6,6,6,6,6,0,10,10,10,10,
                            10,10,10,0,0,0,0,0,0,0,0,0,11,11,11,11,11,11,11,0,0,0,0,0,0,0,0,0,
                            13,13,13,13,13,13,13,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,
                            13,13,13,13,13,13,13,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,
                            4,4,4,4,4,4,4,0,1,1,1,1,1,1,1,0,8,8,8,8,8,8,8,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,
                            4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,0,1,1,1,1,1,1,1,0,8,8,8,8,8,8,8,0,
                            8,8,8,8,8,8,8,0,8,8,8,8,8,8,8,0,12,12,12,12,12,12,12,0,6,6,6,6,6,6,6,0,
                            0,0,0,0,0,0,0,0,6,6,6,0,6,6,6,0,6,6,6,6,6,6,6,0,6,6,6,0,6,6,6,0,
                            6,6,6,6,6,6,6,0,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,5,5,5,0,5,5,5,0,
                            6,6,6,6,6,6,6,0,6,6,6,0,6,6,6,0,6,6,6,6,6,6,6,0,5,5,5,5,5,5,5,0,
                            0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,0,13,13,13,13,13,13,13,0,7,7,7,7,7,7,7,0,
                            0,0,0,0,0,0,0,0,6,6,6,0,6,6,6,0,6,6,6,6,6,6,6,0,6,6,6,0,6,6,6,0,
                            6,6,6,6,6,6,6,0,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,0,
                            0,0,0,0,0,0,0,0,11,11,11,11,11,11,11,0,0,0,0,0,0,0,0,0,14,14,14,14,14,14,14,0,
                            0,0,0,0,0,0,0,0,11,11,11,11,11,11,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                            3,3,3,0,3,3,3,0,3,3,3,3,3,3,3,0,3,3,3,0,3,3,3,0,3,3,3,3,3,3,3,0,
                            10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,11,11,11,11,11,11,11,0,0,0,0,0,0,0,0,0,
                            11,11,11,11,11,11,11,0,0,0,0,0,0,0,0,0,14,14,14,14,14,14,14,0,11,11,11,11,11,11,11,0,
                            0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,0,1,1,1,1,1,1,1,0,8,8,8,8,8,8,8,0,
                            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,4,4,4,4,4,4,4,0,
                            0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,0,1,1,1,1,1,1,1,0,8,8,8,8,8,8,8,0,
                            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
                            4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,
                            8,8,8,8,8,8,8,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,
                            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,
                            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,
                            8,8,8,8,8,8,8,0,4,4,4,4,4,4,4,0,1,1,1,1,1,1,1,0,5,5,5,5,5,5,5,0,
                            3,3,3,3,3,3,3,0,6,6,6,6,6,6,6,0,8,8,8,8,8,8,8,0,6,6,6,6,6,6,6,0,
                            3,3,3,3,3,3,3,0,12,12,12,12,12,12,12,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
                            4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,12,12,12,12,12,12,12,0,
                            8,8,8,8,8,8,8,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,
                            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,
                            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,
                            8,8,8,8,8,8,8,0,1,1,1,1,1,1,1,0,8,8,8,8,8,8,8,0,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,
                            4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,0,6,6,6,6,6,6,6,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0};

void TimerA2Setup() {
    TA2CTL = (TASSEL_1 + MC_1 + ID_0);
    TA2CCR0 = 200;
    TA2CCTL0 = CCIE;
}

void CountdownSetup() {
    TA2CTL = (TASSEL_1 + MC_1 + ID_0);
    TA2CCR0 = 32768;
    TA2CCTL0 = CCIE;
}

void configButt() {
    P7SEL &= ~(BIT4 | BIT0);
    P2SEL &= ~(BIT2);
    P3SEL &= ~(BIT6);

    P7DIR &= ~(BIT4 | BIT0);
    P2DIR &= ~(BIT2);
    P3DIR &= ~(BIT6);

    P7REN |= (BIT4 | BIT0);
    P2REN |= (BIT2);
    P3REN |= (BIT6);

    P7OUT |= (BIT4 | BIT0);
    P2OUT |= (BIT2);
    P3OUT |= (BIT6);
}

unsigned char readButt() {
    unsigned char out = 0;
    if (!(P7IN & BIT0)) {
        out |= BIT3;
    }
    if (!(P3IN & BIT6)) {
        out |= BIT2;
    }
    if (!(P2IN & BIT2)) {
        out |= BIT1;
    }
    if (!(P7IN & BIT4)) {
        out |= BIT0;
    }
    return out;
}

void busyWorkFunc(char inbits) {
    P1SEL &= ~(BIT0);
    P4SEL &= ~(BIT7);

    P1DIR |= BIT0;
    P4DIR |= BIT7;

    P1OUT &= ~(BIT0);
    P4OUT &= ~(BIT7);

    if (inbits & BIT0) {
        P1OUT |= BIT0;
    }
    if (inbits & BIT1) {
        P4OUT |= BIT7;
    }
}

void buzzz(unsigned char butts) {
    int pitch = 0;
    char notes = 0;
    if (butts == 0) {
        BuzzerOff();
    } else {
        if (butts & BIT3) {
            notes++;
            pitch += 66; // B
        }
        if (butts & BIT2) {
            notes++;
            pitch += 59; // C#
        }
        if (butts & BIT1) {
            notes++;
            pitch += 50; // E
        }
        if (butts & BIT0) {
            notes++;
            pitch += 39; // G#
        }
    }
    if (notes > 0) {
        pitch = pitch / notes;
    }

    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    TB0CCR0   = pitch;                    // Set the PWM period in ACLK ticks
    TB0CCTL0 &= ~CCIE;                  // Disable timer interrupts

    TB0CCTL5  = OUTMOD_7;                   // Set/reset mode for PWM
    TB0CCTL5 &= ~CCIE;                      // Disable capture/compare interrupts
    TB0CCR5   = TB0CCR0/2;                  // Configure a 50% duty cycle
}

void configLEDs() {
    P6SEL &= ~(BIT4|BIT3|BIT2|BIT1);
    P6DIR |=  (BIT4|BIT3|BIT2|BIT1);
    P6OUT &= ~(BIT4|BIT3|BIT2|BIT1);
}

void lightLEDs(unsigned char input) {
    unsigned char temp = 0;
    busyWorkFunc(0);
    P6OUT &= ~(BIT4|BIT3|BIT2|BIT1);
    if (input & BIT3) {
        temp |= BIT2;
    }
    if (input & BIT2) {
        temp |= BIT1;
    }
    if (input & BIT1) {
        temp |= BIT3;
    }
    if (input & BIT0) {
        temp |= BIT4;
    }
    P6OUT |= temp;
}

void stopTimer() {
    TA2CTL = MC_0;
    TA2CCTL0 &= ~CCIE;
}

#pragma vector=TIMER2_A0_VECTOR
__interrupt void TimerA2_ISR() {
    if (welcomeCount >  0) {
        welcomeCount--;
        busyWorkFunc(welcomeCount);
        buzzz(welcomeCount);
    } else {
        if (introTimer > 0) {
            introTimer--;
        } else {
            beat512++;
        }
        if (beat512 == 4) {
            if (song[arrayPoint] != lastNote) {
                lightLEDs(song[arrayPoint]);
                buzzz(song[arrayPoint]);
                if ((readButt() == noteCheck)) {
                    currNoteCheck = 1;
                    if ((arrayPoint % 4) == 0) {
                        if (currNoteCheck == 1) {
                            correcNotes++;
                            currNoteCheck = 0;
                        }
                    }
                }
                lastNote = song[arrayPoint];
            }
            if ((arrayPoint % 4) == 0) {
                quadNote++;
            } else if (((arrayPoint + 1) % 4) == 0) {
                noteCheck = song[arrayPoint + 1];
            }
            arrayPoint++;
            beat512 = 0;
        }
    }
}
/*
void updateScreen(uint8_t *screenArray) {
    uint8_t i;
    uint8_t j;
    for (i = 0; i < 7; i++) {
        screenArray[i + 1] = screenArray[i];
    }
    screenArray[0] = song[quadNote];
    for (j = 0; j < 8; j++) {
        if (screenArray[j] & BIT0) {
            Graphics_drawStringCentered(&g_sContext, "#", AUTO_STRING_LENGTH, 80, (10 * j), OPAQUE_TEXT);
        }
        if (screenArray[j] & BIT1) {
            Graphics_drawStringCentered(&g_sContext, "#", AUTO_STRING_LENGTH, 60, (10 * j), OPAQUE_TEXT);
        }
        if (screenArray[j] & BIT2) {
            Graphics_drawStringCentered(&g_sContext, "#", AUTO_STRING_LENGTH, 40, (10 * j), OPAQUE_TEXT);
        }
        if (screenArray[j] & BIT3) {
            Graphics_drawStringCentered(&g_sContext, "#", AUTO_STRING_LENGTH, 20, (10 * j), OPAQUE_TEXT);
        } else {
            Graphics_drawStringCentered(&g_sContext, "                                      ", AUTO_STRING_LENGTH, 48, (10 * j), OPAQUE_TEXT);
        }
    }
    Graphics_flushBuffer(&g_sContext);
}
*/
void welcomeScreen(void)
{
    uint8_t temp = welcomeCount;
    uint8_t display[1] = {0};
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "ECE 2049", AUTO_STRING_LENGTH, 48, 15, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, "MSP430 HERO", AUTO_STRING_LENGTH, 48, 30, OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext, "PRESS * TO PLAY", AUTO_STRING_LENGTH, 48, 45, OPAQUE_TEXT);
    Graphics_flushBuffer(&g_sContext);
    while (getKey() != '*') {}
    Graphics_clearDisplay(&g_sContext);
    _BIS_SR(GIE);
    CountdownSetup();
    Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48, 48, OPAQUE_TEXT);
    busyWorkFunc(3);
    buzzz(3);
    Graphics_flushBuffer(&g_sContext);
    while (welcomeCount > 0) {
        if (temp != welcomeCount) {
            display[0] = welcomeCount + 0x30;
            Graphics_drawStringCentered(&g_sContext, display, AUTO_STRING_LENGTH, 48, 48, OPAQUE_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }
    }
    stopTimer();
    Graphics_drawStringCentered(&g_sContext, "GOOOO!!!!", AUTO_STRING_LENGTH, 48, 48, OPAQUE_TEXT);
    busyWorkFunc(3);
    buzzz(15);
    Graphics_flushBuffer(&g_sContext);
}

void resetGame() {
    stopTimer();
    buzzz(0);
    lightLEDs(0);
    welcomeCount = 3;
    correcNotes = 0;
    currNoteCheck = 0;
    introTimer = 8;
    lastNote = 0;
    beat512 = 0;
    arrayPoint = 0;
    noteCheck = 0;
    quadNote = 0;
    welcomeScreen();
    _BIS_SR(GIE);
    TimerA2Setup();
}


 int main(void) {
    uint8_t buffer[15];
    //uint8_t screenArray[8] = {0,0,0,0,0,0,0,0};
    WDTCTL = WDTPW | WDTHOLD;// stop watchdog timer
    configDisplay();
    configButt();
    configKeypad();
    configLEDs();
    welcomeScreen();
    /*Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "--------------------", AUTO_STRING_LENGTH, 48, 80, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);*/
    _BIS_SR(GIE);
    TimerA2Setup();
    while (1) {
        if (arrayPoint == 1536) {
            stopTimer();
            Graphics_clearDisplay(&g_sContext);
            buffer[0] ='N';
            buffer[1] = 'o';
            buffer[2] = 't';
            buffer[3] = 'e';
            buffer[4] = 's';
            buffer[5] = ':';
            buffer[6] = ' ';
            buffer[7] = (correcNotes / 100) + 0x30;
            if (correcNotes > 100){
                buffer[8] = ((correcNotes /10) % 10) + 0x30;
            }
            else{
                buffer[8] = (correcNotes / 10) + 0x30;
            }
            buffer[9] = correcNotes % 10 + 0x30;
            buffer[10] = '/';
            buffer[11] = '3';
            buffer[12] = '8';
            buffer[13] = '4';
            buffer[14] = '\0';
            if (correcNotes > 230) {
                Graphics_drawStringCentered(&g_sContext,"YOU ROCK", AUTO_STRING_LENGTH, 48, 28, OPAQUE_TEXT);
            } else {
                Graphics_drawStringCentered(&g_sContext,"YOU SUCK", AUTO_STRING_LENGTH, 48, 28, OPAQUE_TEXT);
            }
            Graphics_drawStringCentered(&g_sContext, buffer, AUTO_STRING_LENGTH, 48, 48, OPAQUE_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press '#'", AUTO_STRING_LENGTH, 48, 68, OPAQUE_TEXT);
            Graphics_drawStringCentered(&g_sContext, "to Restart", AUTO_STRING_LENGTH, 48, 78, OPAQUE_TEXT);
            Graphics_flushBuffer(&g_sContext);
            while(getKey() != '#') {}
            resetGame();
        }
        if (getKey() == '#') {
            resetGame();
        }
    }
    return 0;
}
