#include <Wire.h>             //Библиотека I2C.
#include <Adafruit_BMP085.h>  //Библиотека датчика.
#include <EEPROM.h>           //Библиотека для работы с EEPROM памятью.
#include <TimerOne.h>

Adafruit_BMP085 bmp;     //Инициализация датчика.

unsigned long period_bmp = 0;

boolean button_flag = 0;                //Признак нажатия кнопки.
unsigned long button_press_time = 0;    //Фиксация момента нажатия кнопки.
unsigned long button_timer = 0;         //Время в течении которого кнопка нажата.

int ground_alt = 0;   //Высота фиксируемая на момент включения устройства. Высота аэродрома.
int cur_alt = 0;      //Текущая высота.
int max_alt =0;       //Максимальная высота с момента последнего включения устройства (хранится до отключения питания).

byte code[12]={192,252,146,152,172,137,129,220,128,136,227,191}; //Кодовая таблица.

void setup()
{ 
  bmp.begin(2);                     //Инициализация датчика. Число в скобках - настройка качества измерений, от 0 до 3. Чем больше тем точнее, но и медленнее.
  ground_alt = bmp.readAltitude();  //Фиксация высоты аэродрома.
  
  pinMode(8, INPUT); 
  
                                   //Пины зажигания разрядов.
  pinMode(10, OUTPUT);//1-й
  pinMode(11, OUTPUT);//2-й
  pinMode(12, OUTPUT);//3-й
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
                                    //Пины зажигания сегментов (регистр D), пины с 0 по 7.
  DDRD=255;

  Timer1.initialize(20000);
  Timer1.attachInterrupt(indication);

  
  
}

void loop()
{
    if (millis() - period_bmp > 100)           
      {      
        period_bmp = millis();
        cur_alt = bmp.readAltitude() - ground_alt;
        // Serial.println(cur_alt);  
         
        if (max_alt < cur_alt && button_flag == 0)          //Фиксация максимальной высоты.
          {max_alt = cur_alt;}    
       }          

button();
 
}

void indication ()             //Функция вывода символов на дисплей.
{
 if (button_timer < 3999)      //Проверка отсутствия нажатой кнопки.
{
 /* digitalWrite(10, LOW);       //Очистка дисплея в начале цикла.
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  DDRD=255;*/
  
 if (cur_alt >= 0 && cur_alt <= 999)
 {
  int a = cur_alt%10;
  PORTD=code[a];
  digitalWrite(10, HIGH);
  delay(80);
  digitalWrite(10, LOW);
  int b = cur_alt/10%10;
  PORTD=code[b];
  digitalWrite(11, HIGH);
  delay(100);
  digitalWrite(11, LOW);
  int c = (cur_alt/100);
  PORTD=code[c];
  digitalWrite(12, HIGH);
  delay(100);
  digitalWrite(12, LOW); 
 }
 else if (cur_alt > 999) 
 {PORTD=code[11];
  digitalWrite(10, HIGH);}
 else if (cur_alt < 0 && cur_alt >= -99)
 {int a = abs(cur_alt)%10;
  PORTD=code[a];
  digitalWrite(10, HIGH);
  delay(50);
  digitalWrite(10, LOW);
  int b = abs(cur_alt)/10%10;
  PORTD=code[b];
  digitalWrite(11, HIGH);
  delay(50);
  digitalWrite(11, LOW);
  PORTD=code[11];
  digitalWrite(12, HIGH);
  delay(10);
  digitalWrite(12, LOW);
  } 
}

}

void button ()
{
                                                       //Обработка состояний кнопки.
                                                           //*
       if (digitalRead(8) == HIGH && button_timer < 2000)  //При нажатии и удержании кнопки выводит максимальную высоту с момента включения устройства.
          { cur_alt = max_alt;}
            
           if (digitalRead(8) == HIGH && button_flag == 0) //Запоминаем момент нажатия кнопки.
           {button_flag = 1;
            button_press_time = millis();}
            
       if ( digitalRead(8) == HIGH && button_flag == 1)    //Вычисляем длительность нажатия кнопки.
            {button_timer = millis() - button_press_time;}
            
       if (digitalRead(8) == HIGH && button_timer > 2000)  //Если кнопка удерживается больше 2 секунд - выводим сохраненную максимальную высоту из EEPROM.
             {byte H_Byte = EEPROM.read(0);
              byte L_Byte = EEPROM.read(1);
              cur_alt = word(H_Byte, L_Byte);
              
          //cur_alt = EEPROM.read(0)*4;
               }
              
        if (digitalRead(8) == HIGH && button_timer > 4000) //Если кнопка удерживается больше 4 секундв - записываем текущую максимальную высоту в EEPROM.
             {byte H_Byte = highByte(max_alt);
              byte L_Byte = lowByte(max_alt);
              EEPROM.write(0, H_Byte);
              EEPROM.write(1, L_Byte);
          //  EEPROM.write(0, max_alt/4);
              while(digitalRead(8) == HIGH)
              {PORTD=code[5];
               digitalWrite(11, HIGH);
               delay(2000);}                               //Задержка после записи максимального значения в EEPROM, чтобы не мучить его большим количеством перезаписей.
             }
             
       if (digitalRead(8) == LOW && button_flag == 1)      //Обработка отпускания кнопки, начинаем снова показывать текущую высоту.
       {button_flag = 0;
        button_timer = 0;
        cur_alt = bmp.readAltitude() - ground_alt;}
}
