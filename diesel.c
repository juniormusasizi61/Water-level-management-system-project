//calculate the water distance
int calculateWaterLevel(int distance) {
  int waterLevel = maxDistance - distance;
  return (waterLevel < 0) ? 0 : waterLevel;
}

//initialize your vars
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