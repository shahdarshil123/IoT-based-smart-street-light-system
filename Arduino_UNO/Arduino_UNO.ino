const int ldr = A1 ;
const int ProxSensor= A0;
const int led=9;  
int inputVal = 0;
String t="ON";
String data1="";
int value;

#include<SoftwareSerial.h>
SoftwareSerial s(2,3);

void setup() 
{                
  pinMode(led, OUTPUT);          
  pinMode(ldr, INPUT);  
  pinMode(ProxSensor,INPUT);    //Pin 2 is connected to the output of proximity sensor
  Serial.begin(9600);
  Serial.write(1);
  s.begin(9600);
  s.write(1);
  value=analogRead(ldr);
  Serial.println("Light intesity detected  is: ");
  Serial.print(value);
  delay(3000);
  Serial.println("System is initiated");
}

void loop()
{ 
  if(WIFI()=="ON")
  {
  if (analogRead(ldr)<=(value+10)) 
  { 
    if(analogRead(ProxSensor)<=150)      //Check the sensor output
    {
    inputVal = analogRead(ProxSensor);
    analogWrite(led,220);   // set the LED on
    delay(800);
  }
  else 
  {
    analogWrite(led,20);    // set the LED off
    inputVal = analogRead(ProxSensor);
    delay(800);
  }
  }
  else
   { 
    digitalWrite(led, LOW);
  }
  }
  else
  { 
    digitalWrite(led, LOW);
  }
}
String WIFI()
{ 
  Serial.flush();
   if(s.available()>0)
  {
  Serial.flush();
  int data=s.read();
  data1= data1+char(data);
  if(data1=="ON")
  {
  t="ON";
  Serial.println(data1);
  data1="";
  Serial.println("HIGH");
  }

  else if(data1=="OFF")
  {
  t="OFF";
  Serial.println(data1);
  data1="";
  Serial.println("LOW");
  }
  else
  t="ON";
  
}
return(t);
}
