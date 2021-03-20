streetData parseDataFromOWM(){
  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, lineFromServer);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
  }
  streetData1.temp =(doc["current"]["temp"].as<int>());
  streetData1.hum =(doc["current"]["humidity"].as<byte>());
  streetData1.pressure =((doc["current"]["pressure"].as<int>())*0.75);
  streetData1.skyIconCode =(doc["current"]["weather"][0]["id"].as<int>());
  streetData1.windDegree=(doc["currengitt"]["wind_deg"].as<byte>());
  streetData1.windSpeed=(doc["current"]["wind_speed"].as<byte>());
  streetData1.timeNow=(doc["current"]["dt"].as<long>());
  streetData1.timeOffset=(doc["timezone_offset"].as<int>());
  return streetData1;
}

void getWeatherFromOWM() {
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
  }
  client.println("GET /data/2.5/onecall?lat=53.902512&lon=27.561481&exclude=hourly,daily&units=metric&appid=42fc6c4f5fd9135f7b61759ee9b9fb01");
  client.println("Host: samples.openweathermap.org"); // говорим к какому хосту обращаемся (на сервере может быть несколько сайтов)
  client.println("Connection: close"); // говорим что закончили
  client.println();
  Serial.println("");
  delay(1000);
  while(client.available()){
   lineFromServer = client.readStringUntil('\0'); 
   Serial.println(lineFromServer);
  }
  streetData1 = parseDataFromOWM(); // парсим данные из строки ответа сервера в структуры
  date.UnixDateUpdate(streetData1.timeNow, 3);
}