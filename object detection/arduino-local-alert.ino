// Arduino Uno - Ultrasonic Object Detection with Buzzer Alert

const int trigPin   = 2;
const int echoPin   = 3;
const int buzzerPin = 8;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000UL);
  if (duration == 0) return 999;
  return duration / 58;
}

void loop() {
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 10) {
    tone(buzzerPin, 3000);
  }
  else if (distance < 30) {
    tone(buzzerPin, 1500);
    delay(150);
    noTone(buzzerPin);
    delay(150);
  }
  else {
    noTone(buzzerPin);
  }

  delay(50);
}
