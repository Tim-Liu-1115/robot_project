#define BRAKE    0
#define forword  2
#define reverse  3
#define right    4
#define left     5
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").
int MODE;

//MOTOR LF
#define MOTOR_LF_A1_PIN 24
#define MOTOR_LF_B1_PIN 25
#define PWM_MOTOR_LF 3
#define EN_LF_PIN A2
#define CURRENT_LF_SEN A3  //電流檢測
short usSpeed_LF = 65;

//MOTOR RF
#define MOTOR_RF_A1_PIN 22
#define MOTOR_RF_B1_PIN 23
#define PWM_MOTOR_RF 2
#define EN_RF_PIN A0
#define CURRENT_RF_SEN A1
short usSpeed_RF = 40;

//MOTOR LR
#define MOTOR_LR_A1_PIN 26
#define MOTOR_LR_B1_PIN 27
#define PWM_MOTOR_LR 4
#define EN_LR_PIN A4
#define CURRENT_LR_SEN A5
short usSpeed_LR = 50;

//MOTOR RR
#define MOTOR_RR_A1_PIN 28
#define MOTOR_RR_B1_PIN 29
#define PWM_MOTOR_RR 5
#define EN_RR_PIN A6
#define CURRENT_RR_SEN A7
short usSpeed_RR = 52;

unsigned short usMotor_Status = BRAKE;
 
void setup()                         
{
  pinMode(MOTOR_LF_A1_PIN, OUTPUT),pinMode(MOTOR_LF_B1_PIN, OUTPUT),pinMode(PWM_MOTOR_LF, OUTPUT),pinMode(EN_LF_PIN, OUTPUT),pinMode(CURRENT_LF_SEN, OUTPUT);
  pinMode(MOTOR_RF_A1_PIN, OUTPUT),pinMode(MOTOR_LF_B1_PIN, OUTPUT),pinMode(PWM_MOTOR_RF, OUTPUT),pinMode(EN_RF_PIN, OUTPUT),pinMode(CURRENT_RF_SEN, OUTPUT);
  pinMode(MOTOR_LR_A1_PIN, OUTPUT),pinMode(MOTOR_LR_B1_PIN, OUTPUT),pinMode(PWM_MOTOR_LR, OUTPUT),pinMode(EN_LR_PIN, OUTPUT),pinMode(CURRENT_LR_SEN, OUTPUT);
  pinMode(MOTOR_RR_A1_PIN, OUTPUT),pinMode(MOTOR_RR_B1_PIN, OUTPUT),pinMode(PWM_MOTOR_RR, OUTPUT),pinMode(EN_RR_PIN, OUTPUT),pinMode(CURRENT_RR_SEN, OUTPUT);


  Serial.begin(9600);              // 監控視窗指令
  Serial.println("Begin motor control");
  Serial.println(); //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("l. STOP");
  Serial.println("w. FORWARD");
  Serial.println("s. REVERSE");
  Serial.println("d. Right");
  Serial.println("a. Left");
  Serial.println("j. INCREASE SPEED");
  Serial.println("k. DECREASE SPEED");
  Serial.println();

}

void loop() 
{
  char user_input;   

  
  
  while(Serial.available())
  {
    user_input = Serial.read();
    digitalWrite(EN_LF_PIN, HIGH),digitalWrite(EN_RF_PIN, HIGH),digitalWrite(EN_LR_PIN, HIGH),digitalWrite(EN_RR_PIN, HIGH);

    if(user_input =='w')
    {
      Forward();
    }
    else if(user_input =='s')
    {
      Reverse();
    }
    else if(user_input =='d')
    {
      Right();
    }
    else if(user_input =='a')
    {
      Left();
    }
    else if(user_input =='j')
    {
      IncreaseSpeed();
    }
    else if(user_input =='k')
    {
      DecreaseSpeed();
    }
    else if(user_input =='f')
    {
       MODE = 0;
       Serial.println("正向");
    }
    else if(user_input =='g')
    {
       MODE = 1;
       Serial.println("斜向");
    }
    else
    {
      Stop();
    }
      
  }
}

void Stop()
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MODE, usMotor_Status, 0,0,0,0);
}

void Forward()
{
  Serial.println("Forward");
  usMotor_Status = forword;
  motorGo(MODE, usMotor_Status, usSpeed_LF, usSpeed_RF, usSpeed_LR, usSpeed_RR);
}

void Reverse()
{
  Serial.println("Reverse");
  usMotor_Status = reverse;
  motorGo(MODE, usMotor_Status, usSpeed_LF, usSpeed_RF, usSpeed_LR, usSpeed_RR);
}

void Right()
{
  Serial.println("Right");
  usMotor_Status = right;
  motorGo(MODE, usMotor_Status, usSpeed_LF, usSpeed_RF, usSpeed_LR, usSpeed_RR);
}

void Left()
{
  Serial.println("Left");
  usMotor_Status = left;
  motorGo(MODE, usMotor_Status, usSpeed_LF, usSpeed_RF, usSpeed_LR, usSpeed_RR);
}

void IncreaseSpeed()
{
  usSpeed_LF = usSpeed_LF + 10;
  usSpeed_RF = usSpeed_RF + 10;
  usSpeed_LR = usSpeed_LR + 10;
  usSpeed_RR = usSpeed_RR + 10;
  
  if(usSpeed_LF > 255)
    usSpeed_LF = 255;
  if(usSpeed_RF > 230)
    usSpeed_RF = 230;
  if(usSpeed_LR > 240)
    usSpeed_LR = 255;
  if(usSpeed_RR > 242)
    usSpeed_RR = 255;  
  
  Serial.print("Speed +: ");
  Serial.print(usSpeed_LF);
  Serial.print("\t");
  Serial.print(usSpeed_RF);
  Serial.print("\t");
  Serial.print(usSpeed_LR);
  Serial.print("\t");
  Serial.println(usSpeed_RR);

  motorGo(MODE, usMotor_Status, usSpeed_LF, usSpeed_RF, usSpeed_LR, usSpeed_RR);
}

void DecreaseSpeed()
{
  usSpeed_LF = usSpeed_LF - 10;
  usSpeed_RF = usSpeed_RF - 10;
  usSpeed_LR = usSpeed_LR - 10;
  usSpeed_RR = usSpeed_RR - 10;
  
  if(usSpeed_LF < 0)
    usSpeed_LF = 0;
  if(usSpeed_RF < 0)
    usSpeed_RF = 0;
  if(usSpeed_LR < 0)
    usSpeed_LR = 0;
  if(usSpeed_RR < 0)
    usSpeed_RR = 0;  
  
  Serial.print("Speed -: ");
  
  Serial.print(usSpeed_LF);
  Serial.print("\t");
  Serial.print(usSpeed_RF);
  Serial.print("\t");
  Serial.print(usSpeed_LR);
  Serial.print("\t");
  Serial.println(usSpeed_RR);
  

  motorGo(MODE, usMotor_Status, usSpeed_LF, usSpeed_RF, usSpeed_LR, usSpeed_RR);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm_LF, uint8_t pwm_RF, uint8_t pwm_LR, uint8_t pwm_RR)
{
  if(motor == 0)
  {
    if(direct == forword)
    {
      digitalWrite(MOTOR_LF_A1_PIN, LOW); 
      digitalWrite(MOTOR_LF_B1_PIN, HIGH);
      
      digitalWrite(MOTOR_RF_A1_PIN, HIGH); 
      digitalWrite(MOTOR_RF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_LR_A1_PIN, LOW); 
      digitalWrite(MOTOR_LR_B1_PIN, HIGH);
      
      digitalWrite(MOTOR_RR_A1_PIN, HIGH); 
      digitalWrite(MOTOR_RR_B1_PIN, LOW); 
    }                 
    
    else if(direct == reverse)
    {
      digitalWrite(MOTOR_LF_A1_PIN, HIGH); 
      digitalWrite(MOTOR_LF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_RF_A1_PIN, LOW); 
      digitalWrite(MOTOR_RF_B1_PIN, HIGH);
      
      digitalWrite(MOTOR_LR_A1_PIN, HIGH); 
      digitalWrite(MOTOR_LR_B1_PIN, LOW);
      
      digitalWrite(MOTOR_RR_A1_PIN, LOW); 
      digitalWrite(MOTOR_RR_B1_PIN, HIGH);                  
    }

    else if(direct == right)
    {
      digitalWrite(MOTOR_LF_A1_PIN, LOW); 
      digitalWrite(MOTOR_LF_B1_PIN, HIGH);
      
      digitalWrite(MOTOR_RF_A1_PIN, LOW); 
      digitalWrite(MOTOR_RF_B1_PIN, HIGH);
      
      digitalWrite(MOTOR_LR_A1_PIN, HIGH); 
      digitalWrite(MOTOR_LR_B1_PIN, LOW);
      
      digitalWrite(MOTOR_RR_A1_PIN, HIGH); 
      digitalWrite(MOTOR_RR_B1_PIN, LOW);                   
    }

    else if(direct == left)
    {
      digitalWrite(MOTOR_LF_A1_PIN, HIGH); 
      digitalWrite(MOTOR_LF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_RF_A1_PIN, HIGH); 
      digitalWrite(MOTOR_RF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_LR_A1_PIN, LOW); 
      digitalWrite(MOTOR_LR_B1_PIN, HIGH);
      
      digitalWrite(MOTOR_RR_A1_PIN, LOW); 
      digitalWrite(MOTOR_RR_B1_PIN, HIGH);                 
    }
    
   else
    {
      digitalWrite(MOTOR_LF_A1_PIN, LOW); 
      digitalWrite(MOTOR_LF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_RF_A1_PIN, LOW); 
      digitalWrite(MOTOR_RF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_LR_A1_PIN, LOW); 
      digitalWrite(MOTOR_LR_B1_PIN, LOW);
      
      digitalWrite(MOTOR_RR_A1_PIN, LOW); 
      digitalWrite(MOTOR_RR_B1_PIN, LOW);            
    }
   }

   if(motor == 1)
  {
    if(direct == forword)
    {      
      digitalWrite(MOTOR_RF_A1_PIN, HIGH); 
      digitalWrite(MOTOR_RF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_LR_A1_PIN, LOW); 
      digitalWrite(MOTOR_LR_B1_PIN, HIGH);
    }                 
    
    else if(direct == reverse)
    {  
      digitalWrite(MOTOR_RF_A1_PIN, LOW); 
      digitalWrite(MOTOR_RF_B1_PIN, HIGH);
      
      digitalWrite(MOTOR_LR_A1_PIN, HIGH); 
      digitalWrite(MOTOR_LR_B1_PIN, LOW);                
    }

    else if(direct == right)
    {
      digitalWrite(MOTOR_LF_A1_PIN, LOW); 
      digitalWrite(MOTOR_LF_B1_PIN, HIGH);

      digitalWrite(MOTOR_RR_A1_PIN, HIGH); 
      digitalWrite(MOTOR_RR_B1_PIN, LOW);                   
    }

    else if(direct == left)
    {
      digitalWrite(MOTOR_LF_A1_PIN, HIGH); 
      digitalWrite(MOTOR_LF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_RR_A1_PIN, LOW); 
      digitalWrite(MOTOR_RR_B1_PIN, HIGH);                 
    }
    
   else
    {
      digitalWrite(MOTOR_LF_A1_PIN, LOW); 
      digitalWrite(MOTOR_LF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_RF_A1_PIN, LOW); 
      digitalWrite(MOTOR_RF_B1_PIN, LOW);
      
      digitalWrite(MOTOR_LR_A1_PIN, LOW); 
      digitalWrite(MOTOR_LR_B1_PIN, LOW);
      
      digitalWrite(MOTOR_RR_A1_PIN, LOW); 
      digitalWrite(MOTOR_RR_B1_PIN, LOW);            
    }
   }
    
    analogWrite(PWM_MOTOR_LF, pwm_LF);
    analogWrite(PWM_MOTOR_RF, pwm_RF);
    analogWrite(PWM_MOTOR_LR, pwm_LR);
    analogWrite(PWM_MOTOR_RR, pwm_RR); 
  
}
