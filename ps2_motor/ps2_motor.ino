#include <PS2X_lib.h>//導入PS2搖桿庫v1.

PS2X ps2x;
int PS2 = 0;

const int LFmotor1 = 22, LFmotor2 = 24;//左前輪腳位   
const int RFmotor1 = 26, RFmotor2 = 28;//右前輪腳位
const int LBmotor1 = 30, LBmotor2 = 32;//左後輪腳位
const int RBmotor1 = 34, RBmotor2 = 36;//右後輪腳位

int fspeedRY; 
int fspeedRX; 

void setup(){
  PS2 = ps2x.config_gamepad(13,11,12,10, true, true);//ps2接收器腳位(白,灰,棕,橘),黑:接地(GND),紅:3.3V

  pinMode(LFmotor1, OUTPUT), pinMode(LFmotor2, OUTPUT);
  pinMode(RFmotor1, OUTPUT), pinMode(RFmotor2, OUTPUT);
  pinMode(LBmotor1, OUTPUT), pinMode(LBmotor2, OUTPUT);
  pinMode(RBmotor1, OUTPUT), pinMode(RBmotor2, OUTPUT);
  
}
void loop(){
  Stop();
  
  ps2x.read_gamepad();      

  if (ps2x.Analog(PSS_RY) < 125 && ps2x.Analog(PSS_LY)<255)
      front();
  if (ps2x.Analog(PSS_RY) > 131 && ps2x.Analog(PSS_LY)<255) 
      back();
  if (ps2x.Analog(PSS_RX) > 131 && ps2x.Analog(PSS_LY)<255)
      right();
  if (ps2x.Analog(PSS_RX) < 125 && ps2x.Analog(PSS_LY)<255)
      left();
  if (ps2x.Button(PSB_R2))
      Rrotate();
  if (ps2x.Button(PSB_L2))
      Lrotate();
      
}
void Stop(){
  analogWrite(LFmotor1, 0);
  analogWrite(LFmotor2, 0);

  analogWrite(RFmotor1, 0);
  analogWrite(RFmotor2, 0);

  analogWrite(LBmotor1, 0);
  analogWrite(LBmotor2, 0);

  analogWrite(RBmotor1, 0);
  analogWrite(RBmotor2, 0);
}
void front(){
  //LFmotor反轉
  analogWrite(LFmotor1, LOW);
  analogWrite(LFmotor2, HIGH);
  //RFmotor正轉
  analogWrite(RFmotor1, HIGH);
  analogWrite(RFmotor2, LOW);
  //LBmotor反轉
  analogWrite(LBmotor1, LOW);
  analogWrite(LBmotor2, HIGH);
  //RBmotor正轉
  analogWrite(RBmotor1, HIGH);
  analogWrite(RBmotor2, LOW);
}
void back(){
  //LFmotor正轉
  analogWrite(LFmotor1, HIGH);
  analogWrite(LFmotor2, LOW);
  //RFmotor反轉
  analogWrite(RFmotor1, LOW);
  analogWrite(RFmotor2, HIGH);
  //LBmotor正轉
  analogWrite(LBmotor1, HIGH);
  analogWrite(LBmotor2, LOW);
  //RBmotor反轉
  analogWrite(RBmotor1, LOW);
  analogWrite(RBmotor2, HIGH);
}
void right(){
  //LFmotor反轉
  analogWrite(LFmotor1, LOW);
  analogWrite(LFmotor2, HIGH);
  //RFmotor反轉
  analogWrite(RFmotor1, LOW);
  analogWrite(RFmotor2, HIGH);
  //LBmotor正轉
  analogWrite(LBmotor1, HIGH);
  analogWrite(LBmotor2, LOW);
  //RBmotor正轉
  analogWrite(RBmotor1, HIGH);
  analogWrite(RBmotor2, LOW);
}
void left(){
  //LFmotor正轉
  analogWrite(LFmotor1, HIGH);
  analogWrite(LFmotor2, LOW);
  //RFmotor正轉
  analogWrite(RFmotor1, HIGH);
  analogWrite(RFmotor2, LOW);
  //LBmotor反轉
  analogWrite(LBmotor1, LOW);
  analogWrite(LBmotor2, HIGH);
  //RBmotor反轉
  analogWrite(RBmotor1, LOW);
  analogWrite(RBmotor2, HIGH);
}
void Lrotate(){
  //LFmotor正轉
  analogWrite(LFmotor1, HIGH);
  analogWrite(LFmotor2, LOW);
  //RFmotor正轉
  analogWrite(RFmotor1, HIGH);
  analogWrite(RFmotor2, LOW);
  //LBmotor正轉
  analogWrite(LBmotor1, HIGH);
  analogWrite(LBmotor2, LOW);
  //RBmotor正轉
  analogWrite(RBmotor1, HIGH);
  analogWrite(RBmotor2, LOW);
}
void Rrotate(){
  //LFmotor反轉
  analogWrite(LFmotor1, LOW);
  analogWrite(LFmotor2, HIGH);
  //RFmotor反轉
  analogWrite(RFmotor1, LOW);
  analogWrite(RFmotor2, HIGH);
  //LBmotor反轉
  analogWrite(LBmotor1, LOW);
  analogWrite(LBmotor2, HIGH);
  //RBmotor反轉
  analogWrite(RBmotor1, LOW);
  analogWrite(RBmotor2, HIGH);
}
