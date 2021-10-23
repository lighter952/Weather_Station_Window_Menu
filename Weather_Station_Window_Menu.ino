#include <Arduino.h>
#include <dht11.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include<GyverEncoder.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include "GyverButton.h"

#define XDATA 90          // Размещение данных по Х
#define XSIMB (XDATA+13)  // Размещение символов по Х
#define SIZEARR 10
#define UPDATETIME (rate*1000)
//#define DEBUG
#define NOEnternerDEB 1

short MounthCode, YearCode, lastYearOfYear;
struct timeNow {
  int hours;
  int mins;
  int secs;
  int days;
  int mounths;
  int years;
  short dayOfWeek;
} timeNow1;

struct streetData {
  int timeOffset = 0;
    long timeNow = 0;
    int skyIconCode = 0;
    int pressure = 0;
    int temp = 0;
    byte hum = 0;
    byte windSpeed = 0;
    byte windDegree = 0;
} streetData1;

const char* host = "api.openweathermap.org";
String lineFromServer;
uint8_t count=0; 
int8_t selectedMenuPunct=0;
uint8_t temp[10], hum[10],light[10];
uint8_t lastTemp, lastHum, lastLight;
uint16_t rate=1;
unsigned long prTime1=0,prTime2=0,prTime3=0,prTime4=10000,prTime5=0, prTime6=0;
 // №1 Для меню; №2 Для подпунктов ключевых значений; №3 для графиков; №4 для About;

#include "UnixDate.h"

dht11 DHT11;
Adafruit_SSD1306 display(128,64,&Wire,5);
Encoder enc1(D5, D6, D7); // CLK  DT SW
UnixDate date;
GButton butt1(D4);
GButton butt2(D5);

#include "BitMaps.h"
#include "func.h"
#include "streetWeatherFunc.h"


void setup() {
  enc1.setType(TYPE2);
  butt1.setType(LOW_PULL);
  Wire.begin(D3, D2);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  #if DEBUG
    Serial.begin(115200);
  #endif
  startMessage();
  #if NOEnternerDEB == 1 // 1 - с использованием интернета
    WiFi.begin("Tanya", "9RT_8fg-7vb.");
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    while(streetData1.hum==0){
      bool i = 0;
      if(i==0){
        getWeatherFromOWM();
        i=1;
      }
    }
  #endif
  getLastData();
  drawMenuData();
  drawSelectBox();
  
}

void loop() {
  if(enc1.isRight())
    encoderRightTurn();
  if(enc1.isLeft())
    encoderLeftTurn();
  if(enc1.isPress())
    selectMenuPunct(selectedMenuPunct);    
  if(millis()-prTime1>=4000){
    getLastData();
    drawMenuData();
    drawSelectBox(selectedMenuPunct);
    prTime1 += 4000;
  }
  if(millis()-prTime6>180*1000) {
    prTime1=millis();
    getWeatherFromOWM();
  }
  enc1.tick();
}
