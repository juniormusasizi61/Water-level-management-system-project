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