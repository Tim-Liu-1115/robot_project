#include <PS2X_lib.h> //導入PS2搖桿庫v1.8
PS2X ps2x;

int PS2 = 0;

const int Aa = 4; // direction pin 1
const int Ab = 9; // direction pin 2

int fspeedLY; // 指定LY轉速變數

void setup(){
  
  PS2 = ps2x.config_gamepad(13,11,10,12, true, true); //指定PS2搖桿腳位及類比搖桿開啟
  
  pinMode(Aa, OUTPUT); // connection to TB6612FNG
  pinMode(Ab, OUTPUT); // connection to TB6612FNG
  
}

void loop(){
  ps2x.read_gamepad();
  
   
   if (ps2x.Analog(PSS_LY) == 128){
    analogWrite(Aa, 0);
    analogWrite(Ab, 0);
   }
   if (ps2x.Analog(PSS_LY) > 128){
    fspeedLY = map(ps2x.Analog(PSS_LY), 129, 255, 0, 150); // LY搖桿對應馬達驅動的值0~150即可以達到全速(配合電壓及馬達樣式調整)
    analogWrite(Aa, fspeedLY);
    digitalWrite(Ab, HIGH);
  }
   if (ps2x.Analog(PSS_LY) < 128){
    fspeedLY = map(ps2x.Analog(PSS_LY), 0, 127, 150, 0);
    digitalWrite(Aa, HIGH);
    analogWrite(Ab, fspeedLY);
  }
  
  delay(50);
} 
