
#include <NewPing.h>

#include <SoftwareSerial.h>
//sensor pins
#define trig_pin A4 //analog input 1
#define echo_pin A3 //analog input 2

#define LeftMotorForward 9
#define LeftMotorBackward 8

#define RightMotorForward 7
#define RightMotorBackward 6

#define MotorA_PWM 10
#define MotorB_PWM 5

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;
SoftwareSerial mySerial(2,3);
NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function

char getstr;
void setup()
{ 
  
  
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(MotorA_PWM, OUTPUT);
  pinMode(MotorB_PWM, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
    digitalWrite(MotorA_PWM,HIGH);    //ENB Pin set for HIGH.
  digitalWrite(MotorB_PWM,HIGH);    //ENB Pin set for HIGH.

  distance = readPing();
  delay(100);
    Serial.begin(9600); //open the serial port
  mySerial.begin(9600); // open the bluetooth serial port
}
void _mForward()
{ 
  
  digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  Serial.println("go forward!");
}
void _mBack()
{
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  Serial.println("go back!");
}
void _mleft()
{
  
  digitalWrite(LeftMotorBackward, LOW); // did change to move only ryt motor forward
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  Serial.println("go left!");
}
void _mright()
{
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW); // did change to move only left motor forward
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  
}
void _mStop()
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  Serial.println("Stop!");
}


void loop()
  { 
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    _mStop();
    delay(300);
    _mBack();
    delay(400);
    _mStop();
    delay(300);
  }

   else{ 
  getstr=mySerial.read();
  Serial.println(getstr);
 if(getstr=='1')
  {
    _mForward();
  }
  else if(getstr=='2')
  {
    _mBack();
    delay(200);
  }
  else if(getstr=='3')// according to my robot. otherwise L
  {
    _mleft();
    delay(200);
  }
  else if(getstr=='4') // according to my robot. otherwise R
  {
    _mright();
    delay(200);
  }
  else if(getstr=='5')
  {
     _mStop();     
  }
   }
   distance = readPing();
}
int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}
