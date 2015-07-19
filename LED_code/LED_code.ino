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

int LED = 9;
char state = 0;

SoftwareSerial SmartTshirt(14, 15); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(LED, OUTPUT);


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  SmartTshirt.begin(9600);
  SmartTshirt.println("Hello, world?");
}

void loop() // run over and over
{
  if (SmartTshirt.available())
    state = SmartTshirt.read();
    if (state=='1'){
      digitalWrite(LED, 1);
      SmartTshirt.println("LED on");
      Serial.println("LED on");
    }
    if (state=='2'){
      digitalWrite(LED, 0);
      SmartTshirt.println("LED off");
      Serial.println("LED off");
    }
  if (Serial.available())
    SmartTshirt.write(Serial.read());
}

