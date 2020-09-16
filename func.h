//Файл содержит реализации функций
void startMessage(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(1);
  display.setCursor(30,20);
  display.print("Hello");
  display.display();
}
byte searchMaxValue(byte arr[], const byte SIZE=SIZEARR){ //  Ищет максимум в массивк
  byte maxValue=0;
  for(byte i=0;i<SIZE;i++){
    if(arr[i]>maxValue)
      maxValue=arr[i];
  }
  return maxValue;
}
byte searchMinValue(byte arr[], const byte SIZE=SIZEARR){ //  Ищет минимум в массиве
  byte minValue=arr[1];
  for(byte i=0;i<SIZE;i++){
    if(arr[i]<minValue)
      minValue=arr[i];
  }
  return minValue;
}
byte searchMidValue(byte arr[], const byte SIZE=SIZEARR){ //  Ищет среднее значение массива
  uint16_t sumOfarr=0;
  for(byte i=0;i<10;i++){
    sumOfarr+=arr[i];
  }
  return sumOfarr/SIZE;
}
void getLastData(){                                       // Получает данные от датчиков 
  int chk = DHT11.read(D1); // Опрос датчиков в глобальные переменные DHT11PIN 
  lastTemp=DHT11.temperature; 
  lastHum=DHT11.humidity;
  //lastLight= map(analogRead(A0),50,900,0,100);
  
  for(byte i=0; i<9;i++){ // перенос всех значий на еденицу влево, для записи нового элемента в конец массива
    temp[i]=temp[i+1];
    hum[i]=hum[i+1];
    //light[i]=light[i+1];
  }
  temp[SIZEARR-1]=lastTemp;
  hum[SIZEARR-1]=lastHum;
  //light[SIZEARR-1]=lastLight;
  count++;
  if(count>SIZEARR-1)
    count=0;
}
void drawKeyValue(uint8_t arr[],uint8_t SIZE=SIZEARR){    // Отрисовка ключевых значений: минимального, максимального, среднего значения из последних 10.
  display.clearDisplay();
  
  for(uint8_t i=0;i<SIZE;i++){ // Вывод всех анализируемых зачений. SIZE штук
    display.setCursor(18*i,0); // в первой строке(первая половина (5) значений)
    if(i>=SIZEARR/2)           // во второй строке (вторая половина)
      display.setCursor(18*(i-SIZEARR/2),10); // 18 - интервал между значениями( от начал до начала)
      
    if(i+1==count){ // Выделение квадратом текущего получаемого с датчика значения 
      if(i<SIZE/2)
        display.drawRect(18*i-2,-1,15,9,1);
      if(i>=SIZE/2)
        display.drawRect(18*(i-SIZE/2)-2,9,15,10,1);
    }
    display.print(arr[i]);
  }
  
  switch(selectedMenuPunct){ // Отрисовка символов значений 
    case 0:                  // В подпункте меню температуры дома
      for(uint8_t i=0;i<3;i++)  
        display.drawBitmap(105,20+(10*i),CelsiusSmallSimb, 4, 4,1);
    break;
    case 1:                 // В подпункте меню влажности дома
      for(uint8_t i=0;i<3;i++)
        display.drawChar(105,20+(10*i),37,1,0,1);
    break;
    default:
    break;
  }
  
  display.setCursor(0,20);
  display.print("Max of last ");
  display.setCursor(71,20);
  display.print(SIZEARR);
  display.setCursor(83,20);
  display.print(": ");
  display.setCursor(90,20);
  display.print(searchMaxValue(arr,SIZE));
  display.setCursor(0,30);
  display.print("Max of last ");
  display.setCursor(71,30);
  display.print(SIZEARR);
  display.setCursor(83,30);
  display.print(": ");
  display.setCursor(90,30);
  display.print(searchMinValue(arr,SIZE));
  display.setCursor(0,40);
  display.print("Mid of last ");
  display.setCursor(71,40);
  display.print(SIZEARR);
  display.setCursor(83,40);
  display.print(": ");
  display.setCursor(90,40);
  display.print(searchMidValue(arr,SIZE));
  display.display();
}
void drawAxes(uint8_t minValue, uint8_t arr[]){           // Отрисовка графика для влажности и освещенности
  if(minValue>=70)
    minValue=61;
  display.clearDisplay();
  display.drawFastVLine(14,0,64,1); // отрисовка осей координат : Y
  display.drawFastHLine(0,52,128, 1); // отрисовка осей координат : X
  for(short i=0;i<11;i++){ // отрисовка делений осей координат
      if(i<5) display.drawFastHLine(13,3+(10*i),3,1); // Y
      display.drawFastVLine(22+(10*i),51,3,1); // X
  }
  uint8_t val=(minValue/10)%10;
  for(short i = val; i < val+4;i++){ 
    display.setCursor(0,(i-val+1)*10);
    display.print((val*2-i+3)*10);
  }
  enc1.tick();
  for(short i = 0; i < 10;i++){ // Отрисовка значений горизонтальной оси
    display.setCursor(20+(10*i),56);
    display.print(i+1);
  }
  display.drawChar(3,0,37,1,0,1); // Символ влажности
  display.drawChar(3,56,'N',1,0,1); // Символ времени
  enc1.tick();
  display.drawLine(14, (minValue+43)-arr[0],22, (minValue+43)-arr[0],1);
  display.drawLine(22, (minValue+43)-arr[0],32, (minValue+43)-arr[1],1);
  display.drawLine(32, (minValue+43)-arr[1],42, (minValue+43)-arr[2],1);
  display.drawLine(42, (minValue+43)-arr[2],52, (minValue+43)-arr[3],1);
  display.drawLine(52, (minValue+43)-arr[3],62, (minValue+43)-arr[4],1);
  display.drawLine(62, (minValue+43)-arr[4],72, (minValue+43)-arr[5],1);
  display.drawLine(72, (minValue+43)-arr[5],82, (minValue+43)-arr[6],1);
  display.drawLine(82, (minValue+43)-arr[6],92, (minValue+43)-arr[7],1);
  display.drawLine(92, (minValue+43)-arr[7],102,(minValue+43)-arr[8],1);
  display.drawLine(102,(minValue+43)-arr[8],112,(minValue+43)-arr[9],1);
  display.display();
}
void drawTempAxes(uint8_t minValue, uint8_t arr[]){       // Отрисовка графика для температуры
  display.clearDisplay();
  display.drawFastVLine(14,0,64,1);   // отрисовка осей координат : Y
  display.drawFastHLine(0,52,128, 1); // отрисовка осей координат : X
  for(short i=0;i<11;i++){            // отрисовка делений осей координат
      if(i<5) display.drawFastHLine(13,3+(10*i),3,1); // Y
      display.drawFastVLine(22+(10*i),51,3,1);        // X
  }
  for(short i = minValue; i < minValue+4;i++){        //Отрисовка значений вертикальной оси
    display.setCursor(0,(i-minValue+1)*10);
    display.print(minValue*2-i+3);
  }
  for(short i = 0; i < 10;i++){                       // Отрисовка значений горизонтальной оси
    display.setCursor(20+(10*i),56);
    display.print(i+1);
  }
  display.drawBitmap(3,0,CelsiusSmallSimb, 4, 4,1); // Символ градуса
  display.drawChar(3,56,'N',1,0,1); // Символ времени
  display.drawLine(14, 43+(minValue-arr[0])*10 ,22, 43+(minValue-arr[0])*10,1);
  display.drawLine(22, 43+(minValue-arr[0])*10 ,32, 43+(minValue-arr[1])*10,1);
  display.drawLine(32, 43+(minValue-arr[1])*10 ,42, 43+(minValue-arr[2])*10,1);
  display.drawLine(42, 43+(minValue-arr[2])*10 ,52, 43+(minValue-arr[3])*10,1);
  display.drawLine(52, 43+(minValue-arr[3])*10 ,62, 43+(minValue-arr[4])*10,1);
  display.drawLine(62, 43+(minValue-arr[4])*10 ,72, 43+(minValue-arr[5])*10,1);
  display.drawLine(72, 43+(minValue-arr[5])*10 ,82, 43+(minValue-arr[6])*10,1);
  display.drawLine(82, 43+(minValue-arr[6])*10 ,92, 43+(minValue-arr[7])*10,1);
  display.drawLine(92, 43+(minValue-arr[7])*10 ,102,43+(minValue-arr[8])*10,1);
  display.drawLine(102,43+(minValue-arr[8])*10 ,112,43+(minValue-arr[9])*10,1);
  display.display();
}

void windDirection(int degree){
  display.setTextSize(1);
  display.setCursor(0,0);
  if(degree > 337.5 && degree < 22.5)   display.print("S");     // СЕВЕР 
  if(degree > 22.5 && degree < 67.5)    display.print("S-V");   // СЕВЕРО-ВОСТОК 
  if(degree > 67.5 && degree < 112.5)   display.print("V");     // ВОСТОК
  if(degree > 112.5 && degree < 157.5)  display.print("UG-V");  // ЮГО-ВОСТОК  
  if(degree > 157.5 && degree < 202.5)  display.print("UG");    // ЮГ 
  if(degree > 202.5 && degree < 247.5)  display.print("UG-Z");  // ЮГО-ЗАПАД 
  if(degree > 247.5 && degree < 292.5)  display.print("Z");     // ЗАПАД  
  if(degree > 292.5 && degree < 337.5)  display.print("S-Z");   // СЕВЕРО-ЗАПАД  
  //windDirection(streetData1.windDegree);
}
void drawWeatherIcon(){                                // Отрисовка иконок погоды
  if (streetData1.skyIconCode == 200 || streetData1.skyIconCode == 201 || streetData1.skyIconCode == 202 || streetData1.skyIconCode == 210 || streetData1.skyIconCode == 211 || streetData1.skyIconCode ==212 || streetData1.skyIconCode ==221 || streetData1.skyIconCode == 230 || streetData1.skyIconCode == 231 || streetData1.skyIconCode == 232)
    display.drawBitmap(73,38,stormIcon, 18, 18,1); // Гроза
  if (streetData1.skyIconCode == 300 || streetData1.skyIconCode == 301 || streetData1.skyIconCode == 302 || streetData1.skyIconCode == 310 || streetData1.skyIconCode == 311 || streetData1.skyIconCode == 312 || streetData1.skyIconCode == 313 || streetData1.skyIconCode == 314 || streetData1.skyIconCode == 321)
    display.drawBitmap(73,38,rainIcon, 18, 18,1); // Дождь
  if (streetData1.skyIconCode == 500 || streetData1.skyIconCode == 501 || streetData1.skyIconCode == 502 || streetData1.skyIconCode == 503 || streetData1.skyIconCode == 504 || streetData1.skyIconCode == 511 || streetData1.skyIconCode == 520 || streetData1.skyIconCode == 521 || streetData1.skyIconCode == 522 || streetData1.skyIconCode == 531)
    display.drawBitmap(73,38,rainIcon, 18, 18,1); // Дождь
  if(streetData1.skyIconCode == 600 || streetData1.skyIconCode == 601 || streetData1.skyIconCode == 602 || streetData1.skyIconCode == 611 || streetData1.skyIconCode == 612 || streetData1.skyIconCode == 613 || streetData1.skyIconCode == 615 || streetData1.skyIconCode == 616 || streetData1.skyIconCode == 620 || streetData1.skyIconCode == 621 || streetData1.skyIconCode == 622)
    display.drawBitmap(73,38,snowIcon, 18, 18,1); // Снег
  if(streetData1.skyIconCode == 701 || streetData1.skyIconCode == 711 || streetData1.skyIconCode == 721 || streetData1.skyIconCode == 731 || streetData1.skyIconCode == 741 || streetData1.skyIconCode == 751 || streetData1.skyIconCode == 761 || streetData1.skyIconCode == 762 || streetData1.skyIconCode == 771 || streetData1.skyIconCode == 781)
    display.drawBitmap(73,38,mistIcon, 18, 18,1); // Туман
  if(streetData1.skyIconCode == 800)
    display.drawBitmap(73,38,clearSkyIcon, 18, 18,1); // Clear sky 
  if(streetData1.skyIconCode == 801) 
    display.drawBitmap(73,38,lightCloudyIcon, 18, 18,1); // Облочность с прояснениями
  if(streetData1.skyIconCode == 802 || streetData1.skyIconCode == 803 || streetData1.skyIconCode == 804)
    display.drawBitmap(73,38,cloudyIcon, 18, 8,1); // Облочность жесткая
}

void drawMenuData (){                                  //Отрисовка главного меню
  // Шапка
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(30,0);
  display.print("HOME");
  display.setCursor(76,0);
  display.print("STREET");
  display.setTextSize(2);
  display.drawBitmap(3,4,settingsIcon, 11, 11,1);
  display.drawBitmap(3,22,aboutIcon, 12, 12,1);
  display.drawBitmap(3,40,calendarIcon, 11, 12,1);
  
  // Дома
  display.setCursor(27,15); // ЛЕВО-ВЕРХ
  display.print(lastTemp);        // Температура дома
  display.drawBitmap(50,15,CelsiusLargeSimb, 6, 6,1);
  display.setCursor(24,40); // ЛЕВО-НИЗ
  display.print(lastHum);        //Влажность дома
  display.drawChar (49, 40, 37, 1, 0, 2);  
  
  // На улице
  display.setCursor(80,15); // ПРАВО-ВЕРХ
  display.print(streetData1.temp);        //Температура улица
  display.drawBitmap(104,14,CelsiusLargeSimb, 6, 6,1);                            
  display.setTextSize(1);   // ПРАВО-НИЗ
  
  display.setCursor(95,38); //Влажность
  display.print(streetData1.hum);
  display.drawChar (108, 38, 37, 1, 0, 1);
  
  display.setCursor(95,48); //Давление
  display.print(streetData1.pressure);
  display.setCursor(114,48);
  display.print("mm");
  drawWeatherIcon();
  display.display();
}
void drawSelectBox(uint8_t selectedMenuPunct=0){       // Отрисовка выбранного прямоугольника
  if(millis()-prTime5<5000){
    switch(selectedMenuPunct){
      case 0: display.drawRect(20,10,43,24,1);  // Пункт меню температуры дома
      break;
      case 1: display.drawRect(20,34,43,24,1);  // Влажность дома
      break;
      case 2: display.drawRect(70,10,54,54,1);  // Метеосводка  (НЕРЕАЛИЗОВАННО)
      break;
      case 3: display.drawRect(1,1,17,17,1);    // Настройки
      break;
      case 4: display.drawRect(0,19,18,18,1);   // О авторе
      break;
      case 5: display.drawRect(0,37,17,18,1);   // Календарь          (НЕРЕАЛИЗОВАННО)
      break;  
      default:
      break;
    }
  }
  display.display();
}
void seconds(int rate){                                // Функции отрисовки частоты обновления данных
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  display.print("Updating rate: ");
  display.setCursor(86,0);
  display.print(rate);
  display.setCursor(103,0);
  display.print("sec.");
  display.display();
}
void minutes(uint16_t rate){
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  display.print("Updating rate: ");
  display.setCursor(86,0);
  display.print(rate/60);
  display.setCursor(103,0);
  display.print("min.");
  display.setCursor(86,10);
  display.print(rate%60);
  display.setCursor(103,10);
  display.print("sec.");
  display.display();
}
void hourses(uint16_t rate){
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  display.print("Updating rate: ");
  display.setCursor(86,0);
  display.print(rate/3600);
  display.setCursor(103,0);
  display.print("hou.");
  display.setCursor(86,10);
  display.print(rate/60%60);
  display.setCursor(103,10);
  display.print("min.");
  display.setCursor(86,20);
  display.print(rate%60);
  display.setCursor(103,20);
  display.print("sec.");
  display.display();
}

void homeTempPunctMenu(){            // Меню температуры дома
  while(!enc1.isPress()){       // Остоваться в меню до нажатиия энкодера
    enc1.tick();
    if(millis()-prTime2>=UPDATETIME){ // Каждые 2 секунды перерисовывать подпункт меню 
      getLastData();            // Опрос датчиков
      drawKeyValue(temp);       // Отрисовка
      prTime2=millis();         // Обнуление таймера
    }
    if(enc1.isTurn()){          // Если был поворот энкодера
      while(!enc1.isPress()){   // Остовать до нажатиия энкодера
        enc1.tick();
        if(millis()-prTime3>=UPDATETIME){                    // Каждые 2 секунды перерисовывать подпункт меню
          getLastData();                                    // Опрос датчиков
          drawTempAxes(searchMinValue(temp,SIZEARR),temp);  // Отрисовка диаграммы 
          prTime3=millis();                                 // Обнуление таймера
        }
      }
    }
  }
}
void homeHumPunctMenu(){             // Меню влажности дом
  while(!enc1.isPress()){
    enc1.tick();
    if(millis()-prTime2>=UPDATETIME){
      getLastData();
      drawKeyValue(hum);
      
      display.display();
      prTime2=millis();
    }
    if(enc1.isTurn()){
      while(!enc1.isPress()){
        enc1.tick();
        if(millis()-prTime3>=UPDATETIME){
          getLastData();
          drawAxes(searchMinValue(hum,SIZEARR),hum);
          prTime3=millis();
        }
      }
    }
  }
}
void LightPunctMenu(){               // Меню температуры на улице
  while(!enc1.isPress()){
    enc1.tick();
    if(millis()-prTime2>=UPDATETIME){
      getLastData();
      drawKeyValue(light);
      display.display();
      prTime2=millis();
    }
    if(enc1.isTurn()){
      while(!enc1.isPress()){
        enc1.tick();
        if(millis()-prTime3>=UPDATETIME){
          getLastData();
          drawAxes(searchMinValue(light,SIZEARR),light);
          prTime3=millis();
        }
      }
    }
  }
}
void SettingsPunctMenu(){            // Меню настроек
  display.clearDisplay();
  seconds(rate);
  while(!enc1.isPress()){
    enc1.tick();
    if(enc1.isLeft()){ 
      if(rate<=60){  // Если частота меньше минуты
        rate--;      // Отнимаем секунду
        seconds(rate);   // Отрисовываем
      }
      if(rate>60 && rate<=3600){  // Если частота меньше часа
        rate-=5;                 // Отниммем 5 секунд
       minutes(rate);           // Отрисовываем
      }
      if(rate>3600){  // Если частота больше часа
        rate-=300;    // Отнимаем 5 минут
        hourses(rate);   // Отрисовываем
      }
      if(rate<1) rate=1;
    }
    enc1.tick();
    if(enc1.isRight()){
      if(rate<=60){ // Если частота меньше минуты
        rate++;     // Прибавляем секунду
        seconds(rate);  // Отрисовываем
      }
      if(rate>60 && rate<=3600){  // Если частота меньше часа
        rate+=5;                  // Прибавляем 5 секунд
        minutes(rate);            // Отрисовываем
      }
      if(rate>3600){ // Если частота больше часа
        rate+=300;   // Прибавляем 5 минут
        hourses(rate);  // Отрисовываем
      }
    }
  }  
}
void AboutPunctMenu(){               // Функция с информацией
  while(!enc1.isPress()){
    enc1.tick();
    if(millis()-prTime4>10000){
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Author:");
      display.setCursor(0,10);
      display.print("Nikolay Holyas");
      display.setCursor(0,20);
      display.print("@lite_go_95");
      display.setCursor(0,30);
      display.print("ngolyas123@gmail.com");
      display.display();
      prTime4=millis();
    }
  }
}
void weatherMenuPoint(){             // Меню погоды
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Weather (in work)");
  display.display();
}
void calendarMenuPoint(){            // Календарь
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Calendar (in work)");
  display.display();
}
void selectMenuPunct(byte selectedMenuPunct){ //Выбор пункта меню
  switch(selectedMenuPunct){
    case 0: homeTempPunctMenu();  // Пункт меню температуры дома
    break;
    case 1: homeHumPunctMenu();   // Влажность дома
    break;
    case 2: weatherMenuPoint();   // Метеосводка  (НЕРЕАЛИЗОВАННО)
    break;
    case 3: SettingsPunctMenu();  //Настройки
    break;
    case 4: AboutPunctMenu();     // О авторе
    break;
    case 5: calendarMenuPoint();    // Календарь      (НЕРЕАЛИЗОВАННО)
    break;
  }
}

void encoderRightTurn(){
  selectedMenuPunct++;
    prTime5=millis();
    if(selectedMenuPunct>5)
      selectedMenuPunct=0;
    drawMenuData();
    drawSelectBox(selectedMenuPunct);
}
void encoderLeftTurn(){
  selectedMenuPunct--;
    prTime5=millis();
    if(selectedMenuPunct<0)
      selectedMenuPunct=5;  
    drawMenuData();
    drawSelectBox(selectedMenuPunct);
}
//gow a