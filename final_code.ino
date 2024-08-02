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

WiFiClient client;

WebServer server(80);

// Initialize the LCD with I2C address 0x27 and 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions for ESP32
const int trigPin = 18;         // GPIO 18 for ultrasonic sensor trigger
const int echoPin = 19;         // GPIO 19 for ultrasonic sensor echo
const int greenLedPin = 23;     // GPIO 23 for green LED
const int yellowLedPin = 15;    // GPIO 15 for yellow LED
const int redLedPin = 16;       // GPIO 16 for red LED
const int buzzerPin = 17;       // GPIO 17 for buzzer
const int sim800TxPin = 13;     // GPIO 13 for SIM800L TX
const int sim800RxPin = 12;     // GPIO 12 for SIM800L RX

int maxDistance = 22; //Default tank height
int threshold = 5;  // Default threshold

long duration;
int waterLevel ;
int distance;
bool messageSent = false;  // Flag to check if message was sent

SoftwareSerial mySerial(sim800TxPin, sim800RxPin); // SIM800L initialization, Use UART1 for SIM800L

String phoneNumber = "+256740171596"; // Default phone number

const char* alertMessage = "WARNING:  Water level is getting low!";

// ThingSpeak parameters
unsigned long myChannelNumber = 2604177; 
const char* myWriteAPIKey = "7NWM6AHFBYDGMB5B"; 

int calculateWaterLevel(int distance) {
  int waterLevel = maxDistance - distance;
  return (waterLevel < 0) ? 0 : waterLevel;
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  mySerial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();

  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Turn off LEDs and buzzer
  digitalWrite(greenLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);

  Serial.println("Setup complete");

  // Connect to ThingSpeak WiFi
  WiFi.begin(ssidThingSpeak, passwordThingSpeak);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to ThingSpeak WiFi...");
  }
  Serial.println("Connected to ThingSpeak WiFi");

  // Initialize ThingSpeak with WiFiClient
  ThingSpeak.begin(client);

  // Setup WiFi access point
  WiFi.softAP(ssidAP, passwordAP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  // Serve the main HTML page
  server.on("/", HTTP_GET, handleRoot);

  // Handle settings
  server.on("/set_max_distance", HTTP_GET, handleSetMaxDistance);
  server.on("/set_threshold", HTTP_GET, handleSetThreshold);
  server.on("/set_phone_number", HTTP_GET, handleSetPhoneNumber);
  server.on("/water_level", HTTP_GET, handleWaterLevel);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");

  // Setup SIM800L
  delay(1000);
  mySerial.println("AT"); // Check communication
  updateSerial();
  delay(500);
  mySerial.println("AT+CMGF=1"); // Set SMS to text mode
  updateSerial();
  delay(500);
  mySerial.println("AT+CNMI=1,2,0,0,0"); // Configure SMS to be sent to the serial port
  updateSerial();
  delay(500);
}

void updateSerial() {
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  while (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void sendSMS(const String &phoneNumber, const char* message) {
  Serial.print("Sending SMS to: ");
  Serial.println(phoneNumber);

  mySerial.println("AT+CMGF=1");  // Set SMS mode to text
  delay(1000);
  updateSerial();

  mySerial.print("AT+CMGS=\"");
  mySerial.print(phoneNumber);
  mySerial.println("\"");
  delay(1000); // Allow time for SIM800L to process
  updateSerial();

  mySerial.print(message);
  delay(1000); // Allow time for SIM800L to process
  updateSerial();

  mySerial.write(26); // ASCII code of CTRL+Z to send the message
  delay(5000); // Wait for the message to be sent and processed
  updateSerial();
}

void loop() {
  // Measure water level using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in cm
  waterLevel = calculateWaterLevel(distance); // Update the global variable

  // Print water level to serial and LCD
  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println(" cm");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Level:");
  lcd.setCursor(0, 1);
  lcd.print(String(waterLevel) + " cm");

  // Update ThingSpeak with water level
  ThingSpeak.setField(1, waterLevel);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  // Check water level and take appropriate actions
  if (waterLevel < threshold) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    if (!messageSent) {
      sendSMS(phoneNumber, alertMessage);
      messageSent = true;
    }
  }else if (waterLevel == maxDistance / 2) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(buzzerPin, LOW);
  
   }else {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    messageSent = false;
  }

  // Handle client requests
  server.handleClient();

  delay(1000); // Wait before taking next measurement
}

void handleRoot() {
  String html = "<!DOCTYPE html><html>\n";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  html += "<title>Water Level Control</title>\n";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  html += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  html += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  html += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  html += "</style>\n";
  html += "</head>\n<body>\n";
  html += "<h1>Water Level Control</h1>\n";
  html += "<h3>Set Tank height</h3>\n";
  html += "<form action=\"/set_max_distance\" method=\"GET\">\n";
  html += "<input type=\"number\" name=\"max_distance\" min=\"0\" max=\"50\" value=\"" + String(maxDistance) + "\">\n";
  html += "<input class=\"button\" type=\"submit\" value=\"Set\">\n";
  html += "</form>\n";
  html += "<h3>Set Threshold</h3>\n";
  html += "<form action=\"/set_threshold\" method=\"GET\">\n";
  html += "<input type=\"number\" name=\"threshold\" min=\"0\" max=\"50\" value=\"" + String(threshold) + "\">\n";
  html += "<input class=\"button\" type=\"submit\" value=\"Set\">\n";
  html += "</form>\n";
  html += "<h3>Set Phone number</h3>\n";
  html += "<form action=\"/set_phone_number\" method=\"GET\">\n";
  html += "<input type=\"text\" name=\"phone_number\" value=\"" + phoneNumber + "\">\n";
  html += "<input class=\"button\" type=\"submit\" value=\"Set\">\n";
  html += "</form>\n";
  html += "<h3>Current Water Level</h3>\n";
  html += "<p id=\"waterLevel\">Fetching data...</p>\n";
  html += "<script>\n";
  html += "function fetchData() {\n";
  html += "fetch('/water_level').then(response => response.json()).then(data => {\n";
  html += "document.getElementById('waterLevel').innerText = 'Current Water Level: ' + data.level + ' cm';\n";
  html += "});\n";
  html += "}\n";
  html += "setInterval(fetchData, 2000);\n";
  html += "</script>\n";
  html += "</body>\n</html>\n";
  server.send(200, "text/html", html);
}

void handleSetMaxDistance() {
  if (server.hasArg("max_distance")) {
    maxDistance = server.arg("max_distance").toInt();
    Serial.println("Maximum distance set to: " + String(maxDistance));
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void handleSetThreshold() {
  if (server.hasArg("threshold")) {
    threshold = server.arg("threshold").toInt();
    Serial.println("Threshold set to: " + String(threshold));
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void handleSetPhoneNumber() {
  if (server.hasArg("phone_number")) {
    phoneNumber = server.arg("phone_number");
    Serial.println("Phone number set to: " + phoneNumber);
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void handleWaterLevel() {
  String json = "{\"level\": " + String(waterLevel) + "}";
  server.send(200, "application/json", json);
}
