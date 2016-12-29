#include <Ultrasonic.h> //　使用超音波的程式庫
#include <IRremote.h>　//　使用紅外線的程式庫

int RECV_PIN = 11; // 紅外線訊號接腳

IRrecv irrecv(RECV_PIN);
decode_results results;

const int right1=5;  //右輪1
const int right2=6;  //右輪2
const int left1=9;   //左輪1
const int left2=10;  //右輪2
const int trig = 3; // 超聲波Trig Output接腳
const int echo = 13; // 超聲波Echo Input接腳
const int inter_time = 300;
int time = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(2,INPUT);
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  
}

void loop() {
  int d2 = digitalRead(2);
  int a0 = analogRead(A0);
  float duration, distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(300);
  digitalWrite(trig, LOW);
  duration = pulseIn (echo, HIGH);
  distance = (duration/2)/29;
  Serial.print("Data:");
  Serial.print (time/300);
  Serial.print(", d = ");
  Serial.print(distance);
  Serial.println(" cm");
  time = time + inter_time;
  Serial.print(d2);Serial.print(",");Serial.print(a0);  //寫下紅外線巡跡訊號
  delay(inter_time);
  
  if(distance<=5) { //超聲波距離少於5公分就後退
       Backware();
       Stop(); 
    } else{
       if (irrecv.decode(&results)) {
         if(results.value == 0x00FF629D)       { //按前動作
           Forware();
           //Stop();
         }else if(results.value==0x00FFA857)   { //按後動作
           Backware();   
           //Stop();
         } else if(results.value==0x00FFC23D)  { //按右動作
           Rightware();      
           Stop();
         } else if(results.value==0x00FF22DD)  { //按左動作
           Leftware();     
           Stop();
         } else if(results.value==0x00FF02FD)  { //按OK動作          
           Stop();      
         } else if(results.value==0x00FF6897)  { //按1動作
           Forware();
           delay(500);
           Backware();
           delay(500);
           Rightware();
           delay(500);
           Leftware();
           delay(500);
           Stop(); 
         } else if(results.value==0x00FF9867)  { //按2動作
           Backware();
           delay(500);
           Rightware();
           delay(500);
           Leftware();
           delay(500);
           Forware();
           delay(500);
           Stop();
         } else if(results.value==0x00FFB04F)  { //按3動作
           Rightware();
           delay(500);
           Rightware();
           delay(500);
           Rightware();
           delay(500);
           Rightware();
           delay(500);
           Stop();
         } else if(results.value==0x00FF4AB5)  { //按0動作
           if(d2==1){ //巡跡
              Rightware();
           }else{
              Backware();
           }
         }
    Serial.println(results.value, HEX); //寫入紅外線接收訊號
    irrecv.resume(); // Receive the next value
    
  }
  delay(100);
  }
}

void Forware(){//前進函數
  analogWrite(right1,255);
  analogWrite(right2,0);
  analogWrite(left1,255);
  analogWrite(left2,0);
  delay(300);
  }

void Backware(){//後退函數
  analogWrite(right1,0);
  analogWrite(right2,255);
  analogWrite(left1,0);
  analogWrite(left2,255);
  delay(300);
  }

void Rightware(){//右轉函數
  analogWrite(right1,255);
  analogWrite(right2,0);
  analogWrite(left1,0);
  analogWrite(left2,0);
  delay(300);
  }

void Leftware(){ //左轉函數
  analogWrite(right1,0);
  analogWrite(right2,0);
  analogWrite(left1,255);
  analogWrite(left2,0);
  delay(300);
  }
  
void Stop(){ //停止函數
  analogWrite(right1,0);
  analogWrite(right2,0);
  analogWrite(left1,0);
  analogWrite(left2,0);
  delay(300);
  }
