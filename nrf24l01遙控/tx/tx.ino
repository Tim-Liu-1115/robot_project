#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8, 9); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);              // 監控視窗指令
  Serial.println("w. FORWARD");
  Serial.println("s. REVERSE");
  Serial.println("d. Right");
  Serial.println("a. Left");
  Serial.println("q. Lrotate");
  Serial.println("e. Rrotate");
  Serial.println();
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}
void loop() {
  char user_input;     
  while(Serial.available())
  {
    user_input = Serial.read(); //Read user input and trigger appropriate function

     
    if (user_input =='w')
    {
      const char text[] = "Forward"; 
      radio.write(&text, sizeof(text));
    }
    else if (user_input =='s')
    {
      const char text[] = "Reverse"; 
      radio.write(&text, sizeof(text));
    }
    else if (user_input =='d')
    {
      const char text[] = "Right"; 
      radio.write(&text, sizeof(text));
    }
    else if (user_input =='a')
    {
      const char text[] = "Left"; 
      radio.write(&text, sizeof(text));
    }
    else if (user_input =='q')
    {
      const char text[] = "Lrotate"; 
      radio.write(&text, sizeof(text));
    }
    else if (user_input =='e')
    {
      const char text[] = "Rrotate"; 
      radio.write(&text, sizeof(text));
    }
     /*else if (user_input =='f')
    {
      const char text[] = "MODE_1"; 
      radio.write(&text, sizeof(text));
    }
     else if (user_input =='g')
    {
      const char text[] = "MODE_2"; 
      radio.write(&text, sizeof(text));
    }*/
    else if (user_input =='j')
    {
      const char text[] = "IncreaseSpeed"; 
      radio.write(&text, sizeof(text));
    }
    else if (user_input =='k')
    {
      const char text[] = "DecreaseSpeed"; 
      radio.write(&text, sizeof(text));
    }
    else
    {
      const char text[] = "Stop"; 
      radio.write(&text, sizeof(text));
    }
  }
}
