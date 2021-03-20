/* Чтобы добавить пункт в главное меню необходимо в loop(), в проверке на переполнение увеличить порог переполнения,
в функцции selectMenuPunct() добавить кейс.
-_-_-_-_Заготовки_-_-_-_-
  1.Подвал с кнопка назад вперед
    display.drawFastHLine(0,50,128,1);
    display.setCursor(0,53);
    display.print("<BACK");
    display.setCursor(98,53);
    display.print("NEXT>");
    display.display();
    Вариант отрисовки массива влажности при помощи цикла - неудачно
     display.drawLine(14,(minValue+43)-arr[0],22,(minValue+43)-arr[1],1);
    for (uint8_t i=0; i<10;i++){
      display.drawLine(22+(i*10),(minValue+43)-arr[i],22+((i+1)*10),(minValue+43)-arr[i+1],1);
    }
    uint8_t arr[10]={66,67,69,70,71,71,73,77,80,93}; // тестовый набор данных
    Перевод из значения в координату оси У 43=40(длинна оси, минимальный У)
    uint8_t yVal=(minValue+43)-arr[i];

  //display.drawRect(20,10,43,24,1);
  //display.drawRect(20,34,43,24,1);
  //display.drawRect(70,10,46,24,1);
  //display.drawRect(70,34,50,24,1);

  void drawDegreeSimbol(uint8_t x, uint8_t y){           // Отрисовка символа градуса
  display.drawPixel(x+0,y+0,1);
  display.drawPixel(x+1,y+0,1);
  display.drawPixel(x+2,y+0,1);
  display.drawPixel(x+3,y+0,1);
  display.drawPixel(x+0,y+1,1);//5
  display.drawPixel(x+0,y+2,1);
  display.drawPixel(x+0,y+3,1);
  display.drawPixel(x+1,y+3,1);
  display.drawPixel(x+2,y+3,1);
  display.drawPixel(x+3,y+3,1);//10
  display.drawPixel(x+3,y+2,1);
  display.drawPixel(x+3,y+1,1);
  display.display();
}

void timeConvert(){
  dayOfWeekConverter();
  timeNow1.years   = streetData1.timeNow / (3600*24*365) + 1969;
  timeNow1.mounths = streetData1.timeNow / 2628000 % 12;
  if(timeNow1.mounths == 0) timeNow1.mounths = 12;
  timeNow1.days    = (streetData1.timeNow / 86400 - (timeNow1.years-1970)/4) % 365;
  timeNow1.hours   = ((streetData1.timeNow + streetData1.timeOffset) / 3600 % 24);
  timeNow1.mins    = streetData1.timeNow / 60 % 60; 
  timeNow1.secs    = streetData1.timeNow % 60;
  
  short daysInMounth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  for (int i = 0; i < 12 ; i++)  {
    if(timeNow1.days < daysInMounth[i])
      break;
    timeNow1.days -= daysInMounth[i];
    if((timeNow1.years-1970)%4==0)
      timeNow1.days--;
  }

  //timeNow1.days=((( streetData1.timeNow / 86400)+4)%7);

}

void dayOfWeekConverter(){
  //short MounthCode, YearCode, lastYearOfYear;

  if (timeNow1.mounths == 4 || timeNow1.mounths == 7) MounthCode = 0;
  if (timeNow1.mounths == 1 || timeNow1.mounths == 10) MounthCode = 1;
  if (timeNow1.mounths == 5) MounthCode = 2;
  if (timeNow1.mounths == 8) MounthCode = 3;
  if (timeNow1.mounths == 2 || timeNow1.mounths == 3 || timeNow1.mounths == 11) MounthCode = 4;
  if (timeNow1.mounths == 6) MounthCode = 5;
  if (timeNow1.mounths == 12 || timeNow1.mounths == 9) MounthCode = 6;

  lastYearOfYear = timeNow1.years / 10 % 10 * 10 + 2020 % 10;
  YearCode = (6 + lastYearOfYear + lastYearOfYear / 4) % 7;
  timeNow1.dayOfWeek = (timeNow1.days + MounthCode + YearCode) % 7;
}
*/
