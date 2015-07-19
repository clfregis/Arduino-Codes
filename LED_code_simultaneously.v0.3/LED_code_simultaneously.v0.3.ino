/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.
 
 For Summer project, Claudio made some modifications in order to 
 add a LED to test I/O using BT modem
 What this program do is call an ISR each 250 ms and make some functions based on what value is 
 read in SoftwareSerial. If it receives a character l it blinks 10 times an LED, same for char r.
 If it receive a char b, it turn an LED on for 10 times 250 ms, then turn it off.
 
In this case we are working with a different configuration, so the opposite is sent to turn it OFF and ON (1=off, 0=on)
 */
#include <SoftwareSerial.h>
#include "TimerOne.h"

#define break_ON 1
#define break_OFF 0
#define left_ON 1
#define left_OFF 0
#define right_ON 1
#define right_OFF 0
#define interrupt_time 250000

/* Used for connect the pins in the LEDs, since we are doing ports manipulatin instead of using digitalWrite
right_LED  5 - Blue
left_LED  6  - Green
break_LED  7 - Red
*/

char command;
volatile char code;
volatile unsigned int counter_left=1;
volatile unsigned int counter_right=1;
volatile unsigned int counter_break=1;
volatile boolean state_left=0;
volatile boolean state_right=0;
volatile boolean state_break=0;
volatile boolean state=0;

SoftwareSerial SmartTshirt(10, 11); // RX, TX // A4, A5

void setup()
{
  Serial.begin(9600);                                // Open serial communications and wait for port to open:
  DDRD = DDRD | B11100000;                           // Set pins 5,6 and 7 as output
  PORTD = B11100000;                                 // Set pins 5,6 and 7 to HIGH (RGB LED off)
  Serial.println("Started Serial Communication");
  SmartTshirt.begin(9600);                           // Set the data rate for the SoftwareSerial port
  SmartTshirt.println("Started Bluetooth Communication");
  Timer1.initialize(interrupt_time);                 // initialize Timer1, and set a 1/4 second period
  Timer1.attachInterrupt(callback);                  // Attaches callback() as a timer overflow interrupt
}

void callback(){

  if (state_left){
    PORTD = PORTD ^ B01000000;      // Inverts left_LED
    counter_left++;                 // Increases the counter
    }
  if (state_right){
     PORTD = PORTD ^ B00100000;     // Inverts rigth_LED
     counter_right++;               // Increases the counter
   }
  if (state_break){
    if (counter_break==1){          // Only inverts the break LED at the start of 
      PORTD = PORTD ^ B10000000;    // Turn on break_LED
    }
    counter_break++;                // Increases the counter
   }
   if (state){                      // Reset system          
     PORTD = B11100000;             // Disable all LEDs
     counter_left=1;                // Reset counter
     counter_right=1;               // Reset counter
     counter_break=1;               // Reset counter
     state=0;
   }

}

void loop(){ // run over and over
 if (SmartTshirt.available()){     // If there is something to read in serial
    command = SmartTshirt.read();  // Store its reading in command var
 }
 if (command!=0 && command!=10){   // Blutetooth keeps sending null (0 - DEC) until the first connection is reached
                                   // Then, bluetooth keeps send Line Feed (LF, 10 - DEC)
                                   // Analyze the value only when it is not NULL or LF
                                   
    if (command == 'l'){           // If receive the command to activate left arrow
     state_left = left_ON;         // Turn ON the state that indicates left arrow ON
     if (state_right){             // If the system is with right arrow ON
       state_right=right_OFF;      // Turn OFF the state that indicates that right arrow is ON
       state=1;                    // Reset the System
     }
    }
    if (command == 'r'){           // If receive the state that indicates right arrow ON
      state_right = right_ON;      // Turn ON the state that indicates right arrow ON
      if (state_left){             // If the system is with left arrow ON
        state_left=left_OFF;       // Turn OFF the state that indicates that left arrow is ON
        state=1;                   // Reset the System
      }
    }
    if (command == 'b') state_break = break_ON;  // If receive the command to turn ON the breaks, Turn ON its state
    if (command == 'd') state = 1;               // If receive the command to reset the system, Turn ON the state that do it
 }

// Turn OFF the arrows and break LEDs when the time overflow
 if (counter_left>=11){        // When left arrows blinked for 10 times
   counter_left=1;             // Reset counter
   state_left = left_OFF;      // Reset state
 }
  if (counter_right>=11){      // When right arrows blinked for 10 times
   counter_right=1;            // Reset counter
   state_right = right_OFF;    // Reset state
 }
 if (counter_break>=11){       // Break keep ON for 10x250ms 
    PORTD = PORTD ^ B10000000; // Turn OFF break_LED (inverts from the last state)
    counter_break=1;           // Reset counter
    state_break = break_OFF;   // Reset state
 }
}

