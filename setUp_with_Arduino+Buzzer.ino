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
   // Initialize SIM800L communication
  sim800.begin(9600);

  // Initialize ESP-01 communication
  esp.begin(115200);

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

   // Setup SIM800L
  sim800.println("AT");
  delay(50);
  sim800.println("AT+CMGF=1"); // Set SMS to text mode
  delay(50);
  sim800.println("AT+CNMI=1,2,0,0,0"); // Configure SMS to be sent to the serial port
  delay(50);

  // Setup ESP-01
  connectToWiFi();

  // Allow time for the HC-SR04 to warm up
  delay(2000);  // Allow a short delay for initialization
}

void connectToWiFi() {
  esp.println("AT+RST");
  delay(1000);
  esp.println("AT+CWMODE=1");
  delay(1000);
  esp.print("AT+CWJAP=\"");
  esp.print(ssid);
  esp.print("\",\"");
  esp.print(password);
  esp.println("\"");
  delay(5000);

  // Check connection
  esp.println("AT+CIFSR");
  delay(2000);
  while (esp.available()) {
    String response = esp.readString();
    Serial.println(response);
  }
}
void sendToThingSpeak(int waterLevel) {
  esp.print("AT+CIPSTART=\"TCP\",\"");
  esp.print(server);
  esp.println("\",80");
  delay(2000);

  String httpRequest = "GET /update?api_key=";
  httpRequest += apiKey;
  httpRequest += "&field1=";
  httpRequest += String(waterLevel);
  httpRequest += " HTTP/1.1\r\n";
  httpRequest += "Host: ";
  httpRequest += server;
  httpRequest += "\r\n";
  httpRequest += "Connection: close\r\n\r\n";
  
 esp.print("AT+CIPSEND=");
  esp.println(httpRequest.length());
  delay(1000);
  
  esp.print(httpRequest);
  delay(1000);
  
  esp.println("AT+CIPCLOSE");
  delay(1000);
}

void sendSMS(const char* message) {
  for (int i = 0; i < sizeof(phoneNumbers) / sizeof(phoneNumbers[0]); ++i) {
    sim800.print("AT+CMGS=\"");
    sim800.print(phoneNumbers[i]);
    sim800.println("\"");
    delay(1000); // Increased delay
    sim800.print(message);
    delay(1000);
    sim800.write(26); // ASCII code of CTRL+Z
    delay(5000); // Wait for the message to be sent and processed
    while (sim800.available()) {
      char c = sim800.read();
      Serial.write(c); // Print response for debugging
    }
  }
}

void loop() {
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;




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
  
 // Display the water level on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Water Level: ");
    lcd.setCursor(0, 1);
    lcd.print(waterLevel);
    lcd.print(" cm");


  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);
  
  if (waterLevel >= 30) {
    digitalWrite(greenLedPin, HIGH);
    messageSent = false; // Reset message flag if water level is safe
  } 
  else {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    if (!messageSent) {
        sendSMS("Yo! Warning: Water level is below 30 cm!"); // Edit this message
        messageSent = true; // Set flag to true to avoid resending
      }
  }
  azw
    // Send data to ThingSpeak
    sendToThingSpeak(waterLevewql);
  }
}
  
