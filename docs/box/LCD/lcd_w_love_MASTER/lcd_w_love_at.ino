#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // HC-05的TXD,RXD腳位

char data;

void setup() {
  BTSerial.begin(38400);
  serial_setup();
  
  //稍等一秒後再送資料給遠方
  delay(1000);
  BTSerial.write("NOM");
}
void loop()
{
   if (Serial.available()) {
      while (Serial.available() > 0) {
          data = Serial.read();
          BTSerial.print(data);
      }

       while (BTSerial.available() > 0) {
    data = (char) BTSerial.read();
            Serial.print(data);            
    }
}

}



void serial_setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Master's serial is ready");
}

