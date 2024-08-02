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