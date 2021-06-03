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


// defines pins numbers
const int trigPin2 = 4;
const int echoPin2 = 5;

const int trigPin3 = 6;
const int echoPin3 = 7;


const int trigPin = 2;
const int echoPin = 3;
// defines variables
float duration;
float distance[3] = {0};
char prevDir[3] = {};








//back motors
int lm3=4; //left motor output 1
int lm4=5; //left motor output 2
int rm3=6;  //right motor output 1
int rm4=7;  //right motor output 2

//front motors
int lm1=8; //left motor output 1
int lm2=9; //left motor output 2
int rm1=10;  //right motor output 1
int rm2=11;  //right motor output 2


char d=0;
void setup()
{

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input

  // front motors
pinMode(lm1,OUTPUT);
pinMode(lm2,OUTPUT);

pinMode(rm1,OUTPUT);
pinMode(rm2,OUTPUT);

//back motors
pinMode(lm3,OUTPUT);
pinMode(lm4,OUTPUT);

pinMode(rm3,OUTPUT);
pinMode(rm4,OUTPUT);

Serial.begin(9600);

sTOP();

}
void loop()
{
      if(Serial.available()>0)
      {


   
  
      d=Serial.read();
      if(d=='F')
      {
      ForWard();
      }
      if(d=='B')
      {
      BackWard();
      }
      if(d=='L')
      {
      Left();
      }
      if(d=='R')
      {
      Right();
      }
      if(d=='S')
      {
      sTOP();
      }


      //calcDistances();
  calcSeq();
  sendData();
      
      }
}
void ForWard()
{

digitalWrite(lm1,HIGH);
digitalWrite(lm2,LOW);
digitalWrite(rm1,HIGH);
digitalWrite(rm2,LOW);

digitalWrite(lm3,HIGH);
digitalWrite(lm4,LOW);
digitalWrite(rm3,HIGH);
digitalWrite(rm4,LOW);
}
void BackWard()
{
digitalWrite(lm1,LOW);
digitalWrite(lm2,HIGH);
digitalWrite(rm1,LOW);
digitalWrite(rm2,HIGH);

digitalWrite(lm3,LOW);
digitalWrite(lm4,HIGH);
digitalWrite(rm3,LOW);
digitalWrite(rm4,HIGH);
}
void Left()
{
digitalWrite(lm1,LOW);
digitalWrite(lm2,HIGH);
digitalWrite(rm1,HIGH);
digitalWrite(rm2,LOW);

digitalWrite(lm3,LOW);
digitalWrite(lm4,HIGH);
digitalWrite(rm3,HIGH);
digitalWrite(rm4,LOW);
}
void Right()
{
digitalWrite(lm1,HIGH);
digitalWrite(lm2,LOW);
digitalWrite(rm1,LOW);
digitalWrite(rm2,HIGH);

digitalWrite(lm3,HIGH);
digitalWrite(lm4,LOW);
digitalWrite(rm3,LOW);
digitalWrite(rm4,HIGH);
}
void sTOP()
{
digitalWrite(lm1,LOW);
digitalWrite(lm2,LOW);
digitalWrite(rm1,LOW);
digitalWrite(rm2,LOW);

digitalWrite(lm3,LOW);
digitalWrite(lm4,LOW);
digitalWrite(rm3,LOW);
digitalWrite(rm4,LOW);
}



//int [] calc_distance()
//{
//int distances [3] = {0};
//// Clears the trigPin
//digitalWrite(trigPin1, LOW);
//digitalWrite(trigPin2, LOW);
//
//digitalWrite(trigPin3, LOW);
//
//delayMicroseconds(2);
//// Sets the trigPin on HIGH state for 10 micro seconds
//digitalWrite(trigPin1, HIGH);
//digitalWrite(trigPin2, HIGH);
//
//digitalWrite(trigPin3, HIGH);
//
//delayMicroseconds(10);
//digitalWrite(trigPin1, LOW);
//digitalWrite(trigPin2, LOW);
//digitalWrite(trigPin3, LOW);
//// Reads the echoPin, returns the sound wave travel time in microseconds
//
//for(int i = 0;i<3;i++)
//{
//  duration = pulseIn(echoPin, HIGH);
//distances[i] =  duration*0.034/2;
//echoPin++;
//}
//// Calculating the distance
//
//// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance);
//
//return distances;
//  
//
//}





void calcDistances()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance[0] = duration * 0.034 / 2;

  duration = pulseIn(echoPin2, HIGH);
  distance[1] = duration * 0.034 / 2;

  duration = pulseIn(echoPin3, HIGH);
  distance[2] = duration * 0.034 / 2;

  /*Serial.println("ultrasonic 2: "+String(distance[1]) );
    Serial.println("ultrasonic 1: "+String(distance[0]));
    Serial.println("ultrasonic 3: "+String(distance[2] ) );*/
}


void sendData()
{
  char data ;
  for (int i = 0; i < 3; i++)
  {
    if (distance[i] > 50)
    {
      //distance[i]=0;
      if (i == 0)
        data = 'q';
      else if (i == 1)
        data = 'w';
      else if ( i == 2)
        data = 'e';

      if (data != prevDir[i])
      {
        Serial.write(data);
        prevDir[i] = data;

        return;
      }
    }

    /// send if no way is available
    else {
      if (i == 0)
        data = 'a';
      else if (i == 1)
        data = 's';
      else if ( i == 2)
        data = 'd';

      if (data != prevDir[i])
      {
        Serial.write(data);
        prevDir[i] = data;
        return;
      }
    }
  }

}


void calcSeq()
{

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);


  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance[0] = duration * 0.034 / 2;

  //////////////////

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);


  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin2, LOW);


  duration = pulseIn(echoPin2, HIGH);
  distance[1] = duration * 0.034 / 2;

  //////////////////////////

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);


  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin3, LOW);

  duration = pulseIn(echoPin3, HIGH);
  distance[2] = duration * 0.034 / 2;


/*  Serial.println("ultrasonic 1: " + String(distance[0]));

  Serial.println("ultrasonic 2: " + String(distance[1]) );

  Serial.println("ultrasonic 3: " + String(distance[2] ) );*/


  
}
