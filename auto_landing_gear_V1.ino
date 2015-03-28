/*
project automatic retractable landing gear  
by: tinnakon kheowree  
tinnakon_za@hotmail.com
tinnakonza@gmail.com
http://quad3d-tin.lnwshop.com/
https://www.facebook.com/tinnakonza
*/
#include <Arduino.h>
#include <Servo.h> 
#include "Ultrasonic.h"

Servo servo1;
static const int minAngle = 0;
static const int maxAngle = 176;
int servoAngle;
int servoPos;
int servoPin = 10;

#define LEDPin 13
long duration;
long HR_dist=0;
int HR_angle=0;
int HR_dir=1;
int minimumRange=5;
int maximumRange=200;

// Main loop variables
unsigned long previousTime = 0;
long Dt_roop = 20000;
float G_Dt = 0.01; 

void setup() {
 
 Serial.begin (9600);
 servo1.attach(servoPin);
 pinMode(LEDPin, OUTPUT);
 UltrasonicInt();
 previousTime = micros();
}
void loop() {
   Dt_roop = micros() - previousTime;// 50 Hz task loop (10 ms) 
   if(Dt_roop <= 0)
   {
    Dt_roop = 20001; 
   }   
    if (Dt_roop >= 20000) //// 50 Hz task loop
    {
      previousTime = micros();
      G_Dt = Dt_roop*0.000001;
      UltrasonicRead();
      ///////////////////
      if(Altitude_sonaf > 0.5){
        HR_angle = 180;
      }
      else{
        HR_angle = 0;
      }
      ///////////////////
      servoPos = constrain(map(HR_angle, 0,180,minAngle,maxAngle),minAngle,maxAngle);
      servo1.write(servoPos);
      
      //Serial.print(Altitude_sonaf);Serial.print("\t");
      //Serial.print(servoPos);Serial.print("\t");
      //Serial.print("\n"); 
    }
}
