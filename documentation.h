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
*/
