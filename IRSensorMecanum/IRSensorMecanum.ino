//IR Sensor
const int d1 = 8;
const int d2 = 9;
const int d3 = 10;
const int d4 = 11;
const int d5 = 12;
String irValue;
//motor 1
#define DIR1 2
#define pwm1 3
//motor 2
#define DIR2 4
#define pwm2 5

#define p 60

#define pwm 70

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
  
  pinMode(d1,INPUT);
  pinMode(d2,INPUT);
  pinMode(d3,INPUT);
  pinMode(d4,INPUT);
  pinMode(d5,INPUT);

  
  //Power motor 1
  pinMode(pwm1,OUTPUT);
  pinMode(DIR1,OUTPUT);
   
  //Power motor 2
  pinMode(pwm2,OUTPUT);
  pinMode(DIR2,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

   int v1 = digitalRead(d1);
   int v2 = digitalRead(d2);
   int v3 = digitalRead(d3);
   int v4 = digitalRead(d4);
   int v5 = digitalRead(d5);

 irValue = (String)v1 + (String)v2 + (String)v3 + (String)v4 + (String)v5;
   Serial.println(irValue);  
  
   if((irValue.equals("00010"))||(irValue.equals("01000")))
   {
          //forward
          Serial.println("Forward...!!!");
  
          //motor 1 and motor 4
          analogWrite(pwm1,p);
          digitalWrite(DIR1,LOW);

          //motor 2 and motor 3
          analogWrite(pwm2,pwm);
          digitalWrite(DIR2,LOW);
   }
   else if((irValue.equals("10000")) || (irValue.equals("11000")))
   {
          //Right
          Serial.println("Right...!!!");
          
         //motor 1 and 4
         analogWrite(pwm1,p);
         digitalWrite(DIR1,HIGH);
  
        //motor 2 and 3
        analogWrite(pwm2,pwm);
        digitalWrite(DIR2,LOW);
    }   
   else if((irValue.equals("00001")) || ((irValue.equals("00011"))))
   {
        //Left
        Serial.println("Left...!!!");
        //motor 1 and 4
        analogWrite(pwm1,p);
        digitalWrite(DIR1,LOW);
  
        //motor 2 and 3
        analogWrite(pwm2,pwm);
        digitalWrite(DIR2,HIGH);
 
   }   
   else
   {
      //Stop...!!!
        
        analogWrite(pwm1,0); 
        analogWrite(pwm2,0);
   }
}
