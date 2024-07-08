const int trigPin = 18;
const int echoPin = 19;

const int greenLedPin = 16;
const int redLedPin = 4;

const int maxDistance = 50;

long duration;
int distance;

int calculateWaterLevel(int distance) {
  int waterLevel = maxDistance - distance;
  if (waterLevel < 0) {
    waterLevel = 0; 
  }
  return waterLevel;
}

void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);

  Serial.println("Setup complete");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  Serial.print("Duration: ");
  Serial.println(duration);
  
  distance = duration * 0.034 / 2;
  
  int waterLevel = calculateWaterLevel(distance);
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Water Level: ");
  Serial.print(waterLevel);
  Serial.println(" cm");
  
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  
  if (waterLevel >= 30) {
    digitalWrite(greenLedPin, HIGH);

  } else {
    digitalWrite(redLedPin, HIGH);
  }
  
  delay(1000);
}
