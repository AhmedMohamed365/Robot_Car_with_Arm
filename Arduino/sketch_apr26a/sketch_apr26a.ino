
#include<SoftwareSerial.h>

SoftwareSerial s(5,6);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
s.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if ( s.available() >0)
{
 char d = s.read();
 Serial.println(d); 
}
}
