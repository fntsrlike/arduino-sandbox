#include <SoftwareSerial.h>

#define SERIAL_RATE 9600
#define HC05_BTRate 38400
#define HC06_BTRate 9600

#define MASTER_RX_PIN 8
#define MASTER_TX_PIN 9
#define MASTER_BT_RATE HC05_BTRate
#define SLAVE_RX_PIN 8
#define SLAVE_TX_PIN 9
#define SALVE_BT_RATE HC06_BTRate

SoftwareSerial MASTER_BT(RX_PIN, TX_PIN);
SoftwareSerial SLAVE_BT(RX_PIN, TX_PIN);

char data;

void setup() {
    serial_setup();
    bluetooth_setup();
}

void loop() {
    if (Serial.available()) {
        while (Serial.available() > 0) {
            data = Serial.read();
            BT.print(data);
        }
    }

    if (BT.available()) {
        waiting_data_recieved();
        LCD.clear();

        while (BT.available() > 0) {
            data = (char) BT.read();
            Serial.print(data);
            LCD.write(data);
        }
    }
}

void waiting_data_recieved() {
    delay(100);
}

void serial_setup() {
    Serial.begin(SERIAL_RATE);
    while (!Serial);
    Serial.println("Slave's serial is ready");
}

void bluetooth_setup() {
    MASTER_BT_RATE.begin(MASTER_BT_RATE);
    SLAVE_BT_RATE.begin(SLAVE_BT_RATE);
    BT.println("Slave's BT is ready");
}