#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
const double del = 1000/120;
const double maxV = 1;
double pos = 0;
int mode = 0;
double h = 4;

const int SW_pin = 2;
const int X_pin = A0;
const int Y_pin = A1;




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


  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  if(mode==0){
    for(int i = 0; i < 16; i++){
      writeLevel(func1(i+pos), i);
    }
    pos+=(maxV/512)*(analogRead(Y_pin)-513);
    if(h>8&&h>0&&abs(512-X_pin)>256){
      h+=1000/del;
      Serial.println("aaa");
    }
  }
  
  delay(del);
}

double func0(double x){
  return h*cos(x)+8;
}

double func1(double x){
  return 0.01*x*x;
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