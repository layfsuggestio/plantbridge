#include <Arduino.h>

/**
 * On sparkfun ESP8266
 * 
 * Pinout:
 * 
 * 02: SDA (I2C to Display)
 * 14: SCL (I2C to Display)
 * 
 * 
 * 
 * **/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <WiFiClient.h>

#define LIGHT_LED 0
#define STATUS_LED 4
#define POURING_SERVO_GPIO 5
#define RELAIS 15
#define RELAIS_2 16

#define DT 3000

#define POURING_IDLE_POS 10
#define POURING_ACTIVE_POS 90

ESP8266WiFiMulti WiFiMulti;

String prefix = "http://104.198.192.55/api/";

Servo pouringServo;

#define HUMIDITY 0b00
#define LIGHT 0b11
#define TEMPERATURE 0b01
unsigned long lasttime;
int humidity, light, temp;

int e = 0;

WiFiClient client;
HTTPClient http;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  Serial.begin(115200);
  setup_io();
  lasttime = 0;

  setup_lcd();

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


    String endpoint = prefix + "request_status.php";
    if (http.begin(client, endpoint)) {
      int returnCode = http.GET();

      if (returnCode == HTTP_CODE_OK) {
        String message = http.getString();
        if (message[0] == '1') {
           handle_reward();
        }
        if (message[1] == '1') lcd.backlight();
        else lcd.noBacklight();

        char resultOfTurn = message[2];
        if (resultOfTurn == '0') {
          e = 1;
        } else {
          e = 0;
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

void handle_reward() {
  pouringServo.write(POURING_ACTIVE_POS);
  delay(2000);
  http.begin(client, prefix + "reset_status.php"); http.GET();
  pouringServo.write(POURING_IDLE_POS);
  e = 1;
}

void read_sensors() {
  if (digitalRead(RELAIS) == HUMIDITY) {
    humidity = analogRead(A0);
    set_analog_input(TEMPERATURE);
    delay(200);
    temp = analogRead(A0);
    delay(200);
    set_analog_input(LIGHT);
    delay(200);
    light = analogRead(A0);
    look_left(e);
  } else {
    light = analogRead(A0);
    set_analog_input(TEMPERATURE);
    delay(200);
    temp = analogRead(A0);
    delay(200);
    set_analog_input(HUMIDITY);
    delay(200);
    humidity = analogRead(A0);
    look_right(e);
  }
}

int set_analog_input(int chan) {
  digitalWrite(RELAIS, chan & 0b01);
  digitalWrite(RELAIS_2, chan & 0b10);
}

void setup_io() {
  pinMode(STATUS_LED, OUTPUT);
  pinMode(LIGHT_LED, OUTPUT);
  pinMode(POURING_SERVO_GPIO, OUTPUT);
  pinMode(RELAIS, OUTPUT);
  pinMode(RELAIS_2, OUTPUT);
  pinMode(SCL, INPUT_PULLUP);
  pinMode(SDA, INPUT_PULLUP);
  digitalWrite(STATUS_LED, 0);
  digitalWrite(LIGHT_LED, 0);
  digitalWrite(RELAIS, 0);
  digitalWrite(RELAIS_2, 0);
  digitalWrite(RELAIS, 0);
}


byte customChar0[] = {
  B11111,
  B00011,
  B00000,
  B00111,
  B01000,
  B10000,
  B10000,
  B10000
};

byte customChar1[] = {
  B00000,
  B00000,
  B00000,
  B11100,
  B00010,
  B00001,
  B00001,
  B00001
};

byte customChar2[] = {
  B10000,
  B10000,
  B10000,
  B01000,
  B00111,
  B00000,
  B00000,
  B00000
};

byte customChar3[] = {
  B11001,
  B11001,
  B00001,
  B00010,
  B11100,
  B00000,
  B00000,
  B00000
};

byte customChar4[] = {
  B10011,
  B10011,
  B10000,
  B01000,
  B00111,
  B00000,
  B00000,
  B00000
};

byte customChar5[] = {
  B00001,
  B00001,
  B00001,
  B00010,
  B11100,
  B00000,
  B00000,
  B00000
};

byte customChar6[] = {
  B00011,
  B01110,
  B11000,
  B00111,
  B01000,
  B10000,
  B10000,
  B10000
};

byte customChar7[] = {
  B10000,
  B11110,
  B00011,
  B11100,
  B00010,
  B00001,
  B00001,
  B00001
};

void setup_lcd() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar0);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.createChar(6, customChar6);
  lcd.createChar(7, customChar7);
  lcd.home();
  look_right(e);
}

void look_right(int evil) {
  draw_eye(4, 0, evil);
  draw_eye(10, 0, evil);
}

void look_left(int evil) {
  draw_eye(4, 1, evil);
  draw_eye(10, 1, evil);
}

void draw_eye(int start_idx, int lr, int evil) {
  lcd.setCursor(start_idx, 0);
  if (evil) {
    lcd.write(6);
    lcd.write(7);
  } else {
    lcd.write(0);
    lcd.write(7);
  }
  lcd.setCursor(start_idx, 1);
  if (lr) {
    lcd.write(2);
    lcd.write(3);
  } else {
    lcd.write(4);
    lcd.write(5);
  }
}
