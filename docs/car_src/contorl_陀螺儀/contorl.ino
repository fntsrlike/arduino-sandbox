#include <I2Cdev.h>//舊的Arduino版本需要引用程式庫
#include <Wire.h>　//舊的Arduino版本需要引用程式庫
#include "MPU6050.h" //引用程式庫
#include <SoftwareSerial.h>   // 引用程式庫
SoftwareSerial BT(6, 5); // 傳送腳, 接收腳
MPU6050 accelgyro;
 
int16_t ax, ay, az;//三軸的傾斜值
int16_t gx, gy, gz;//本數據暫時用不到
char act = 'e'; //停止
char Oldact = 'e';
 
void setup() {
  Wire.begin();
  Serial.begin(38400);   // 與電腦序列埠連線,可監控程式執行情形
  accelgyro.initialize(); //啟動MPU6050
  BT.begin(38400);  //啟動藍芽
  }
 
void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  if(ax > 11300)
    act = 'e';  //停止
  if(az > 5400)
    act = 'a';  //前進
  if(az < -5660)
    act = 'b';  //後退
  if(ay < -5560)
    act = 'c';  //左轉
  if(ay > 5400 )
    act = 'd';  //右轉
  if(act != Oldact){ //如果有新的動作才執行藍芽訊號傳送
    BT.print(act);
    Serial.println(act);
    delay(300); //延遲一段時間避免頻繁的傳送訊號
  }
 Oldact = act;
}

