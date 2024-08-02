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
     
  
