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