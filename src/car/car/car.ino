#include <SoftwareSerial.h>
#include <AFMotor.h>

#define SERIAL_RATE 9600
#define HC05_BTRate 38400
#define HC06_BTRate 9600
#define RX_PIN 14
#define TX_PIN 15
#define BT_RATE HC06_BTRate

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
SoftwareSerial BTSerial(RX_PIN, TX_PIN);

char actionCode;

void setup() {
    Serial.begin(SERIAL_RATE);
    BTSerial.begin(BT_RATE);
    motor1.run(RELEASE);
    motor2.run(RELEASE);

    Serial.println("setup finished.");
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

void waiting_data_recieved() {
    delay(100);
}

