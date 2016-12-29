#include <Wire.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(8, 9); // HC-05的TXD,RXD腳位
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

char data;
void setup()
{
   lcd.begin(16, 2);
   BTSerial.begin(38400);
   serial_setup();
    lcd.print("Hello, World!");
}
void loop()
{
    if (Serial.available()) {
      while (Serial.available() > 0) {
          data = Serial.read();
          BTSerial.print(data);
      }
  }

 
  // 檢查是否有資料傳來
  if (BTSerial.available()) {
    delay(100);  //稍候一下，讓資料都到
    lcd.clear(); //清除 LCD 畫面
 // 讀取所有資料，並顯示在 LCD
   while (BTSerial.available() > 0) {
    data = (char) BTSerial.read();
            Serial.print(data);
            lcd.write(data);
    }
  }
}


void serial_setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Slave's serial is ready");
}
