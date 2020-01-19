#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <WiFiClient.h>

#define LIGHT_LED 0
#define STATUS_LED 4
#define RED 13
#define POURING_SERVO_GPIO 5
#define RELAIS 15
#define RELAIS_2 16

#define DT 3000

#define POURING_IDLE_POS 10
#define POURING_ACTIVE_POS 170

ESP8266WiFiMulti WiFiMulti;

String prefix = "http://104.198.192.55/api/";

Servo pouringServo;

#define HUMIDITY 0b00
#define LIGHT 0b11
#define TEMPERATURE 0b01
unsigned long lasttime;
int humidity, light, temp;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  Serial.begin(115200);

  pinMode(STATUS_LED, OUTPUT);
  pinMode(LIGHT_LED, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(POURING_SERVO_GPIO, OUTPUT);
  pinMode(RELAIS, OUTPUT);
  pinMode(RELAIS_2, OUTPUT);
  pinMode(SCL, INPUT_PULLUP);
  pinMode(SDA, INPUT_PULLUP);
  digitalWrite(STATUS_LED, 0);
  digitalWrite(LIGHT_LED, 0);
  digitalWrite(RED, 0);
  digitalWrite(RELAIS, 0);
  digitalWrite(RELAIS_2, 0);
  lasttime = 0;

  lcd.init();
  lcd.print("Basilikum.");
  lcd.backlight();

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
        String endpoint = prefix + "new_measurement.php?humidity=" + String(humidity) + "&light=" + String(light) + "&temp=" + String(temp);
        Serial.print(endpoint); Serial.print("\n\r");
        http.begin(client, endpoint); http.GET();
      }
    }
  }
}

void read_sensors() {
  if (digitalRead(RELAIS) == HUMIDITY) {
    humidity = analogRead(A0);
    set_analog_input(LIGHT);
    delay(400);
    light = analogRead(A0);
    set_analog_input(TEMPERATURE);
    delay(400);
    temp = analogRead(A0);
    
  } else {
    temp = analogRead(A0);
    set_analog_input(LIGHT);
    delay(400);
    light = analogRead(A0);
    set_analog_input(HUMIDITY);
    delay(400);
    humidity = analogRead(A0);
  }
}

int set_analog_input(int chan) {
  digitalWrite(RELAIS, chan & 0b01);
  digitalWrite(RELAIS_2, chan & 0b10);
}
