#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "GyverButton.h"
#include "ESP8266WiFi.h"
Adafruit_SSD1306 display(128,64,&Wire,5);

void setup() {
  Wire.begin(D3, D2);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(1);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Setup done");
  display.display();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);
}

void loop() {
  //Serial.println("scan start");
  int n = WiFi.scanNetworks();
  //Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(n); // Serial.print(n);
    display.setCursor(10,0);
    display.print("networks found"); //Serial.println(" networks found");    
    display.display();
    for (int i = 0; i < n; ++i) {
      display.setCursor(0,10*i+10);
      display.print(i+1);           //Serial.print(i + 1);
      display.setCursor(7,10*i+10);
      display.print(":");           //Serial.print(":");
      display.setCursor(13,10*i+10);
      display.print(WiFi.SSID(i));  //Serial.print(WiFi.SSID(i));
      display.setCursor(95,10*i+10);
      display.print("(");           //Serial.print(" (");
      display.setCursor(100,10*i+10);
      display.print(WiFi.RSSI(i));  //Serial.print(WiFi.RSSI(i));
      display.setCursor(117,10*i+10);
      display.print(")");         //Serial.print(")");
      display.display();          //Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  display.display();
  Serial.println("");
  delay(5000);
}
