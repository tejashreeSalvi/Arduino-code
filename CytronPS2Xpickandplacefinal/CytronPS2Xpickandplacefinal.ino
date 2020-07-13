#include <SoftwareSerial.h>
#include <Cytron_G15Shield.h>
#include<PS2X_lib.h>
  
//check pins...
Cytron_G15Shield g15(2, 3, 8); // SoftwareSerial: Rx, Tx and Control pin
#define G15_1 1

//0,1,9
//PS2 pin
#define data 12
#define cmd 11
#define clk 13
#define attention 10

//Motor 1
#define m11 22 
#define m12 24
//Motor 2
#define m21 26
#define m22 28

//Gripper Motor...
#define mgripper1 6
#define mgripper2 7
int tempLY;
PS2X ps2x;

boolean pressure =  false;
boolean rumble  = false;

int error = 0 ;
int type = 0;
int vibrate = 0;

int LX,LY,RX,RY;
int tempLX;
void setup() {
  // put your setup code here, to run once:
    //G15_ Cube Servo Motor pinMode...
   g15.begin(19200);
   
  Serial.begin(57600);
   
  error = ps2x.config_gamepad(clk,cmd,attention,data,pressure,rumble);
  if(error == 0)
  {
    Serial.println("Found!!!");
  }
  else if(error == 1)
  {
    Serial.println("Not Found!!!");
  }
  else if(error == 2)
  {
    Serial.println("Found but no cmds...!!!!");
  }
  else if(error == 3)
  {
    Serial.println("Found but refuse for pressure Mode..!!!");
  }
   
  Serial.println(ps2x.Analog(1),HEX);
  
  type = ps2x.readType();
  switch(type)
  {
    case 0:
        Serial.println("Unknown Controller Type...!!!");
    break;
    case 1:
        Serial.println("DualShock Controller Found...!!!");
    break;
    case 2:
        Serial.println("Sony Controller Found....!!!");
    break;
  }

  //Motor 1
  pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  //Motor 2
  pinMode(m21,OUTPUT);
  pinMode(m22,OUTPUT);
  
  //Motor Gripper...
  pinMode(mgripper1,OUTPUT);
  pinMode(mgripper2,OUTPUT);

  //Servo
  // Make sure G15 in position mode
  g15.exitWheelMode(G15_1);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  ps2x.read_gamepad(false,vibrate);//read controller...
  LY = ps2x.Analog(PSS_LY);
  LX = ps2x.Analog(PSS_LX);
  tempLY=LY;
  tempLX = LX;
  RY = ps2x.Analog(PSS_RY);
  RX = ps2x.Analog(PSS_RX);
  Serial.println(ps2x.Button(PSB_PAD_LEFT));
  
  //Serial.println(LX);
  //Serial.println("LY");
  //Serial.println(LY);
  //Serial.println(RX);
  //Serial.println(RY);
  
  //Left Joystick... for Moving Gripper
  
  if(LX > 128){
      openGripper();     
  }
  /*else if(LX == 128){
      stopGripper();
  }*/
  else if(LX < 128){
      closeGripper();
  }
  else if(LY < 127){
      upArm();
  }
  else if(LY > 127){
      downArm();
  }
  else if(LY == 127){
      if(tempLY < 127){
        upArm();
      }
      else if(tempLY > 127){
        downArm();
      }
  }
  //Right Joystick... for Moving Motors 
  else if(RX < 128){
    left();
  }
  else if(RX > 128){
    right();
  }
  else if(RY < 127){
    forward();
  }
  else if(RY > 127){
    backward();
  }
  else if(LX == 128){
    stopGripper();
  }
  else{
   stopBot();
   //stopGripper();
  }

/*
  if(ps2x.Button(PSB_PAD_LEFT) == 1){
    left();
  }
  else if(ps2x.Button(PSB_PAD_RIGHT) == 1){
    right();
  }
  else if(ps2x.Button(PSB_PAD_UP) == 1){
    forward();
  }
  else if(ps2x.Button(PSB_PAD_DOWN) == 1){
    backward();
  }
  //Flip the gripper;
  else if(ps2x.Analog(PSS_LY) < 127){
        //Close the gripper...

        digitalWrite(mgripper1,HIGH);
        digitalWrite(mgripper2,LOW);
        
  }
  else if(ps2x.Analog(PSS_LY) > 127){
       //open the gripper...

       digitalWrite(mgripper1,LOW);
       digitalWrite(mgripper2,HIGH);
       
  }
  else if(ps2x.Analog(PSS_LY) == 127){
      //Stop the gripper...
      
      digitalWrite(mgripper1,LOW);
      digitalWrite(mgripper2,LOW);
      
  }
  else if(ps2x.Button(PSS_RX) < 128){
   
        upArm();   
  }
  else if(ps2x.Button(PSS_RX) > 128)
        downArm();
  }
  else{
    stopBot();
  }*/
}

void forward(){
    Serial.println("Forward...!!!");
    digitalWrite(m11,HIGH);
    digitalWrite(m12,LOW);
    digitalWrite(m21,HIGH);
    digitalWrite(m22,LOW);
}
void backward(){
    Serial.println("Backward...!!!");
    digitalWrite(m11,LOW);
    digitalWrite(m12,HIGH);
    digitalWrite(m21,LOW);
    digitalWrite(m22,HIGH);
}
void left(){
    Serial.println("Left...!!!");
    digitalWrite(m11,LOW);
    digitalWrite(m12,HIGH);
    digitalWrite(m21,HIGH);
    digitalWrite(m22,LOW);
}

void right(){
    Serial.println("Right...!!!");
    digitalWrite(m11,HIGH);
    digitalWrite(m12,LOW);
    digitalWrite(m21,LOW);
    digitalWrite(m22,HIGH);
}

void stopBot(){
    Serial.println("Stop Bot...!!!");
    digitalWrite(m11,LOW);
    digitalWrite(m12,LOW);
    digitalWrite(m21,LOW);
    digitalWrite(m22,LOW);
}

void openGripper(){

      //for gripper open...
      digitalWrite(mgripper1,HIGH);
      digitalWrite(mgripper2,LOW);
     
}
void stopGripper(){
  
      //Stop Gripper...
      digitalWrite(mgripper1,LOW);
      digitalWrite(mgripper2,LOW);

}
void closeGripper(){
      //for gripper close...
      digitalWrite(mgripper1,LOW);
      digitalWrite(mgripper2,HIGH);
}

void upArm(){    
  
  //for moving arm up...
  Serial.println("Hello1");
  g15.setLED(G15_1, ON);
  g15.setSpeed(G15_1, 200); // Set G15 (ID = 1) speed to 500, 
  g15.setPosAngle(G15_1, 90); // Set G15 (ID = 1) position to 0 deg
  delay(1000);
/*  g15.setLED(G15_1, OFF);
  g15.setSpeed(G15_1, 100);
  g15.setPosAngle(G15_1, 180); // Set G15 (ID = 1) position to 90 deg
  delay(1000);*/ 
}

void stopArm(){
  int angle;
  
  word error1 = 0; 
  byte data1[10];
  word position = 0;

  Serial.println("H");
  error1 = g15.getPos(G15_1, data1);
    
    Serial.println("I");
    digitalWrite(LED, LOW);
    position = data1[0];
    position = position | (word)(data1[1] << 8);
    Serial.print(position); // Print position
    angle = ConvertPosToAngle(position);
    
    Serial.println("Angle");
    Serial.println(angle);
    
  if(angle == 90){
    g15.setLED(G15_1, ON);
    g15.setSpeed(G15_1, 200); // Set G15 (ID = 1) speed to 500, 
    g15.setPosAngle(G15_1, 90); // Set G15 (ID = 1) position to 0 deg
    delay(100);  
  }
  else {
    g15.setLED(G15_1, ON);
    g15.setSpeed(G15_1, 200); // Set G15 (ID = 1) speed to 500, 
    g15.setPosAngle(G15_1, 180); // Set G15 (ID = 1) position to 0 deg
    delay(100);    
  }
  
}
void downArm(){

  Serial.println("Hello");
  //for moving arm down...
  g15.setLED(G15_1, ON);
  g15.setSpeed(G15_1, 200); // Set G15 (ID = 1) speed to 500, 
  g15.setPosAngle(G15_1, 180); // Set G15 (ID = 1) position to 0 deg
  delay(1000);
  /*g15.setLED(G15_1, OFF);
  g15.setSpeed(G15_1, 100);
  g15.setPosAngle(G15_1, 90); // Set G15 (ID = 1) position to 90 deg
  delay(1000);*/
}
