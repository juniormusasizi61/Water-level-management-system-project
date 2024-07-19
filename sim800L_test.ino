#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); 


void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing....."); 
  delay(1000);

  mySerial.println("AT"); 
  updateSerial();

  mySerial.println("AT+CMGF=1"); 
  updateSerial();
 mySerial.println("AT+CMGS=\"+256754738336\"");
  updateSerial();
  mySerial.print("Hey! water levels are getting low. Please do the needfull to make sure people are in a safe state of having enough water...."); //text content
  updateSerial();
  mySerial.write(26);
}

void loop()
{
}


void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
  
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
}