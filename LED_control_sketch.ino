#include <SoftwareSerial.h>
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2


const int trigPin = 7;
const int echoPin = 8;

const int greenLedPin = 4;
const int redLedPin = 5;
const int buzzerPin = 6;

const int maxDistance = 50;

long duration;
int distance;

int calculateWaterLevel(int distance) {
  int waterLevel = maxDistance - distance;
  if (waterLevel < 0) {
    waterLevel = 0; 
  }
  return waterLevel;
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);

  Serial.println("Setup complete");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  Serial.print("Duration: ");
  Serial.println(duration);
  
  distance = duration * 0.034 / 2;
  
  int waterLevel = calculateWaterLevel(distance);
  
  lcd.setCursor(1,0 );
  lcd.print("Water Level: ");
 
  lcd.setCursor(1,1);
  lcd.print(waterLevel);
  lcd.print(" cm");

  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  if (waterLevel >= 30) {
    digitalWrite(greenLedPin, HIGH);

  } else {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
   
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
 mySerial.println("AT+CMGS=\"+256754738336\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("hey! water levels are getting low. do the needfull to make sure people are in a safe state of having enough water...."); //text content
  updateSerial();
  mySerial.write(26);

}

  
  delay(2000);
}
void updateSerial(){
  delay(6000);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}