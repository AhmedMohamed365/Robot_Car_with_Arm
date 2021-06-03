/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
const int trigPin2 = 9;
const int echoPin2 = 10;

const int trigPin3 = 11;
const int echoPin3 = 12;


const int trigPin = 2;
const int echoPin = 3;
// defines variables
long duration;
int distance[3] ={0};

char input;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {


calcDistances();

}


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
distance[0] = duration*0.034/2;

duration = pulseIn(echoPin2, HIGH);
distance[1] = duration*0.034/2;

duration = pulseIn(echoPin3, HIGH);
distance[2] = duration*0.034/2;
}


void sendData()
{
  for(int i = 0;i<3;i++)
  {
    if(distance[i] <5)
    {
      distance[i]=0;

      continue;
    }

    Serial.write(i);
  }

  
}
