#include <SoftwareSerial.h>
#include <I2Cdev.h>
#include <Wire.h>
#include "MPU6050.h"

#define SERIAL_RATE 9600
#define HC05_BTRate 38400
#define HC06_BTRate 9600
#define RX_PIN 6
#define TX_PIN 5
#define BT_RATE HC05_BTRate

SoftwareSerial BTSerial(RX_PIN, TX_PIN);
MPU6050 accelgyro;

int16_t ax, ay, az; //三軸的傾斜值
int16_t gx, gy, gz; //本數據暫時用不到
char actionCode = 'e';     //停止
char OldActionCode = 'e';

void setup() {
    Wire.begin();
    Serial.begin(SERIAL_RATE);
    BTSerial.begin(BT_RATE);
    accelgyro.initialize();
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    if (ax > 11300)
        actionCode = 'e';  //停止
    if (az > 5400)
        actionCode = 'a';  //前進
    if (az < -5660)
        actionCode = 'b';  //後退
    if (ay < -5560)
        actionCode = 'c';  //左轉
    if (ay > 5400 )
        actionCode = 'd';  //右轉
    if (actionCode != OldActionCode){ //如果有新的動作才執行藍芽訊號傳送
        BTSerial.print(actionCode);
        Serial.print(actionCode);
        delay(300); //延遲一段時間避免頻繁的傳送訊號
    }
    OldActionCode = actionCode;
}

