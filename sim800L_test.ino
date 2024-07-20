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

  // List of phone numbers
  const char* phoneNumbers[] = {
    "+256754738336",
    "+256741483019",
    "+256760760092",
    "+256754738339",
    "+256754738340"
  };

  const char* message = "Hey! water levels are getting low. Please do the needful to make sure people are in a safe state of having enough water....";

  // Highlighted part: Loop through the phone numbers and send SMS to each one
  for (int i = 0; i < 5; i++) {
    mySerial.print("AT+CMGS=\"");
    mySerial.print(phoneNumbers[i]);
    mySerial.println("\"");
    updateSerial();
    mySerial.print(message); //text content
    updateSerial();
    mySerial.write(26);
    updateSerial();
    delay(1000); 
  }
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
