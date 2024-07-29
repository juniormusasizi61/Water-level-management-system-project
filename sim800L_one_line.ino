#include <SoftwareSerial.h>

// Initialize SoftwareSerial for communication with SIM800L module
// SIM800L Tx is connected to Arduino pin 3, and Rx is connected to pin 2
SoftwareSerial mySerial(3, 2);

void setup()
{
  // Begin serial communication with the Arduino IDE Serial Monitor
  

  Serial.begin(9600);
  
  // Begin serial communication with the SIM800L module
  
  mySerial.begin(9600);

  // Print an initializing message to the Serial Monitor
  Serial.println("Initializing..."); 
  delay(1000); // Wait for 1 second to ensure the GSM module is ready

  // Send AT command to the SIM800L module to check if it is responsive
  mySerial.println("AT"); 
  updateSerial(); // Call the function to handle serial communication

  // Set SMS mode to text mode for the SIM800L module
  mySerial.println("AT+CMGF=1"); 
  updateSerial(); // Call the function to handle serial communication

  // Specify the recipient's phone number for the SMS
  mySerial.println("AT+CMGS=\"+256754738336\""); // Change to the recipient's phone number
  updateSerial(); 

  // Send the SMS content to the SIM800L module
  mySerial.print("Hey! water levels are getting low; Please do the needfull to make sure people are in a safe state of having enough water!...."); // Text content
  updateSerial(); // Call the function to handle serial communication

  // End the SMS message with the CTRL+Z character (ASCII 26) to send it
  mySerial.write(26);
}

void loop()
{
  
}

void updateSerial()
{
  delay(500); // Wait for half a second to allow serial data to be received
 
  while (Serial.available()) 
  {
    mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
  }
  // Forward data received from the SIM800L module to the Arduino Serial Monitor
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read()); // Forward what Software Serial received to Serial Port
  }
}


