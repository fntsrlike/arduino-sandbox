#include <SoftwareSerial.h>
#include <IRremote.h>
int RECV_PIN = 2; // 使用數位腳位2接收紅外線訊號
IRrecv irrecv(RECV_PIN); // 初始化紅外線訊號輸入
decode_results results; // 儲存訊號的結構
//SoftwareSerial mySerial(13,12); // RX, TX
const int negR=5; //5,6,9,10為UNO PWM腳位
const int posR=6;
const int negL=9;
const int posL=10;

//設定速度
const int Rspeed=200;
const int Lspeed=200;


char val;
void setup()
{
  pinMode(posR,OUTPUT);
  pinMode(negR,OUTPUT);
  pinMode(posL,OUTPUT);
  pinMode(negL,OUTPUT);   
 // mySerial.begin(9600);  //hc-05淘寶版本預設為9600bps
  Serial.begin(9600);
 irrecv.blink13(true); // 當收到訊號時，腳位13的LED便會閃爍
 irrecv.enableIRIn(); // 啟動接收
  
}
void loop() 
{
 if (irrecv.decode(&results))
    
   { // 接收紅外線訊號並解碼
    if(results.value==0xFD502A) //輸入自己的紅外線編碼
    {
  forward(Rspeed,Lspeed); //前進
    }
if(results.value==0xFF500A) //輸入自己的紅外線編碼
    {
   back(Rspeed,Lspeed); //後退
   }
if(results.value==0xFCD032) //輸入自己的紅外線編碼
    {
  left(Rspeed,Lspeed); //左轉
    }
if(results.value==0xFED012) //輸入自己的紅外線編碼
    {
  right(Rspeed,Lspeed); //右轉
   }
if(results.value==0xFC403B) //輸入自己的紅外線編碼
    {
  pause(0,0); //停止
    }
Serial.println(results.value, HEX);
irrecv.resume(); // 準備接收下一個訊號

}
}       

void forward(byte RmotorSpeed, byte LmotorSpeed)
{

    analogWrite(posR,0);
    analogWrite(negR,RmotorSpeed);         
    analogWrite(posL,0);
    analogWrite(negL,LmotorSpeed);   

}  
void back(byte RmotorSpeed, byte LmotorSpeed)
{
    
    analogWrite(posR,RmotorSpeed);
    analogWrite(negR,0);         
    analogWrite(posL,LmotorSpeed);
    analogWrite(negL,0);   
} 
void pause(byte RmotorSpeed, byte LmotorSpeed)
{
    analogWrite(posR,0);
    analogWrite(negR,0);         
    analogWrite(posL,0);
    analogWrite(negL,0);   
} 
void right(byte RmotorSpeed, byte LmotorSpeed)
{
    analogWrite(posR,0);
    analogWrite(negR,0);         
    analogWrite(posL,0);
    analogWrite(negL,LmotorSpeed);   
} 
void left(byte RmotorSpeed, byte LmotorSpeed)
{
    analogWrite(posR,0);
    analogWrite(negR,RmotorSpeed);         
    analogWrite(posL,0);
    analogWrite(negL,0);  
} 

 

