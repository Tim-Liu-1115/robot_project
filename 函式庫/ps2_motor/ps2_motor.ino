#include <PS2X_lib.h>//導入PS2搖桿庫v1.

PS2X ps2x;
int PS2 = 0;

const int LFmotor1 = 26, LFmotor2 = 28, LFpwm = 3;//左前輪腳位   ※pwm要接到arduino mega有pwm標示的位子※
const int RFmotor1 = 22, RFmotor2 = 24, RFpwm = 4;//右前輪腳位
const int LBmotor1 = 30, LBmotor2 = 32, LBpwm = 5;//左後輪腳位
const int RBmotor1 = 34, RBmotor2 = 36, RBpwm = 2;//右後輪腳位

int fspeedRY; 
int fspeedRX; 

void setup(){
  PS2 = ps2x.config_gamepad(13,11,12,10, true, true);//ps2接收器腳位(白,灰,棕,橘),黑:接地(GND),紅:3.3V

  pinMode(LFmotor1, OUTPUT), pinMode(LFmotor2, OUTPUT), pinMode(LFpwm, OUTPUT);
  pinMode(RFmotor1, OUTPUT), pinMode(RFmotor2, OUTPUT), pinMode(RFpwm, OUTPUT);
  pinMode(LBmotor1, OUTPUT), pinMode(LBmotor2, OUTPUT), pinMode(LBpwm, OUTPUT);
  pinMode(RBmotor1, OUTPUT), pinMode(RBmotor2, OUTPUT), pinMode(RBpwm, OUTPUT);
  
}
void loop(){
  ps2x.read_gamepad();

  if (ps2x.Analog(PSS_RY) == 127)analogWrite(RFpwm, 0);
  if (ps2x.Analog(PSS_RY) == 127)analogWrite(LFpwm, 0);
  if (ps2x.Analog(PSS_RY) == 127)analogWrite(RBpwm, 0);
  if (ps2x.Analog(PSS_RY) == 127)analogWrite(LBpwm, 0);
  if (ps2x.Analog(PSS_RX) == 128)analogWrite(RFpwm, 0);
  if (ps2x.Analog(PSS_RX) == 128)analogWrite(LFpwm, 0);
  if (ps2x.Analog(PSS_RX) == 128)analogWrite(RBpwm, 0);
  if (ps2x.Analog(PSS_RX) == 128)analogWrite(LBpwm, 0);

  if (ps2x.Analog(PSS_RY) < 127 && ps2x.Analog(PSS_LY)<255){
      fspeedRY = map(ps2x.Analog(PSS_RY), 0, 126, 255, 255); //向前馬力:0~255
      front();
  }
  if (ps2x.Analog(PSS_RY) > 127 && ps2x.Analog(PSS_LY)<255){
      fspeedRY = map(ps2x.Analog(PSS_RY), 128, 255, 255, 255);//向後馬力:0~255 
      back();
  }
  if (ps2x.Analog(PSS_RX) > 128 && ps2x.Analog(PSS_LY)<255){
      fspeedRX = map(ps2x.Analog(PSS_RX), 129, 255, 255, 255);//向右馬力:0~255 
      right();
  }
  if (ps2x.Analog(PSS_RX) < 128 && ps2x.Analog(PSS_LY)<255){
      fspeedRX = map(ps2x.Analog(PSS_RX), 0, 127, 255, 255); //向左馬力:0~255
      left();
  }
  delay(50);
}
void front(){
  //LFmotor反轉
  digitalWrite(LFmotor1, LOW);
  digitalWrite(LFmotor2, HIGH);
  analogWrite(LFpwm, fspeedRY);
  digitalWrite(LFmotor2, HIGH);
  //RFmotor正轉
  digitalWrite(RFmotor1, HIGH);
  digitalWrite(RFmotor2, LOW);
  analogWrite(RFpwm, fspeedRY);
  digitalWrite(RFmotor2, LOW);
  //LBmotor反轉
  digitalWrite(LBmotor1, LOW);
  digitalWrite(LBmotor2, HIGH);
  analogWrite(LBpwm, fspeedRY);
  digitalWrite(LBmotor2, HIGH);
  //RBmotor正轉
  digitalWrite(RBmotor1, HIGH);
  digitalWrite(RBmotor2, LOW);
  analogWrite(RBpwm, fspeedRY);
  digitalWrite(RBmotor2, LOW);
}
void back(){
   //LFmotor正轉
  digitalWrite(LFmotor1, HIGH);
  digitalWrite(LFmotor2, LOW);
  analogWrite(LFpwm, fspeedRY);
  digitalWrite(LFmotor2, LOW);
  //RFmotor反轉
  digitalWrite(RFmotor1, LOW);
  digitalWrite(RFmotor2, HIGH);
  analogWrite(RFpwm, fspeedRY);
  digitalWrite(RFmotor2, HIGH);
  //LBmotor正轉
  digitalWrite(LBmotor1, HIGH);
  digitalWrite(LBmotor2, LOW);
  analogWrite(LBpwm, fspeedRY);
  digitalWrite(LBmotor2, LOW);
  //RBmotor反轉
  digitalWrite(RBmotor1, LOW);
  digitalWrite(RBmotor2, HIGH);
  analogWrite(RBpwm, fspeedRY);
  digitalWrite(RBmotor2, HIGH);
}
void right(){
  //LFmotor反轉
  digitalWrite(LFmotor1, LOW);
  digitalWrite(LFmotor2, HIGH);
  analogWrite(LFpwm, fspeedRX);
  digitalWrite(LFmotor2, HIGH);
  //RFmotor反轉
  digitalWrite(RFmotor1, LOW);
  digitalWrite(RFmotor2, HIGH);
  analogWrite(RFpwm, fspeedRX);
  digitalWrite(RFmotor2, HIGH);
  //LBmotor正轉
  digitalWrite(LBmotor1, HIGH);
  digitalWrite(LBmotor2, LOW);
  analogWrite(LBpwm, fspeedRX);
  digitalWrite(LBmotor2, LOW);
  //RBmotor正轉
  digitalWrite(RBmotor1, HIGH);
  digitalWrite(RBmotor2, LOW);
  analogWrite(RBpwm, fspeedRX);
  digitalWrite(RBmotor2, LOW);
}
void left(){
  //LFmotor正轉
  digitalWrite(LFmotor1, HIGH);
  digitalWrite(LFmotor2, LOW);
  analogWrite(LFpwm, fspeedRX);
  digitalWrite(LFmotor2, LOW);
  //RFmotor正轉
  digitalWrite(RFmotor1, HIGH);
  digitalWrite(RFmotor2, LOW);
  analogWrite(RFpwm, fspeedRX);
  digitalWrite(RFmotor2, LOW);
  //LBmotor反轉
  digitalWrite(LBmotor1, LOW);
  digitalWrite(LBmotor2, HIGH);
  analogWrite(LBpwm, fspeedRX);
  digitalWrite(LBmotor2, HIGH);
  //RBmotor反轉
  digitalWrite(RBmotor1, LOW);
  digitalWrite(RBmotor2, HIGH);
  analogWrite(RBpwm, fspeedRX);
  digitalWrite(RBmotor2, HIGH);
}
