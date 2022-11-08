#include <msp430.h> 



void delay(int time){ //Is used as a delay (time is amount of time you want the delay to loop through)
    volatile long i = time;

    while(i != 0){
        i = i - 1;
    }
}

void allOn(){ //Turns all leds on pin6 bit 0-4 on
    P6OUT |= BIT0;
    P6OUT |= BIT1;
    P6OUT |= BIT2;
    P6OUT |= BIT3;
    P6OUT |= BIT4;
}
void allOff(){ //Turns all leds on pin6 bit 0-4 off
    P6OUT &= ~BIT0;
    P6OUT &= ~BIT1;
    P6OUT &= ~BIT2;
    P6OUT &= ~BIT3;
    P6OUT &= ~BIT4;
}

void redOn(){ //Turns pins 6.1 and 6.3 on
    P6OUT |= BIT1;
    P6OUT |= BIT3;
}
void blueOn(){ //Turns pins 6.0, 6.2 and 6.4 on
    P6OUT |= BIT0;
    P6OUT |= BIT2;
    P6OUT |= BIT4;
}

void trickle(int delaySpeed){ //Turns on and off pins in a "trickle" pattern
    delay(delaySpeed);
    P6OUT |= BIT0;
    delay(delaySpeed);
    P6OUT |= BIT1;
    delay(delaySpeed);
    P6OUT &= ~BIT0;
    delay(delaySpeed);
    P6OUT |= BIT2;
    delay(delaySpeed);
    P6OUT &= ~BIT1;
    delay(delaySpeed);
    P6OUT |= BIT3;
    delay(delaySpeed);
    P6OUT &= ~BIT2;
    delay(delaySpeed);
    P6OUT |= BIT4;
    delay(delaySpeed);
    P6OUT &= ~BIT3;
    delay(delaySpeed);
    P6OUT |= BIT5;
    delay(delaySpeed);
    P6OUT &= ~BIT4;
    delay(delaySpeed);
    P6OUT &= ~BIT5;


}
/**
 * main.c
 */
void main(void){

   WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
   PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode

   //For LEDS
   P6DIR |= BIT0;
   P6DIR |= BIT1;
   P6DIR |= BIT2;
   P6DIR |= BIT3;
   P6DIR |= BIT4;



   P1DIR |= ~BIT2;                  //Pin 1 BIT2
   P1OUT &= ~BIT2;                  //Pin 1 BIT2

   P1DIR |= ~BIT3;
   P1OUT &= ~BIT3;

   P3DIR |= ~BIT4;
   P3OUT &= ~BIT4;

   P4DIR |= ~BIT5;
   P4OUT &= ~BIT5;


   //Pin 1,3,4
   P1DIR &= ~BIT4;
   P1REN &= ~BIT4;

   P3DIR &= ~BIT4;
   P3REN &= ~BIT4;

   P4DIR &= ~BIT4;
   P4REN &= ~BIT4;

   P1DIR |= BIT0;                   //For LED on board

   //P4DIR &= ~BIT1;                 // Clear Bit P4.1. 0 = Input, 1 = Output
   //P4REN |= BIT1;                  // Set 1 to Bit 1
   //P4OUT |= BIT1;                  // Set 1 to Bit 1



   int SW1, SW2, SW3, SW4;                        // Store the information in the register

   for (;;){

       SW1 = P1IN;                 // Store a copy
       SW2 = P1IN;
       SW3 = P3IN;
       SW4 = P4IN;

       SW1 &= BIT2;                // Clear everything and keep Bit 1
       SW2 &= BIT3;
       SW3 &= BIT4;
       SW4 &= BIT5;

       if(SW1 != 0){
           for(;;){ //Pattern 1
             allOff();
             allOn();
             delay(5000);
             allOff();
             delay(6000);
          }
       }
       if(SW2 != 0){
           for(;;){
               allOff();
               delay(20000);
               redOn();
               delay(10000);
               blueOn();
               delay(20000);
               allOff();
           }
       }

       if(SW3 != 0){
           for(;;){
               allOff();
               delay(5000);
               blueOn();
               delay(7000);
           }
       }

       if(SW4 != 0){
           for(;;){
               trickle(10000); //Pattern 4
               trickle(3000);  //Pattern 5
           }
       }

       //if (SW2 != 0 || SW3 != 0 || SW4 != 0){               // If it is 0, the user pressed the button
           //P1OUT |= BIT0;
       //}else{
           //P1OUT &= ~BIT0;
       //}
   }

}

