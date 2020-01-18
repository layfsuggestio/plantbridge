#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#define LIGHT_LED 0
#define STATUS_LED 4
#define RED 13
#define POURING_SERVO_GPIO 5
#define RELAIS 2

#define DT 3000

#define POURING_IDLE_POS 10
#define POURING_ACTIVE_POS 170

ESP8266WiFiMulti WiFiMulti;

String prefix = "http://104.198.192.55/api/";

Servo pouringServo;

#define HUMIDITY 0
#define LIGHT 1
unsigned long lasttime;
int humidity, light;

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(true);

  pinMode(STATUS_LED, OUTPUT);
  pinMode(LIGHT_LED, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(POURING_SERVO_GPIO, OUTPUT);
  pinMode(RELAIS, OUTPUT);
  digitalWrite(STATUS_LED, 0);
  digitalWrite(LIGHT_LED, 0);
  digitalWrite(RED, 0);
  lasttime = 0;

  pouringServo.attach(POURING_SERVO_GPIO);	 
  pouringServo.write(POURING_IDLE_POS);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("ArchNet", "TUbedefined");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  digitalWrite(STATUS_LED, 1);
  digitalWrite(RELAIS, HUMIDITY);

}

void loop() {
  // Set WifiStatus to STATUS_LED LED
  digitalWrite(STATUS_LED, WiFi.status() == WL_CONNECTED);
  
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;
    String endpoint = prefix + "request_status.php";
    if (http.begin(client, endpoint)) {
      int returnCode = http.GET();

      if (returnCode == HTTP_CODE_OK) {
        String message = http.getString();
        if (message.toInt()) {
          digitalWrite(RED, 0);
          pouringServo.write(POURING_ACTIVE_POS);
          delay(2000);
          http.begin(client, prefix + "reset_status.php"); http.GET();
          pouringServo.write(POURING_IDLE_POS);
        } else {
          digitalWrite(RED, 1);
        }
      }

      digitalWrite(LIGHT_LED, light >= 400);

      if (millis() - lasttime > DT) {
        lasttime = millis();
        read_sensors();
        String endpoint = prefix + "new_measurement.php?humidity=" + String(humidity) + "&light=" + String(light);
        Serial.print(endpoint); Serial.print("\n\r");
        http.begin(client, endpoint); http.GET();
      }

    }

  }

  //delay(1000);
}

void read_sensors() {
  if (digitalRead(RELAIS) == HUMIDITY) {
    humidity = analogRead(A0);
    digitalWrite(RELAIS, LIGHT);
    delay(200);
    light = analogRead(A0);
  } else {
    light = analogRead(A0);
    digitalWrite(RELAIS, HUMIDITY);
    delay(200);
    humidity = analogRead(A0);
  }


}
