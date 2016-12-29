// 匯入LiquidCrystal程式庫得標頭檔
#include <LiquidCrystal.h>

// 初始化LCD，建立物件lcd，指定腳位。
// 順序是RS、Enable、D4、D5、D6、D7
// 要配合前面的接線順序 
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

void setup(){
  // 指定LCD的尺寸，我用的是一列16個字，2列。 
  lcd.clear();
  lcd.begin(16, 2);

  // 印出Hello , World! 
  lcd.print("Hello, World!");
}

void loop(){
  // 欄跟列從0開始數
  // 所以第0列是上面那一列，第1列是下面那一列。
  // 第0欄是最左邊，第15欄是最右邊。
  lcd.setCursor(0, 1); // 將游標移動第0欄、第1列。

  // 顯示板子重置後經過的秒數 
  lcd.print(millis() / 1000);
}
