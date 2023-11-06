#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
const int del = 100;
int count = 0;
int mode = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
byte myLevels[8][8];

void setup() {
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(j<i){
        myLevels[7-i][j] = 0b00000;
      }else{
        myLevels[7-i][j] = 0b11111;
      }
    }
  }

  for(int i = 0; i < 8; i++){
    lcd.createChar(i, myLevels[i]);
  }




  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  for(int i = 0; i < 16; i++){
    writeLevel(15, i);
  }
  delay(del);
  // for(int i = 0; i < 16; i++){
  //   writeLevel(i, i);
  // }
}

void loop() {
  if(mode==0){
    for(int i = 0; i < 16; i++){
      writeLevel(func(i+count), i);
    }
  }
  count++;
  delay(del);
}

double func(double x){
  return 8*sin(x)+8;
}

int writeLevel(int lev, int x){
  lcd.setCursor(x, 1);
  if(lev>7){
    lcd.write(7);
    lcd.setCursor(x, 0);
    lcd.write(lev-8);
  }else{
    lcd.write(lev);
    lcd.setCursor(x, 0);
    lcd.write(" ");
  }
  return 1;
}