
#include<Servo.h> // Servo Library outputs PPM signal so we are adding the library 
int mill=0,oldmill=0,curr=0;// Variables for calculating the time taken for one loop
int setpoint=110,Kp=2; // Process variables Setpoint is in centimeters below which the collision avoidance kicks in 
                      // Kp is propotional coanstant which ranges from 1 to 10 higher the value higher the response to obstacles 
int ch1=1500,ch2=1500; // Input variables 
Servo s1,s2; // Output 



void setup()
{
  Serial.begin(115200); // Serial protocol initialization
  s1.attach(9); // This binds the pin 9 to the s1 servo variable
  s2.attach(10); // This binds the pin 10 to the s1 servo variable
 
  
  
}
void loop()
{
  int left,right,front,back; // variables where corresponding sensors reading will be stored
  int d1,d2,d3,d4;
  int temp,temp1,temp2,temp3; // Temporary variables 
  int e1,e2,e3,e4; // Error variables
  int op1,op2,op3,op4,opx,opy; // Calculation and output variables
  int tt;
  tt=0;
  ch1=pulseIn(2,HIGH,25000); // This reads the Channel 1 of your RC receiver
  ch2=pulseIn(3,HIGH,25000); // This reads the Channel 2 of your RC receiver
  temp=0;
  temp1=0;
  temp2=0;
  temp3=0;
  
  //Since the arduino has multiplexed ADC there will be slight errors in 
  // reading the values from the sonar so we are going to read multiple times 
  // and average the values  
 
 //-------------Reading the Left Sonar--------------//
 
  for(int i=0;i<=3;i++)
  {
    left = analogRead(A0);
    delay(2); // This delay is to wait for the Arduino's ADC to finish its sampling
    temp=temp+left;
  }
  d1=temp/3; // the raw value read from the sonar is stored in the variable d1
  
  
 //-------------Reading the Right Sonar--------------//
 
  for(int i=0;i<=3;i++)
  {
    right = analogRead(A1);
    delay(2);
    temp1=temp1+right;
  }
  d2=temp1/3;
  
  delay(10);
 //-------------Reading the Front Sonar--------------//
 
  for(int i=0;i<=3;i++)
  { 
    front = analogRead(A2);
    delay(2);
    temp2=temp2+front;
  }
  d3=temp2/3;
  
  delay(10);
 //-------------Reading the Back Sonar--------------//
 
  for(int i=0;i<=3;i++)
  { 
    back = analogRead(A3);
    delay(2);
    temp3=temp3+back;
  }
  d4=temp3/3;
  
 delay(10);
  
  // in order to make the collision avoidance take over when the 
  // quadcopter is below the setpoint and avoide unnecessary errors due 
  // higher soanr values we are constraining sonar values to setpoint  
  d1=constrain(d1,0,setpoint);
  d2=constrain(d2,0,setpoint);
  d3=constrain(d3,0,setpoint);
  d4=constrain(d4,0,setpoint);
   
  // Caluculating the error in distance
  e1=setpoint-d1;
  e2=setpoint-d2;
  e3=setpoint-d3;
  e4=setpoint-d4;
  
  // Multiplying the error with the propotional coanstant
  op1=e1*Kp;
  op2=e2*Kp;
  op3=e3*Kp;
  op4=e4*Kp;
  
  op1=constrain(op1,0,200);
  op2=constrain(op2,0,200);
  op3=constrain(op3,0,200);
  op4=constrain(op4,0,200);
  
  opx=ch1+op1-op2;// Ch1 is the value read from the RC receiver 
  opy=ch2+op4-op3;
   
   s1.writeMicroseconds(opx); //This outputs the PPM signal to the Flight controller   	
   s2.writeMicroseconds(opy);	
   
  Serial.print(d1);
  Serial.print(",");
  Serial.print(d2);
  Serial.print(",");
  Serial.print(d3);
  Serial.print(",");
  Serial.println(d4);
  

  digitalWrite(13,HIGH);// Just to make sure the code is executing 
 /* mill=millis();
  curr=mill-oldmill;
  oldmill=oldmill+curr;
  Serial.println(curr);
  
  */
}
  
  
  
  
  

  
  
  
  
