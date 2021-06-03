#include<Servo.h>

Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5;
Servo servo_6;
Servo servo_7;

int servo1 = 90;
int servo2 = 0;
int servo3 = 90;
int servo4 = 90;
int servo5 = 90;
int servo6 = 90;
int servo7 = 90;





void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
servo_1.attach(3);
servo_2.attach(4);
//servo_3.attach(10);
servo_4.attach(5);
servo_5.attach(6);
servo_6.attach(7);
servo_7.attach(8);

servo_1.write(servo1); 
servo_2.write(servo2); 
servo_3.write(servo3); 
servo_4.write(servo4); 
servo_5.write(servo5); 
servo_6.write(servo6); 
servo_7.write(servo7);

}

void loop() {
char state = "0";
if(Serial.available() > 0){     
  state = Serial.read();   
  Serial.println(state);
} 
if (state == 'a'){ 


  servo_1.write(120);
  delay(500);
  servo_1.write(90);
      
}

if (state == 'x'){
  servo_1.write(70);
  delay(500);
  servo_1.write(90);
       
}

if (state == 'j'){
    if(servo2>0){
     for(int i = servo2 ; i > servo2-10 ; i--)
      {
          servo_2.write(i);
          delay(5);
      }
      servo2 = servo2-10;
     } 
}

if (state == 'd'){
  if(servo2<180){
      for(int i = servo2 ; i < servo2+10 ; i++)
      {
          servo_2.write(i);
          delay(5);
      }
      servo2 = servo2+10;
     }  
}



if(state == 'k'){


 servo_4.write(120);
  delay(200);
  servo_4.write(90);
}

if (state == 'm'){
   servo_4.write(60);
  delay(200);
  servo_4.write(90);
}

if(state == 'n'){
   if(servo5>0){
     for(int i = servo5 ; i > servo5-10 ; i--)
      {
          servo_5.write(i);
          delay(5);
      }
      servo5 = servo5-10;
     } 
}

if (state == 'o'){
  if(servo5<180){
    for(int i = servo5 ; i < servo5+10 ; i++)
      {
          servo_5.write(i);
          delay(5);
      }
      servo5 = servo5+10;
     }
}

if(state == 'i'){
   if(servo6>0){
     for(int i = servo6 ; i > servo6-10 ; i--)
      {
          servo_6.write(i);
          delay(5);
      }
      servo6 = servo6-10;
     } 
}

if (state == 'h'){
  if(servo6<180){
    for(int i = servo6 ; i < servo6+10 ; i++)
      {
          servo_6.write(i);
          delay(5);
      }
      servo6 = servo6+10;
     }
}

if(state == 'z'){
   if(servo7>0){
     for(int i = servo7 ; i > servo7-10 ; i--)
      {
          servo_7.write(i);
          delay(5);
      }
      servo7 = servo7-10;
     } 
}

if (state == 'g'){
  if(servo7<180){
    for(int i = servo7 ; i < servo7+10 ; i++)
      {
          servo_7.write(i);
          delay(5);
      }
      servo7 = servo7+10;
     }
}

}
