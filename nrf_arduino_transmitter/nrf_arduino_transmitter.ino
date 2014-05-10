#include <SoftwareSerial.h>
// For the electronic wiring , you should :
// Connect pinRx to the Pin2 of XBee(Tx , Dout)
// Connect pinTx to the Pin3 of XBee(Rx , Din)

// Define the pins on Arduino for XBee comminication
uint8_t pinRx = 2 , pinTx = 4; // the pin on Arduino
long BaudRate = 9600 , sysTick = 0;
char GotChar;
// Initialize NewSoftSerial
SoftwareSerial mySerial( pinRx , pinTx );

void setup()  
{ // You shall see these messages in Arduino Serial Monitor
// This part is the official library , it will be used for talking to
// PC serial port
  Serial.begin(BaudRate);
  Serial.println("XBee Communication Test Start !");
  Serial.print("BaudRate:");
  Serial.println(BaudRate);
  Serial.print("NewSoftSerial Rx Pin#");
  Serial.println(pinRx,DEC);
  Serial.print("NewSoftSerial Tx Pin#");
  Serial.println(pinTx,DEC);

  // This part is the NewSoftSerial for talking to XBee
  mySerial.begin(BaudRate);
  mySerial.println("Powered by NewSoftSerial !");
}

void loop()                    
{
      mySerial.print(1);
      delay(5000);
}
