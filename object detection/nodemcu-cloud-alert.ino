// NodeMCU (ESP8266) - Ultrasonic Object Detection with IFTTT Alert

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

const char* iftttHost  = "maker.ifttt.com";
const char* iftttEvent = "object_alert";
const char* iftttKey   = "YOUR_IFTTT_KEY";

const int trigPin   = D5;
const int echoPin   = D6;
const int buzzerPin = D7;

const int ALERT_DISTANCE_CM      = 20;
const unsigned long ALERT_COOLDOWN = 60000UL;

unsigned long lastAlertTime = 0;

long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000UL);
  if (duration == 0) return 999;
  return duration / 58;
}

void sendIFTTTAlert(long distance) {
  if (WiFi.status() != WL_CONNECTED) return;

  WiFiClient client;
  HTTPClient http;

  String url = String("http://") + iftttHost +
               "/trigger/" + iftttEvent +
               "/json/with/key/" + iftttKey +
               "?value1=" + String(distance);

  http.begin(client, url);
  http.GET();
  http.end();
}

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
}

void loop() {
  long distance = getDistanceCM();
  Serial.println(distance);

  if (distance < ALERT_DISTANCE_CM) {
    digitalWrite(buzzerPin, HIGH);

    unsigned long now = millis();
    if (now - lastAlertTime > ALERT_COOLDOWN) {
      sendIFTTTAlert(distance);
      lastAlertTime = now;
    }
  } else if (distance < 40) {
    digitalWrite(buzzerPin, HIGH);
    delay(150);
    digitalWrite(buzzerPin, LOW);
    delay(150);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(100);
}
