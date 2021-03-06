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
 
In this case we are working with a RGB LED, so the opposite is sent to turn it off and on (1=off, 0=on)
 */
#include <SoftwareSerial.h>
#include "TimerOne.h"


// right_LED  5 - Blue
// left_LED  6  - Green
// break_LED  7 - Red


char command;
volatile char code;
volatile int counter=1;
volatile int counter_break=1;


SoftwareSerial SmartTshirt(10, 11); // RX, TX // A4, A5

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  DDRD = DDRD | B11100000; // Set pins 5,6 and 7 as output
  
  // Turn off all LEDs
  PORTD = B11100000;       // Set pins 5,6 and 7 to HIGH (RGB LED off)
  
  Serial.println("Started Serial Communication");
  // set the data rate for the SoftwareSerial port
  SmartTshirt.begin(9600);
  SmartTshirt.println("Started Bluetooth Communication");
  Timer1.initialize(250000);         // initialize timer1, and set a 1/4 second period
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}

void callback()
{
  if (code =='l'){
    PORTD = PORTD ^ B01000000; // Inverts left_LED
    counter++;
    }
   else if (code =='r'){
     PORTD = PORTD ^ B00100000; // Inverts rigth_LED
     counter++;
   }
   else if (code =='b'){
      PORTD = B01111111;  // Turn on break_LED
      counter_break++;
   }
   else{
     PORTD = B11100000;
   }

}

void loop() // run over and over
{
 if (SmartTshirt.available()){
    command = SmartTshirt.read();
 }
 if (command!=0 && command!=10){
   code=command;
 }
 if (counter>=11){
   counter=1;
   code='a';
 }
 if (counter_break>=11){
    PORTD = B11100000;
    counter_break=1;
    code='a';
 }
}

