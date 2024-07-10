//include the newping library #
#include "NewPing.h"
// Define pins for HC-SR04 sensor
const int trigPin = 2;  // Trigger pin
const int echoPin = 3;  // Echo pin

// Define pins for LEDs indicating water levels
const int greenLed = 4;  // Green LED for high water level
const int redLed = 5;
const int  buzzerpin = 6;   // Red LED for low water level

// Speed of sound in air in cm/ms at temperature around 20°C
#define   Tank_height   47 // cm/ms

//setup pins and maximum distance 
NewPing sonar(trigPin, echoPin, Tank_height);

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzerpin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the distance in centimeters
  int height = sonar.ping_cm();
  
  // Calculate the difference from Tank_height
  int difference = Tank_height - height;
  
  // Output for debugging
  Serial.print("Raw Distance: ");
  Serial.print(height);
  Serial.println(" cm");
  
  // Output to Serial Monitor
  Serial.print("Calculated Water level: ");
  Serial.print(difference);
  Serial.println(" cm");

  // Determine LED status based on water level
  if (difference >= 30) {
    digitalWrite(greenLed, HIGH);  
    digitalWrite(redLed, LOW);     
  } else {
    digitalWrite(greenLed, LOW);   
    digitalWrite(redLed, HIGH); 
    digitalwrite(buzzerpin, HIGH);
  }

  delay(2000);  
}