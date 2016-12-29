#include <SoftwareSerial.h>
#define SERIAL_RATE 9600
#define HC05_BTRate 38400
#define HC06_BTRate 9600

#define RX_PIN 12
#define TX_PIN 13
#define BT_RATE HC05_BTRate

SoftwareSerial BTSerial(RX_PIN, TX_PIN);
char data;

void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Slave's serial is ready");

    BTSerial.begin(38400);
    delay(100);
    BTSerial.println("Slave's BT is ready");
}

void loop() {
    if (Serial.available()) {
        while (Serial.available() > 0) {
            data = Serial.read();
            BTSerial.print(data);
        }
    }

    if (BTSerial.available()) {
        waiting_data_recieved();

        while (BTSerial.available() > 0) {
            data = (char) BTSerial.read();
            Serial.print(data);
        }
    }
}

void waiting_data_recieved() {
    delay(100);
}
