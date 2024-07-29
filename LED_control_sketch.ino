#include <SoftwareSerial.h>
#include "LiquidCrystal_I2C.h"

// Initialize the LCD with I2C address 0x27 and 16 columns x 2 rows.s

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize SoftwareSerial for SIM800L module communication

SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

// Define pin numbers for ultrasonic sensor.
const int trigPin = 7;
const int echoPin = 8;

// Define pin numbers for LEDs and buzzer
const int greenLedPin = 4;
const int redLedPin = 5;
const int buzzerPin = 6;

// Maximum distance for water level measurement
const int maxDistance = 50;

// Variables for duration of ultrasonic pulse and calculated distance
long duration;
int distance;

// Function to calculate water level based on distance
int calculateWaterLevel(int distance) {
  int waterLevel = maxDistance - distance;
  if (waterLevel < 0) {
    waterLevel = 0; 
  }
  return waterLevel;
}

void setup() {
  // Start serial communication
  Serial.begin(115200);
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Set pin modes for ultrasonic sensor, LEDs, and buzzer
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Turn off LEDs and buzzer initially
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);

  // Print setup completion message
  Serial.println("Setup complete");
}

void loop() {
  
  // Send a pulse from the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read  pulse duration from the ultrasonic sensor
  duration = pulseIn(echoPin, HIGH);

  // Print  duration for debugging
  Serial.print("Duration: ");
  Serial.println(duration);

  // Calculate distance from duration.
  distance = duration * 0.034 / 2;

  // Calculate water level from distance
  int waterLevel = calculateWaterLevel(distance);

  // Display water level on LCD
  
  lcd.setCursor(1, 0);
  lcd.print("Water Level: ");
  lcd.setCursor(1, 1);
  lcd.print(waterLevel);
  lcd.print(" cm");

  // Turn off LEDs and buzzer
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);

  // Check water level and update LEDs and buzzer accordingly.
  
  if (waterLevel >= 30) {
    digitalWrite(greenLedPin, HIGH);
  } else 
  {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    // Begin serial communication with Arduino and SIM800L
    mySerial.begin(9600);
    Serial.println("Initializing...");
    delay(1000);

    // Send AT commands to SIM800L
    mySerial.println("AT"); // Handshake test
    updateSerial();
    mySerial.println("AT+CMGF=1"); // Configure TEXT mode.
    updateSerial();
    mySerial.println("AT+CMGS=\"+256754738336\""); // Recipient phone number.
    updateSerial();
    mySerial.print("hey! water levels are getting low. do the needful to make sure people are in a safe state of having enough water...."); // Text content
    updateSerial();
    mySerial.write(26); // End of message character.
  }

  // Wait for 2 seconds before repeating the loop
  delay(2000);
}

// Function to update serial communication between Arduino and SIM800L
void updateSerial() {
 
  delay(6000);
  while (Serial.available()) {
    mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
  }
  
  
  while (mySerial.available()) {
    Serial.write(mySerial.read()); // Forward what Software Serial received to Serial Port
  
  }
}
