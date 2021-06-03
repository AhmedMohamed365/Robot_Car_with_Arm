// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 9; 
// Create a servo object 
char i = 'a';
Servo Servo1; 
void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
   Serial.begin(9600);
}
void loop(){ 

  if(Serial.available()>0)
  {
    if(i == 'a' )
   Servo1.write(0);

     else if( i == 'b' )
     Servo1.write(90);

     else if ( i == 'c')
       Servo1.write(180); 
  }
                    
};
