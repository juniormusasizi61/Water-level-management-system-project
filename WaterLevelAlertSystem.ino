
  //Check if the water level is below the threshold
if (waterLevel < threshold) {
    //Turn off the green and yellow LEDs, turn on the red LED and the buzzer.
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    
    //Check if the alert message has not been sent
    if (!messageSent) {
        //Send an SMS alert and set the messageSent flag to true.
        sendSMS(phoneNumber, alertMessage);
        messageSent = true;
    }
} else if (waterLevel == maxDistance / 2) {
    //If the water level is at half of the max distance, turn on the yellow LED, turn off others and the buzzer.
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(buzzerPin, LOW);
} else {
    //If the water level is above the threshold, turn on the green LED, turn off others and the buzzer.
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    //Reset the messageSent flag to allow future alerts.
    messageSent = false;
}
// Handle client requests
  server.handleClient();

  delay(1000); // Wait before taking next measurement
}

  
