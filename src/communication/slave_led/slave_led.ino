#include <SoftwareSerial.h>
#define SERIAL_RATE 9600
#define HC05_BTRate 38400
#define HC06_BTRate 9600

#define RX_PIN 12
#define TX_PIN 13
#define BT_RATE HC06_BTRate

const byte LED_PIN = 8;  // 定義LED腳位

SoftwareSerial BTSerial(RX_PIN, TX_PIN);
char data;

void setup() {
    BTSerial.begin(BT_RATE);
    delay(100);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    if (BTSerial.available()) {
        waiting_data_recieved();

        while (BTSerial.available() > 0) {
            data = (char) BTSerial.read();
            if (data == '1') {
                digitalWrite(LED_PIN, HIGH);
                // 回應命令發送端，告知「已開燈」
                BTSerial.println("LED ON");
            } else if (data == '0') {
                digitalWrite(LED_PIN, LOW);
                // 回應命令發送端，告知「已關燈」
                BTSerial.println("LED OFF");
            }
        }
    }
}

void waiting_data_recieved() {
    delay(100);
}
