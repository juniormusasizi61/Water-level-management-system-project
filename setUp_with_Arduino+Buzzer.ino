#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 2;
const int echoPin = 3;

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
  }
  
  delay(2000);
}