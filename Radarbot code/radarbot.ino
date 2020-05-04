#include <SoftwareSerial.h>
//SoftwareSerial mySerial(0,1); // RX, TX
// Includes the Servo library
#include <Servo.h>
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 5;
const int echoPin = 6;
// Variables for the duration and the distance
long duration;
int distance;

int motorPin = 8; //right side to IB - forward

int motorPin2 = 9; //left side to IA - forward

int motorPin3 = 10; //right side to IA - backward

int motorPin4 = 11; //left side to IB - backward

Servo myServo; // Creates a servo object for controlling the servo motor
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
   pinMode(motorPin, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  myServo.attach(7); // Defines on which pin is the servo motor attached
}

//Forward Fuction sets motors to go forward
void forward()
{
      //Serial.println("Forward");    
digitalWrite(motorPin, HIGH);

digitalWrite(motorPin2, LOW);      //foreward

digitalWrite(motorPin3, HIGH);  

digitalWrite(motorPin4, LOW);
delay(10);              
}

void halt(){ 

digitalWrite(motorPin, LOW);

digitalWrite(motorPin2, LOW);

digitalWrite(motorPin3, LOW);  

digitalWrite(motorPin4, LOW);
delay(2000);
 }

//Right Function sets motors for right
void right()
{
      //Serial.println("right");    
     digitalWrite(motorPin, LOW);  

      digitalWrite(motorPin2, HIGH);          //right

      digitalWrite(motorPin3, HIGH);  

      digitalWrite(motorPin4, LOW);
      delay(2000);
   
}

// Left Function sets motors for left
void left()
{        
      //Serial.println("left");    
      digitalWrite(motorPin, HIGH);  

      digitalWrite(motorPin2, LOW);          //left

      digitalWrite(motorPin3, LOW);  

      digitalWrite(motorPin4, HIGH);

      delay(2000);
     
}

// Back Fnction sets motors going backwards
void back()
{
      //Serial.println("back");    
    digitalWrite(motorPin, LOW);  

    digitalWrite(motorPin2, HIGH);  

    digitalWrite(motorPin3, LOW);  // back

    digitalWrite(motorPin4, HIGH); 
    delay(2000);
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance()
{ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

void loop() {

  long int forwdis, leftdis, rightdis;
  // rotates the servo motor from 15 to 165 degrees
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(20);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
 
      Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }

  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(20);
  distance = calculateDistance();
  Serial.print(i);
 Serial.print(",");
 Serial.print(distance);
Serial.print(".");
  }



 if (forwdis >= 15) //If the forward dis is greater than 12 cm keep going forward
{
forward();
 }
 else if (forwdis < 15)  //If distance is less than 15 cm then
  {
   // back();

      
        
    // Look left and get left distance
    myServo.write(165); 
    delay(300);
    leftdis = calculateDistance();
   // Serial.println (leftdis);
    
    // Look right and get right distance
    myServo.write(15);
    delay(300);
    rightdis = calculateDistance();
   // Serial.println (rightdis);
    
    // Reset servo centre possition
    myServo.write(90);
    delay(150);
      
      // If Left distance is greater than right then go left
      if (leftdis > rightdis) 
      {
     //   Serial.print("LEFT"); // Display direction of movment
      //  Serial.print(leftdis); // Print distance in cm
        left();
        forward();
      }

      // If right distance is greater than left distance go right
      else if (rightdis > leftdis) 
      {
       // Serial.print("RIGHT"); // Display direction of movment
       // Serial.print(rightdis); // Print distance in cm
        right();forward();
      }
    
      // If each are the same then go backwards and clear LCD
      else if (rightdis == leftdis) 
      {
         back(); forward(); 
      }   
  }
}

 

