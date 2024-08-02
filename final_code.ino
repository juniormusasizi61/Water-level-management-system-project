#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ThingSpeak.h>
#include <WebServer.h>
#include <SoftwareSerial.h>

// WiFi credentials for ThingSpeak
const char* ssidThingSpeak = "Alvin";
const char* passwordThingSpeak = "AliDaT12";