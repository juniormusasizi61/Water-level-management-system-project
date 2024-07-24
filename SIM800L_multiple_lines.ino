#include "LiquidCrystal_I2C.h"
#include <SoftwareSerial.h>

// Initialize the LCD with I2C address 0x27 and 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int trigPin = 2;
const int echoPin = 3;
const int greenLedPin = 4;
const int redLedPin = 5;
const int buzzerPin = 6;
const int sim800TxPin = 7;
const int sim800RxPin = 8;

// Maximum distance to measure (in cm)
const int maxDistance = 50;

// Variables to store duration and distance
long duration;
int distance;
bool messageSent = false;  // Flag to check if message was sent

// SIM800L initialization
SoftwareSerial sim800(sim800TxPin, sim800RxPin);

// List of phone numbers
const char* phoneNumbers[] = {
  "+256740171596",
  "+256754269490",
};

int calculateWaterLevel(int distance) {
  int waterLevel = maxDistance - distance;
  return (waterLevel < 0) ? 0 : waterLevel;
}

