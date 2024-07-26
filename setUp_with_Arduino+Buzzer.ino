#include "LiquidCrystal_I2C.h"
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 2;
const int echoPin = 3;

const int greenLedPin = 4;
const int redLedPin = 5;
const int buzzerPin = 6;
const int sim800TxPin = 7;
const int sim800RxPin = 8;
const int espTxPin = 10;
const int espRxPin = 11;

const int maxDistance = 50;

long duration;
int distance;
bool messageSent = false;  // Flag to check if message was sent
unsigned long previousMillis = 0;
const unsigned long interval = 500; // 0.5 seconds interval

// SIM800L initialization
SoftwareSerial sim800(sim800TxPin, sim800RxPin);

// ESP-01 initialization
SoftwareSerial esp(espRxPin, espTxPin);

// ThingSpeak settings
const char* ssid = "MayaJ";          // Replace with your WiFi SSID
const char* password = "Astromaya11";  // Replace with your WiFi Password
const char* apiKey = "7NWM6AHFBYDGMB5B";  // Replace with your ThingSpeak API Key
const char* server = "api.thingspeak.com";

const char* phoneNumbers[] = {
  "+256740171596", // Replace with your first phone number
  "+256754269490"  // Replace with your second phone number
};

int calculateWaterLevel(int distance) {
  int waterLevel = maxDistance - distance;
  return (waterLevel < 0) ? 0 : waterLevel;
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
  }
  
  delay(2000);
}