//www.elegoo.com
//2016.09.23
/*
Use "myservo.write (angle)" to command the micron servo 
to the angle degree which has a range from 10 to 180. 
If it exceeds the range, the micro servo won’t recognize 
this angle and will keep rotating.
*/
#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(0, 1); // RX, TX
#include <Servo.h> //servo library
Servo myservo; // create servo object to control servo
int Echo = A4;  
int Trig = A5; 
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS = 150;
int rightDistance = 0,leftDistance = 0,middleDistance = 0 ;


void _mForward()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);//digital output
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
 //Serial.println("go forward :");
 //Bluetooth.println("go forward");
    Serial.print(middleDistance);
    Serial.print(",");
    Serial.print(leftDistance);
    Serial.print(",");
    Serial.print(rightDistance);
   Serial.print(",");
    Serial.println("F");
    Bluetooth.print(middleDistance);
    Bluetooth.print(",");
    Bluetooth.print(leftDistance);
    Bluetooth.print(",");
    Bluetooth.print(rightDistance);
    Bluetooth.print(",");
    Bluetooth.println("F"); 
}

void _mBack()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
 //Serial.println("go back!");
 //Bluetooth.println("go back!");
    Serial.print(middleDistance);
    Serial.print(",");
    Serial.print(leftDistance);
    Serial.print(",");
    Serial.print(rightDistance);
    Serial.print(",");
    Serial.println("B"); 
    Bluetooth.print(middleDistance);
    Bluetooth.print(",");
    Bluetooth.print(leftDistance);
    Bluetooth.print(",");
    Bluetooth.print(rightDistance);
    Bluetooth.print(",");
    Bluetooth.println("B"); 
}

void _mleft()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW); 
 //Serial.println("go left!");
 //Bluetooth.println("go left!");
    Serial.print(middleDistance);
    Serial.print(",");
    Serial.print(leftDistance);
    Serial.print(",");
    Serial.print(rightDistance);
    Serial.print(",");
    Serial.println("L");
    Bluetooth.print(middleDistance);
    Bluetooth.print(",");
    Bluetooth.print(leftDistance);
    Bluetooth.print(",");
    Bluetooth.print(rightDistance);
    Bluetooth.print(",");
    Bluetooth.println("L"); 
}

void _mright()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
 //Serial.println("go right!");
 //Bluetooth.println("go right!");
    Serial.print(middleDistance);
    Serial.print(",");
    Serial.print(leftDistance);
    Serial.print(",");
    Serial.print(rightDistance);
    Serial.print(",");
    Serial.println("R"); 
    Bluetooth.print(middleDistance);
    Bluetooth.print(",");
    Bluetooth.print(leftDistance);
    Bluetooth.print(",");
    Bluetooth.print(rightDistance);
    Bluetooth.print(",");
    Bluetooth.println("R"); 
 

} 
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
 // Serial.println("obstacle at:");
 // Serial.print(middleDistance);
  //Bluetooth.println("obstacle at:");
 // Bluetooth.print(middleDistance);  
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
    rightDistance = 0,leftDistance = 0,middleDistance = 0 ;
    myservo.write(90);//setservo position according to scaled value
    delay(500); 
    middleDistance = Distance_test();
    #ifdef send
    Serial.print("middleDistance=");
    Serial.println(middleDistance);
    #endif

    if(middleDistance<=30)
    {     
      _mStop();
      delay(500);     
      myservo.write(10);//10°-180°          
      delay(1000);      
      rightDistance = Distance_test();
     // Serial.print("right distance:");
     // Serial.println(rightDistance);
     // Bluetooth.println("right distance: ");
     // Bluetooth.print(rightDistance);

      #ifdef send
      Serial.print("rightDistance=");
      Serial.println(rightDistance);
      #endif

      delay(500);
       myservo.write(90);              
      delay(1000);                                                  
      myservo.write(180);              
      delay(1000); 
      leftDistance = Distance_test();
     // Serial.print("left distance: ");
     // Serial.println(leftDistance);
     // Bluetooth.print("left distance: ");
     // Bluetooth.println(leftDistance);

      #ifdef send
      Serial.print("leftDistance=");
      Serial.println(leftDistance);
      #endif

      delay(500);
      myservo.write(90);              
      delay(1000);
      if(rightDistance>leftDistance)  
      {
        _mright();
        delay(360);
       }
       else if(rightDistance<leftDistance)
       {
        _mleft();
        delay(360);
       }
       else if((rightDistance<=30)||(leftDistance<=30))
       {
        _mBack();
        delay(180);
       }
       else
       {
        _mForward();
       }
    }  
    else
        _mForward(); 
                       
}

