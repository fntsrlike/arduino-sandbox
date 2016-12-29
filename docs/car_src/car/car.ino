#include <SoftwareSerial.h>   // 引用程式庫
#include <AFMotor.h>
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(14, 15); // 傳送腳, 接收腳,也就是類比腳位A0和A1.
char act;  // 儲存接收資料的變數
 
void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
 }
 
void loop()
{
  if (BT.available())
  {
    act = BT.read();
    Serial.println(act);//序列埠監視窗(查看程式執行情形)
    switch(act)
    {
      case 'a':
        forward();
        break;
      case 'b':
        backward();
        break;
      case 'c':
        left();
        break;
      case 'd':
        right();
        break;
      case 'e':
        motorstop();
        break;  
    }
  }
}
 
void forward()
{
  motor1.setSpeed(120);
  motor1.run(FORWARD);
  motor2.setSpeed(120);
  motor2.run(FORWARD);
 }
void backward()
{
  motor1.setSpeed(120);
  motor1.run(BACKWARD);
  motor2.setSpeed(120);
  motor2.run(BACKWARD);
 }
 
void right()
{
  motor1.setSpeed(80);
  motor1.run(FORWARD);
  motor2.setSpeed(80);
  motor2.run(BACKWARD);
 }
 
void left()
{
  motor1.setSpeed(80);
  motor1.run(BACKWARD);
  motor2.setSpeed(80);
  motor2.run(FORWARD);
 }
 
void motorstop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(100);
 
}
 

