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
 */
#include <SoftwareSerial.h>
#define break_ON 1
#define break_OFF 0
#define left_ON 1
#define left_OFF 0
#define right_ON 1
#define right_OFF 0
#define time 250


// right_LED  5 - Blue
// left_LED  6  - Green
// break_LED  7 - Red

unsigned long mseconds;

char command = 0;
boolean state_break, state_left, state_right;


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
  state_break = break_OFF;
  state_left = left_OFF;
  state_right = right_OFF;
}

void loop() // run over and over
{
  // For test purposes we are using a RGB LED
  // it works with 0 to turn on and 1 to turn off
//  while(!SmartTshirt.available()){
//    //bliking leds here;
//    if (state_left == left_ON){
//      delay(time);
//      PORTD = PORTD ^ B01000000; // Inverts left_LED
//      delay(time);
//    }
//     if (state_right == right_ON){
//      delay(time);
//      PORTD = PORTD ^ B00100000; // Inverts left_LED
//      delay(time);
//    }
//  }
  if (SmartTshirt.available()){
    command = SmartTshirt.read();
    if (command =='b'){
      PORTD = PORTD ^ B10000000;  // Inverts break_LED
      if (state_break == break_OFF){
        SmartTshirt.println("Break ON");
        Serial.println("Break ON");
        state_break = break_ON;
      }
      else{
        SmartTshirt.println("Break OFF");
        Serial.println("Break OFF");
        state_break = break_OFF;
      }

    }
    if (command =='l'){
      PORTD = PORTD ^ B01000000; // Inverts left_LED
      delay(time);
      PORTD = PORTD ^ B01000000;
      delay(time);
      PORTD = PORTD ^ B01000000;
      delay(time);
      PORTD = PORTD ^ B01000000;
      delay(time);
      PORTD = PORTD ^ B01000000;
      delay(time);
      PORTD = PORTD ^ B01000000;
      delay(time);
      PORTD = PORTD ^ B01000000;
      delay(time);
      PORTD = PORTD ^ B01000000;
      delay(time);
      PORTD = PORTD ^ B01000000;
      delay(time);
      PORTD = PORTD ^ B01000000;
//      if (state_left == left_OFF){
//        SmartTshirt.println("Left ON");
//        Serial.println("Left ON");
//        state_left = left_ON;
//      }
//      else{
//        SmartTshirt.println("Left OFF");
//        Serial.println("Left OFF");
//        state_left = left_OFF;
//      }
    }
    if (command =='r'){
      PORTD = PORTD ^ B00100000; // Inverts rigth_LED
      delay(time);
      PORTD = PORTD ^ B00100000;
      delay(time);
      PORTD = PORTD ^ B00100000;
      delay(time);
      PORTD = PORTD ^ B00100000;
      delay(time);
      PORTD = PORTD ^ B00100000;
      delay(time);
      PORTD = PORTD ^ B00100000;
      delay(time);
      PORTD = PORTD ^ B00100000;
      delay(time);
      PORTD = PORTD ^ B00100000;
      delay(time);
      PORTD = PORTD ^ B00100000;
      delay(time);
      PORTD = PORTD ^ B00100000;
//      if (state_right == right_OFF){
//        SmartTshirt.println("Right ON");
//        Serial.println("Right ON");
//        state_right = right_ON;
//      }
//      else{
//        SmartTshirt.println("Right OFF");
//        Serial.println("Right OFF");
//        state_right = right_OFF;
//      }
    }
  }
// Debug purposes
//  if (Serial.available()){
//    SmartTshirt.write(Serial.read()); // Send to BT modem what is read in Serial port
//}
}

