
// Libraries
#include <math.h>

// button
int button = 2;

//Ultrasonic
// Vcc->5V 
int USS_trig = 5; // Trigger pin
int USS_echo = 4; // Echo pin

// Motor (Right)
int In1R = 11;  // Input 1 for the right DC motor to control the direction of the motor
int In2R = 10;  // Input 2 for the right DC motor to control the direction of the motor
int EnR = 12;   // Enable pin for the right DC motor to control the speed of the motor

// Motor (Left)
int In1L = 8;  // Input 1 for the left DC motor to control the direction of the motor
int In2L = 7;  // Input 2 for the left DC motor to control the direction of the motor
int EnL = 9;   // Enable pin for the left DC motor to control the speed of the motor

// VARIABLES
unsigned long color_val, QTR_time_1, QTR_time_2; //needed for QTR sensor's function working
unsigned long WHITE=3000; //brightness of white line. (needed to adjust bc values depends on environment)
bool direction = true;
bool opponent = false;
int distance_of_opponent = 30;

// Setup
void setup() {
  Serial.begin(9600);
  //Ultrasonic sensor
  pinMode(USS_trig, OUTPUT);
  pinMode(USS_echo, INPUT);
  //Right motor
  pinMode(In1R, OUTPUT);  // set the INPUT1 pin of the right DC motor as an OUTPUT
  pinMode(In2R, OUTPUT);  // set the INPUT2 pin of the right DC motor as an OUTPUT
  pinMode(EnR, OUTPUT);   // set the Enable pin of the right DC motor as an OUTPUT

  pinMode(In1L, OUTPUT);  // set the INPUT1 pin of the left DC motor as an OUTPUT
  pinMode(In2L, OUTPUT);  // set the INPUT2 pin of the left DC motor as an OUTPUT
  pinMode(EnL, OUTPUT);   // set the Enable pin of the left DC motor as an OUTPUT

  // Instead of stopping the whole thing, just stop the motor :)
  analogWrite(EnR, 0);  // Stop the right DC motor by making the speed 0
  analogWrite(EnL, 0);  // Stop the left DC motor by making the speed 0
  digitalWrite(13, HIGH); //showing that, robot is ready by led on board

  while (digitalRead(button)!=HIGH){ //waiting for the button to be pressed to start the robot.
    delay(1);
  }
  digitalWrite(13, LOW);
  delay(2000);

}
// Function for measuring distance in cm by UltraSonic Sensor 

// Main loop ////////////////////////////////////////////////////////////




float getDist() {
  // Impulse 10 Microseconds
  digitalWrite(USS_trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(USS_trig, LOW);
  // Measuring time of signal treveling 
  uint32_t us = pulseIn(USS_echo, HIGH);
  // Calculating distance (in cm) and returning
  return (us * 0.034 / 2); 
}
//foward function:
void goForward() {
  digitalWrite(In1R, HIGH);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2R, LOW);
  digitalWrite(In1L, HIGH);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2L, LOW);
  analogWrite(EnR, 255);     // move at full speed
  analogWrite(EnL, 255);  // move at full speed
}
void turnRight(int percent=100) { //percent value from 0 to 100, for power of motors (needed, because robot may turn too fast that ultrasnic sensors will not be able to measure) (initaly at 100)
  int power = ceil(2.55*percent);
  digitalWrite(In1R, LOW);  // It is low and the other one is high so the motor will move counterclockwise
  digitalWrite(In2R, HIGH);
  digitalWrite(In1L, HIGH);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2L, LOW);
  analogWrite(EnR, power);     
  analogWrite(EnL, power);  
}


void turnLeft(int percent=100) {  //percent value from 0 to 100, for power of motors (needed, because robot may turn too fast that ultrasnic sensors will not be able to measure) (initaly at 100)
  int power = ceil(2.55*percent);
  digitalWrite(In1R, HIGH);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2R, LOW);
  digitalWrite(In1L, LOW);  // It is low and the other one is high so the motor will move counterclockwise
  digitalWrite(In2L, HIGH);
  analogWrite(EnR, power);    
  analogWrite(EnL, power);  
}

// stop
void turn_off(int time = 100){
  digitalWrite(In1R, LOW);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2R, LOW);
  digitalWrite(In1L, LOW);  // It is high and the other one is high so the motor will stop
  digitalWrite(In2L, LOW);
  analogWrite(EnR, 0);
  analogWrite(EnL, 0);
  delay(time);
}

int counter = 0;
void search(){ //searching for opponent
  int angle = 6;
  if(opponent==false || counter>1){
    counter=0;
    opponent = false;
    Serial.println("Basic search...");
    Serial.print("Counter: ");
    Serial.println(counter);
    do{
      turnRight(70);
      delay(50);
      turn_off(70);
      if (getDist() <= distance_of_opponent){
        Serial.println("Found something in basic search...");
        opponent=true;
        Serial.println("Attacking...");
        while (getDist()<distance_of_opponent){
            goForward();
        }
      }
    } while(opponent == false);
  }
  else{
    Serial.println("Starting following function...");
    if(direction==true){
      Serial.println("Turning RIGHT and checking...");
      counter+=1;
      Serial.print("Counter: ");
      Serial.println(counter);
      for(int i=1;i<=angle;i++){
        turnRight(70);
        delay(50);
        turn_off(70);
        if (getDist() <= distance_of_opponent){
          Serial.println("Found something.. attacking");
          counter=0;
          Serial.println("Putting counter to zero while attacking");
          direction=true;
          while (getDist()<distance_of_opponent){
            goForward();
          }
          Serial.println("Stop attacking. Braking the loop");
          break;
        }
        else{
          direction=false;
          Serial.println("Didnt find nothing, changing searching to the left");
        }
      }
      if (direction=false){
        Serial.println("Returning to the initial position...");
        for(int i=1;i<=angle;i++){
          turnLeft(70);
          delay(60);
          turn_off(70);
        }
      }
    }
    else{
      Serial.println("Turning LEFT, and searching ...");
      counter+=1;
      Serial.print("Counter: ");
      Serial.println(counter);
      for(int i=1;i<=angle;i++){
        turnLeft(70);
        delay(50);
        turn_off(70);
        if (getDist() <= distance_of_opponent){
          Serial.println("Found something attacking...");
          counter=0;
          Serial.println("Putting counter to zero while attacking");
          direction=false;
          while (getDist()<distance_of_opponent){
            goForward();
          }
          Serial.println("Stopped attacking, breaking the loop");
          break;
        }
        else{
          direction=true;
          Serial.println("Changing direction of spinning to the RIGHT");
        }
      }
      if (direction=true){
        Serial.println("Returnign to inital position...");
        for(int i=1;i<=angle;i++){
          turnRight(70);
          delay(60);
          turn_off(70);
        }
      }
    }
  }
}
void loop() {

    if (getDist() < distance_of_opponent) {
      Serial.println("Found something from the main loop inital attacking");
      goForward(); 
      }
    else { 
      Serial.println("Didnt find nothing while the main loop in inital, starting search() function");
      while(true){
        search(); 
      }
      }
    // goForward();
}

