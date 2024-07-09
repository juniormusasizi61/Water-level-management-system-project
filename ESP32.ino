#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 18;
const int echoPin = 19;

const int greenLedPin = 16;
const int redLedPin = 4;

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

  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);

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
  
  if (waterLevel >= 30) {
    digitalWrite(greenLedPin, HIGH);

  } else {
    digitalWrite(redLedPin, HIGH);
  }
  
  delay(1000);
}
