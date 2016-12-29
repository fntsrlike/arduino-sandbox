#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "SoftwareSerial.h"

SoftwareSerial BT(10,11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	lcd.begin();
	lcd.backlight();
}

void loop()
{

}

