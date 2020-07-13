#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>

//Board 1
//Left front wheel
#define DIR1 25
#define pwm1 3

//Left Back wheel
#define DIR3 22
#define pwm3 4

//Board 2
//Right front wheel
#define DIR2 24
#define pwm2 2

//Right back wheel
#define DIR4 23
#define pwm4 5

#define p1 70
#define p2 70
#define p3 70
#define p4 70

Cytron_PS2Shield ps2(10, 11); // SoftwareSerial: Rx and Tx pin
//Cytron_PS2Shield ps2; // HardwareSerial, note: 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
  
  //Board 1
  pinMode(pwm1,OUTPUT);
  pinMode(DIR1,OUTPUT);

  pinMode(pwm2,OUTPUT);
  pinMode(DIR2,OUTPUT);

  //Board 2
  pinMode(pwm3,OUTPUT);
  pinMode(DIR3,OUTPUT);

  pinMode(pwm4,OUTPUT);
  pinMode(DIR4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(ps2.readButton(PS2_UP) == 0)
  {
    //Serial.println("Hello");
    Serial.println(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS));
    forward();
  } 
  if(ps2.readButton(PS2_DOWN) == 0)
  {
    //Serial.println("Hello");
    Serial.println(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS));
    backward();
  }
  if(ps2.readButton(PS2_LEFT) == 0){
    left();
  }
  if(ps2.readButton(PS2_RIGHT) == 0){
    right();
  }
  if(ps2.readButton(PS2_LEFT_1) == 0){
    turnLeft();
  }
  if(ps2.readButton(PS2_RIGHT_1) == 0){
    turnRight();
  }
  if(ps2.readButton(PS2_LEFT_2) == 0){
    leftdiagional();
  }
  if(ps2.readButton(PS2_RIGHT_2) == 0){
    rightdiagional();
  }
  else
  {
    stopBot();
  }  
}

void forward()
{
  Serial.println("Forward");
  analogWrite(pwm1,p1);
  digitalWrite(DIR1,HIGH);

  //motor 2 and motor 3
  analogWrite(pwm2,p2);
  digitalWrite(DIR2,HIGH);

  analogWrite(pwm3,p3);
  digitalWrite(DIR3,HIGH);

  //motor 2 and motor 3
  analogWrite(pwm4,p4);
  digitalWrite(DIR4,HIGH);
}
void backward()
{
  
  Serial.println("Backward");
  //motor 1 
  analogWrite(pwm1,p1);
  digitalWrite(DIR1,LOW);

  //motor 2  
  analogWrite(pwm2,p2);
  digitalWrite(DIR2,LOW);

  //motor 3
  analogWrite(pwm3,p3);
  digitalWrite(DIR3,LOW);

  //motor 4 
  analogWrite(pwm4,p4);
  digitalWrite(DIR4,LOW);
}
void left()
{
  
  Serial.println("Left");
  //motor 1 
  analogWrite(pwm1,p1);
  digitalWrite(DIR1,LOW);
  
  //motor 2 
  analogWrite(pwm2,p2);
  digitalWrite(DIR2,HIGH);

  
  //motor 3
  analogWrite(pwm3,p3);
  digitalWrite(DIR3,HIGH);
  
  //motor 4
  analogWrite(pwm4,p4);
  digitalWrite(DIR4,LOW);
}
void right()
{  
  
  Serial.println("Right");
  //motor 1
  analogWrite(pwm1,p1);
  digitalWrite(DIR1,HIGH);
  
  //motor 2
  analogWrite(pwm2,p2);
  digitalWrite(DIR2,LOW);
 
  //motor 3
  analogWrite(pwm3,p3);
  digitalWrite(DIR3,LOW);
  
  //motor 4
  analogWrite(pwm4,p4);
  digitalWrite(DIR4,HIGH);
}

void turnRight(){

  Serial.println("turnLeft");
  //motor 1
  analogWrite(pwm1,p1);
  digitalWrite(DIR1,HIGH);
  
  //motor 2
  analogWrite(pwm2,p2);
  digitalWrite(DIR2,LOW);
 
  //motor 3
  analogWrite(pwm3,p3);
  digitalWrite(DIR3,HIGH);
  
  //motor 4
  analogWrite(pwm4,p4);
  digitalWrite(DIR4,LOW);
  
}

void turnLeft(){

  Serial.println("turnRight");
  //motor 1
  analogWrite(pwm1,p1);
  digitalWrite(DIR1,LOW);
  
  //motor 2
  analogWrite(pwm2,p2);
  digitalWrite(DIR2,HIGH);
 
  //motor 3
  analogWrite(pwm3,p3);
  digitalWrite(DIR3,LOW);
  
  //motor 4
  analogWrite(pwm4,p4);
  digitalWrite(DIR4,HIGH);
  
}

void rightdiagional(){

    Serial.println("LeftDiagional");
  //motor 1
  //left front
  analogWrite(pwm1,p1);
  digitalWrite(DIR1,HIGH);
  
  //motor 2
  //left back
  analogWrite(pwm2,0);
  
  //motor 3
  //right back
  analogWrite(pwm4,p4);
  digitalWrite(DIR4,HIGH);
  
  //motor 4
  //right front
  analogWrite(pwm3,0);
}

void leftdiagional(){
    Serial.println("RightDiagional");
  //motor 1
  analogWrite(pwm1,0);
  
  //motor 2
  analogWrite(pwm2,p2);
  digitalWrite(DIR2,HIGH);
  
  //motor 3
  analogWrite(pwm3,p3);
  digitalWrite(DIR3,HIGH);
  
  //motor 4
  analogWrite(pwm4,0);
}

void leftBackdiagional(){

 
}

void rightBackdiagional(){
  
}

void stopBot()
{
  Serial.println("Stop");
   analogWrite(pwm1,0); 
   analogWrite(pwm2,0); 
   analogWrite(pwm3,0); 
   analogWrite(pwm4,0);  
}
