/*Arduino Voice Control Robot 
 *Version 1.0
 *Created By DIY Builder
 *Before Uploading the sketch you must install the required libraries first. 
 *Unless you'll get compilation error message.
 *Also remove the bluetooth and servo connector before uploading the sketch.
 *You can contact me here https://www.instagram.com/diy.builder/
 */
 


#include<NewPing.h>
#include <AFMotor.h>
#include <Servo.h>

#define RIGHT A2              // Right IR sensor connected to analog pin A2 of Arduino Uno:
#define LEFT A3               // Left IR sensor connected to analog pin A3 of Arduino Uno:
#define TRIGGER_PIN A1        // Trigger pin connected to analog pin A1 of Arduino Uno:
#define ECHO_PIN A0           // Echo pin connected to analog pin A0 of Arduino Uno:
#define MAX_DISTANCE 200      // Maximum ping distance:

unsigned int distance = 0;    //Variable to store ultrasonic sensor distance:
unsigned int Right_Value = 0; //Variable to store Right IR sensor value:
unsigned int Left_Value = 0;  //Variable to store Left IR sensor value:
  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //NewPing setup of pins and maximum distance:

String command;

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

Servo myservo;
int pos=0;     //variable to store the servo position:


void setup() {
  
Serial.begin(9600);
myservo.attach(10);
{
for(pos = 90; pos <= 180; pos += 1){    // goes from 90 degrees to 180 degrees:
  myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
  delay(15);                            //wait 15ms for the servo to reach the position:
  } 
for(pos = 180; pos >= 0; pos-= 1) {     // goes from 180 degrees to 0 degrees:
  myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
  delay(15);                            //wait 15ms for the servo to reach the position:
  }
for(pos = 0; pos<=90; pos += 1) {       //goes from 180 degrees to 0 degrees:
  myservo.write(pos);                   //tell servo to move according to the value of 'pos' variable:
  delay(15);                            //wait 15ms for the servo to reach the position:
  }
}
   pinMode(RIGHT, INPUT); //set analog pin RIGHT as an input:
   pinMode(LEFT, INPUT);  //set analog pin RIGHT as an input:
}
myservo.write(90);

}

void loop() {
  
 delay(10);
 while(Serial.available()) {
  command = "";  
  command = Serial.readString();
  
    Serial.print(command);
}
  if(command == "*move forward#"){
    forward();
  }else if(command == "*move backward#"){
    backward();
  }else if(command == "*turn left#"){
    left();
  }else if(command == "*turn right#"){
    right();
  }else if(command == "*stop#") {
    Stop();
 }else if(command == "*follow#"){
    follow();
  command = "";
}

void forward() {
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  delay(1500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
}

void backward() {
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  delay(1500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void left() {
  myservo.write(180);
  delay(500);
  myservo.write(90);
  delay(500);
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void right() {
  myservo.write(0);
  delay(500);
  myservo.write(90);
  delay(500);
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void follow(){
  delay(50);                                        //wait 50ms between pings:
distance = sonar.ping_cm();                       //send ping, get distance in cm and store it in 'distance' variable:
Serial.print("distance");                   
Serial.println(distance);                         // print the distance in serial monitor:


    Right_Value = digitalRead(RIGHT);             // read the value from Right IR sensor:
    Left_Value = digitalRead(LEFT);               // read the value from Left IR sensor:
 
Serial.print("RIGHT");                      
Serial.println(Right_Value);                      // print the right IR sensor value in serial monitor:
Serial.print("LEFT");                       
Serial.println(Left_Value);                       //print the left IR sensor value in serial monitor:

if((distance > 1) && (distance < 15)){            //check wheather the ultrasonic sensor's value stays between 1 to 15.
                                                  //If the condition is 'true' then the statement below will execute:
  //Move Forward:
  Motor1.setSpeed(130);  //define motor1 speed:
  Motor1.run(FORWARD);   //rotate motor1 clockwise:
  Motor2.setSpeed(130);  //define motor2 speed:
  Motor2.run(FORWARD);   //rotate motor2 clockwise:
  Motor3.setSpeed(130);  //define motor3 speed:
  Motor3.run(FORWARD);   //rotate motor3 clockwise:
  Motor4.setSpeed(130);  //define motor4 speed:
  Motor4.run(FORWARD);   //rotate motor4 clockwise:
  
}else if((Right_Value==0) && (Left_Value==1)) {   //If the condition is 'true' then the statement below will execute:
  
  //Turn Left                                                
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(FORWARD);   //rotate motor1 cloclwise:
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(FORWARD);   //rotate motor2 clockwise:
  Motor3.setSpeed(150);  //define motor3 speed:
  Motor3.run(BACKWARD);  //rotate motor3 anticlockwise:
  Motor4.setSpeed(150);  //define motor4 speed:
  Motor4.run(BACKWARD);  //rotate motor4 anticlockwise:
  delay(150);
  
}else if((Right_Value==1)&&(Left_Value==0)) {     //If the condition is 'true' then the statement below will execute:
  
  //Turn Right
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(BACKWARD);  //rotate motor1 anticlockwise:
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(BACKWARD);  //rotate motor2 anticlockwise:
  Motor3.setSpeed(150);  //define motor3 speed:
  Motor3.run(FORWARD);   //rotate motor3 clockwise:
  Motor4.setSpeed(150);  //define motor4 speed:
  Motor4.run(FORWARD);   //rotate motor4 clockwise:
  delay(150);
  
}else if(distance > 15) {                          //If the condition is 'true' then the statement below will execute:
  
  //Stop
  Motor1.setSpeed(0);    //define motor1 speed:
  Motor1.run(RELEASE);   //stop motor1:
  Motor2.setSpeed(0);    //define motor2 speed:
  Motor2.run(RELEASE);   //stop motor2:
  Motor3.setSpeed(0);    //define motor3 speed:
  Motor3.run(RELEASE);   //stop motor3:
  Motor4.setSpeed(0);    //define motor4 speed:
  Motor4.run(RELEASE);   //stop motor4:
}
}