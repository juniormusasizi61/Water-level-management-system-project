
  //Check if the water level is below the threshold
if (waterLevel < threshold) {
    //Turn off the green and yellow LEDs, turn on the red LED and the buzzer
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    
  //Check if the alert message has not been sent
    if (!messageSent) {
        // Send an SMS alert and set the messageSent flag to true
        sendSMS(phoneNumber, alertMessage);
        messageSent = true;
    }
} else if (waterLevel == maxDistance / 2) {
    //If the water level is at half of the max distance, turn on the yellow LED, turn off others and the buzzer
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(buzzerPin, LOW);
} else {
    // If the water level is above the threshold, turn on the green LED, turn off others and the buzzer
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    // Reset the messageSent flag to allow future alerts
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


  
