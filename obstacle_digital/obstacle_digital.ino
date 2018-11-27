#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(0, 1); // RX, TX
#include <Servo.h> //servo library
Servo myservo; // create servo object to control servo
int Echo = A4;  
int Trig = A5; 
int in1 = A3;
int in2 = A2;
int in3 = A1;
int in4 = A0;
int ENA = 5;
int ENB = 11;
int ABS = 150;
int rightDistance = 0,leftDistance = 0,middleDistance = 0 ;
int h = 160;
int l = 0;
int distance[180];
char decision;

void _mForward()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  analogWrite(in1,h);//digital output
  analogWrite(in2,l);
  analogWrite(in3,l);
  analogWrite(in4,h);
  decision = 'F';
        delay(650);

}

void _mBack()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  analogWrite(in1,l);
  analogWrite(in2,h);
  analogWrite(in3,h);
  analogWrite(in4,l);
  decision = 'B';
     delay(650);
     _transmit();
}

void _mleft()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  analogWrite(in1,h);
  analogWrite(in2,l);
  analogWrite(in3,h);
  analogWrite(in4,l);  
  decision = 'L';
     delay(650);
     _transmit();
}

void _mright()
{
 analogWrite(ENA,ABS);
  analogWrite(in1,l);
  analogWrite(in2,h);
  analogWrite(in3,l);
  analogWrite(in4,h);
  decision = 'R';
     delay(650);
     _transmit();
} 
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
} 
 /*Ultrasonic distance measurement Sub function*/
int Distance_test()   
{
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH); 
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance/58;  
  return (int)Fdistance; 
}  

void _scan()
{
  
  for(int i=5;i<=170;i+=5)
        {  
  myservo.write(i);
  distance[i] = Distance_test();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  delay(50);
  }
 // Serial.println(" ");
  // Repeats the previous lines from 175 to 5 degrees
   middleDistance = distance[90];
   rightDistance = distance[10];
   leftDistance = distance[170];
  // myservo.write(90);
}

void _transmit()
{
  for(int i=5;i<=175;i+=5)
  {
  Serial.print(distance[i]); // Sends the distance value into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Bluetooth.print(distance[i]);
    Bluetooth.print(",");
  }
  Serial.print(middleDistance);
    Serial.print(",");
    Serial.print(leftDistance);
    Serial.print(",");
    Serial.print(rightDistance);
   Serial.print(",");
    Serial.print(decision);
    Serial.println(",");
    Bluetooth.print(middleDistance);
    Bluetooth.print(",");
    Bluetooth.print(leftDistance);
    Bluetooth.print(",");
    Bluetooth.print(rightDistance);
    Bluetooth.print(",");
    Bluetooth.print(decision);
    Bluetooth.println(",");

}
void setup() 
{ 
  myservo.attach(3);// attach servo on pin 3 to servo object
  Serial.begin(9600);  
  Bluetooth.begin(9600);
  Bluetooth.println("bluetooth connected!");   
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
} 

void loop() 
{ 
    _mStop();
    _scan();
    myservo.write(90);//setservo position according to scaled value

    if(middleDistance<=70)
    {     
      _mStop();
      delay(250);     
      
      if(rightDistance>leftDistance)  
      {
        _mright();
        delay(200);
       }
       else if(rightDistance<leftDistance)
       {
        _mleft();
        delay(200);
       }
       else if((rightDistance<=70)||(leftDistance<=70))
       {
        _mBack();
        delay(180);
       }
       else
       {
        _mForward();
       }
    }  // end if(middle distance)
    else
        _mForward();
        _transmit();   
}
