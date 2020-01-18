#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#define WIFI_OK_LED 0
#define STATUS_LED 4
#define RED 13
#define POURING_SERVO_GPIO 5

#define POURING_IDLE_POS 10
#define POURING_ACTIVE_POS 170

ESP8266WiFiMulti WiFiMulti;

String prefix = "http://104.198.192.55/api/";

Servo pouringServo;

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(true);

  pinMode(STATUS_LED, OUTPUT);
  pinMode(WIFI_OK_LED, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(POURING_SERVO_GPIO, OUTPUT);
  digitalWrite(STATUS_LED, 0);
  digitalWrite(WIFI_OK_LED, 0);
  digitalWrite(RED, 0);

  pouringServo.attach(POURING_SERVO_GPIO);	 
  pouringServo.write(POURING_IDLE_POS);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("ArchNet", "TUbedefined");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  digitalWrite(STATUS_LED, 1);

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

    }


//    Serial.print("[HTTP] begin...\n\r");
//    if (http.begin(client, "http://104.198.192.55/api/new_measurement.php?humidity=55&light=0")) {  // HTTP
//
//
//      Serial.print("[HTTP] GET...\n");
//      // start connection and send HTTP header
//      int httpCode = http.GET();
//
//      // httpCode will be negative on error
//      if (httpCode > 0) {
//        // HTTP header has been send and Server response header has been handled
//        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
//
//        // file found at server
//        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
//          String payload = http.getString();
//          Serial.println(payload);
//        }
//      } else {
//        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
//      }
//
//      http.end();
//    } else {
//      Serial.printf("[HTTP} Unable to connect\n");
//    }
  }

  //delay(1000);
}
