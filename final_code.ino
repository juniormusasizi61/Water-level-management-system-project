#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ThingSpeak.h>
#include <WebServer.h>
#include <SoftwareSerial.h>

// WiFi credentials for ThingSpeak
const char* ssidThingSpeak = "Alvin";
const char* passwordThingSpeak = "AliDaT12";

// WiFi credentials for Access Point
const char* ssidAP = "ESP32";
const char* passwordAP = "12345678";

// IP Address details
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Define WiFiClient object
WiFiClient client;

WebServer server(80);

// Initialize the LCD with I2C address 0x27 and 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions for ESP32
const int trigPin = 18;         // GPIO 18 for ultrasonic sensor trigger
const int echoPin = 19;         // GPIO 19 for ultrasonic sensor echo
const int greenLedPin = 23;     // GPIO 23 for green LED
const int yellowLedPin = 15;    // GPIO 22 for yellow LED
const int redLedPin = 16;       // GPIO 16 for red LED
const int buzzerPin = 17;       // GPIO 17 for buzzer
const int sim800TxPin = 13;     // GPIO 13 for SIM800L TX
const int sim800RxPin = 12;     // GPIO 12 for SIM800L RX

// Maximum distance to measure (in cm)
int maxDistance = 22;
int threshold = 5;  // Default threshold

// Variables to store duration and distance
long duration;
int waterLevel ;
int distance;
bool messageSent = false;  // Flag to check if message was sent