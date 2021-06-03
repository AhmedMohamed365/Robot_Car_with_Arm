  //
//for Blutooth controled Robotic Car

// defines pins numbers for ultraSonics
//const int trigPin1 = 9;
//const int echoPin1 = 10;
//
////2
//
//const int trigPin2 = 11;
//const int echoPin2 = 12;
//
////3
//
//const int trigPin3 = 2;
//const int echoPin3 = 3;
// defines variables for ultraSonic calc
long duration;
int distance;
//back motors

#include<SoftwareSerial.h>
#include<Servo.h>

SoftwareSerial bluetooth(11,12);

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

////////////////////////////////////
int lm3 = 6; //left motor output 1
int lm4 = 7; //left motor output 2
int rm3 = 9; //right motor output 1
int rm4 = 8; //right motor output 2

//front motor

int lm1 = 4; //left motor output 1
int lm2 = 5; //left motor output 2
int rm1 = 2; //right motor output 1
int rm2 = 3; //right motor output 2


char state = 0;
void setup()
{

  Serial.begin(9600);
  servo_1.attach(A5);
  servo_2.attach(A2);
  //servo_3.attach();
  servo_4.attach(A3);
  servo_5.attach(A4);
  servo_6.attach(2);
  servo_7.attach(3);

  servo_1.write(servo1);
  servo_2.write(servo2);
  servo_3.write(servo3);
  servo_4.write(servo4);
  servo_5.write(servo5);
  servo_6.write(servo6);
  servo_7.write(servo7);


  // for ultraSonics
  //  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  //pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  // front motors
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);

  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);

  //back motors
  pinMode(lm3, OUTPUT);
  pinMode(lm4, OUTPUT);

  pinMode(rm3, OUTPUT);
  pinMode(rm4, OUTPUT);

  Serial.begin(9600);
  bluetooth.begin(9600);

  sTOP();

servo_5.write(150);
// ArmGoUp();
//
//  delay(1000);
//  ArmGoDown();

 
}
void loop()
{

 
  if (bluetooth.available() > 0)
  {

    state = bluetooth.read();
    Serial.println(state);
    
    if (state == 'f')
    {
      ForWard();
    }
    if (state == 'b')
    {
      BackWard();
    }
    if (state == 'l')
    {
      Left();
    }
    if (state == 'r')
    {
      Right();
    }
    if (state == 's')
    {
      sTOP();
    }




    if (state == 'a') {


      servo_1.write(120);
      delay(200);
      servo_1.write(90);

    }

    if (state == 'x') {
      servo_1.write(70);
      delay(200);
      servo_1.write(90);

    }

    if (state == 'j') {
      if (servo2 > 0) {
        for (int i = servo2 ; i > servo2 - 5 ; i--)
        {
          servo_2.write(i);
          delay(5);
        }
        servo2 = servo2 - 5;
      }
    }

    if (state == 'd') {
      if (servo2 < 180) {
        for (int i = servo2 ; i < servo2 + 5 ; i++)
        {
          servo_2.write(i);
          delay(5);
        }
        servo2 = servo2 + 5;
      }
    }



    if (state == 'k') {


      servo_4.write(120);
      delay(200);
      servo_4.write(90);
    }

    if (state == 'm') {
      servo_4.write(60);
      delay(200);
      servo_4.write(90);
    }

    if (state == 'n') {
      if (servo5 > 0) {
        for (int i = servo5 ; i > servo5 - 10 ; i--)
        {
          servo_5.write(i);
          delay(5);
        }
        servo5 = servo5 - 10;
      }
    }

    if (state == 'o') {
      if (servo5 < 180) {
        for (int i = servo5 ; i < servo5 + 10 ; i++)
        {
          servo_5.write(i);
          delay(5);
        }
        servo5 = servo5 + 10;
      }
    }

    if (state == 'i') {
      if (servo6 > 0) {
        for (int i = servo6 ; i > servo6 - 10 ; i--)
        {
          servo_6.write(i);
          delay(5);
        }
        servo6 = servo6 - 10;
      }
    }

    if (state == 'h') {
      if (servo6 < 180) {
        for (int i = servo6 ; i < servo6 + 10 ; i++)
        {
          servo_6.write(i);
          delay(5);
        }
        servo6 = servo6 + 10;
      }
    }

    if (state == 'z') {
      if (servo7 > 0) {
        for (int i = servo7 ; i > servo7 - 10 ; i--)
        {
          servo_7.write(i);
          delay(5);
        }
        servo7 = servo7 - 10;
      }
    }

    if (state == 'g') {
      if (servo7 < 180) {
        for (int i = servo7 ; i < servo7 + 10 ; i++)
        {
          servo_7.write(i);
          delay(5);
        }
        servo7 = servo7 + 10;
      }
    }


    
  }
}
void ForWard()
{

  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);

  digitalWrite(lm3, LOW);
  digitalWrite(lm4, HIGH);
  digitalWrite(rm3, LOW);
  digitalWrite(rm4, HIGH);
}
void BackWard()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);

  digitalWrite(lm3, HIGH);
  digitalWrite(lm4, LOW);
  Serial.print("I'm back");
  digitalWrite(rm3, HIGH);
  digitalWrite(rm4, LOW);
}
void Left()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);

  digitalWrite(lm3, LOW);
  digitalWrite(lm4, HIGH);
  digitalWrite(rm3, HIGH);
  digitalWrite(rm4, LOW);
}
void Right()
{
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);

  digitalWrite(lm3, HIGH);
  digitalWrite(lm4, LOW);
  digitalWrite(rm3, LOW);
  digitalWrite(rm4, HIGH);
}
void sTOP()
{
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);

  digitalWrite(lm3, LOW);
  digitalWrite(lm4, LOW);
  digitalWrite(rm3, LOW);
  digitalWrite(rm4, LOW);
}


void ArmGoDown()
{
//  // A2   , A3  , A4  will rotate right to descende the arm

  //A2
  for (int i = servo2 ; i > servo2 - 10 ; i--)
        {
          servo_2.write(i);
          delay(500);
        }
        servo2 = servo2 - 10;
delay(500);

//A3
 for (int i = servo4 ; i > servo4 - 10 ; i--)
        {
          servo_4.write(i+50);
          delay(500);
        }
        servo4 = servo4 + 10;


        delay(500);
 for (int i = servo4 ; i > servo4  +10 ; i++)
        {
          servo_4.write(i);
          delay(500);
        }
        servo4 = servo4 + 50;


//A4

 
      


      
}




void ArmGoUp()
{
// A2  , A3 , A4 will rotate left to lift the arm

  //A2
  for (int i = servo2 ; i > servo2 + 10 ; i++)
        {
          servo_2.write(i);
          delay(5);
        }
        servo2 = servo2 + 50;


//A3
 for (int i = servo4 ; i > servo4  +10 ; i++)
        {
          servo_4.write(i);
          delay(5);
        }
        servo4 = servo4 + 50;



//A4
//servo_5.write(90);
 
  
}
//int [] calc_distance()
//{
//  int distances [3] = {0};
//  // Clears the trigPin
//  digitalWrite(trigPin1, LOW);
//  digitalWrite(trigPin2, LOW);
//
//  digitalWrite(trigPin3, LOW);
//
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin1, HIGH);
//  digitalWrite(trigPin2, HIGH);
//
//  digitalWrite(trigPin3, HIGH);
//
//  delayMicroseconds(10);
//  digitalWrite(trigPin1, LOW);
//  digitalWrite(trigPin2, LOW);
//  digitalWrite(trigPin3, LOW);
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//
//  for (int i = 0; i < 3; i++)
//  {
//    duration = pulseIn(echoPin, HIGH);
//    distances[i] =  duration * 0.034 / 2;
//    echoPin++;
//  }
//  // Calculating the distance
//
//  // Prints the distance on the Serial Monitor
//  Serial.print("Distance: ");
//  Serial.println(distance);
//
//  return distances;
//
//
//}
