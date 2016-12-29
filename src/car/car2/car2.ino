#include <SoftwareSerial.h>

#define SERIAL_RATE 9600
#define HC05_BTRate 38400
#define HC06_BTRate 9600
#define RX_PIN 2
#define TX_PIN 3
#define BT_RATE HC06_BTRate

SoftwareSerial BTSerial(RX_PIN, TX_PIN);

const int negR=5; //5,6,9,10為UNO PWM腳位
const int posR=6;
const int negL=9;
const int posL=10;
const byte LED_PIN = 8;  // 定義LED腳位

//設定速度
const int RmotorSpeed=200;
const int LmotorSpeed=200;
char actionCode;

void setup()
{
    pinMode(posR,OUTPUT);
    pinMode(negR,OUTPUT);
    pinMode(posL,OUTPUT);
    pinMode(negL,OUTPUT);
    Serial.begin(SERIAL_RATE);
    Serial.println("setup finished");
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    if (Serial.available()) {
        while (Serial.available() > 0) {
            actionCode = (char) Serial.read();
            execute(actionCode);
        }
    }

    if (BTSerial.available()) {
        Serial.println("BT Recieved");
        waiting_data_recieved();
        while (BTSerial.available() > 0) {
            actionCode = (char) BTSerial.read();
            execute(actionCode);
        }
    }
}

void execute(char actionCode)
{
    Serial.println(actionCode);
    switch(actionCode)
    {
        case 'a':
            forward();
            break;
        case 'b':
            back();
            break;
        case 'c':
            left();
            break;
        case 'd':
            right();
            break;
        case 'e':
            pause();
            break;
        case '1':
            digitalWrite(LED_PIN, HIGH);
            BTSerial.println("LED ON");
            break;
        case '0':
            digitalWrite(LED_PIN, LOW);
            BTSerial.println("LED OFF");
            break;
    }
}

void forward()
{

        analogWrite(posR,0);
        analogWrite(negR,RmotorSpeed);
        analogWrite(posL,0);
        analogWrite(negL,LmotorSpeed);

}
void back()
{

        analogWrite(posR,RmotorSpeed);
        analogWrite(negR,0);
        analogWrite(posL,LmotorSpeed);
        analogWrite(negL,0);
}
void pause()
{
        analogWrite(posR,0);
        analogWrite(negR,0);
        analogWrite(posL,0);
        analogWrite(negL,0);
}
void right()
{
        analogWrite(posR,0);
        analogWrite(negR,0);
        analogWrite(posL,0);
        analogWrite(negL,LmotorSpeed);
}
void left()
{
        analogWrite(posR,0);
        analogWrite(negR,RmotorSpeed);
        analogWrite(posL,0);
        analogWrite(negL,0);
}


void waiting_data_recieved() {
    delay(100);
}
