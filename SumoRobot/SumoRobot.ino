/* Some important info:
Wheels diameter without band: 64mm
Wheels diameter with band: 67mm
Wheels widht: 26mm
Formula for movement: 
*/
/* Check list before match:
1. Wash Tires and dry it
2. Check Voltage in batteries.
*/



// PinOut

// QTR
// VIN -> 5V
int QTR_F = 5;  //The FRONT QTR-1A sensor, we will use it as a digital pin
int QTR_B = 6;  // The BACK QTR-1A sensor, we will use it as a digital pin

//Ultrasonic
// Vcc->5V 
int USS_trig; // Trigger pin
int USS_echo; // Echo pin

// Motor (Right)
int In1R = 10;  // Input 1 for the right DC motor to control the direction of the motor
int In2R = 11;  // Input 2 for the right DC motor to control the direction of the motor
int EnR = 12;   // Enable pin for the right DC motor to control the speed of the motor

// Motor (Left)
int In1L = 7;  // Input 1 for the left DC motor to control the direction of the motor
int In2L = 8;  // Input 2 for the left DC motor to control the direction of the motor
int EnL = 9;   // Enable pin for the left DC motor to control the speed of the motor

// VARIABLES


// Setup
void setup() {
  Serial.begin(9600);
  //Ultrasonic sensor
  pinMode(USS_trig, OUTPUT);
  pinMode(USS_echo, INPUT);
  // QTR
  pinMode(QTR_F, INPUT);  // set the FRONT egde senosr as an INPUT
  pinMode(QTR_B, INPUT);  // set the BACK egde senosr as an INPUT
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
}
// Function for measuring distance in cm by UltraSonic Sensor 
float getDist() {
  // Impulse 10 Microseconds
  digitalWrite(USS_trig, HIGH);
  delayMicroseconds(10);
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
  analogWrite(EnR, 255);     // move at full speed
  digitalWrite(In1L, HIGH);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2L, LOW);
  analogWrite(EnL, 255);  // move at full speed
}

void turnRight() {
  digitalWrite(In1R, LOW);  // It is low and the other one is high so the motor will move counterclockwise
  digitalWrite(In2R, HIGH);
  analogWrite(EnR, 255);     // move at full speed
  digitalWrite(In1L, HIGH);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2L, LOW);
  analogWrite(EnL, 255);  // move at full speed
}

// left
void turnLeft() {
  digitalWrite(In1R, HIGH);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2R, LOW);
  analogWrite(EnR, 255);    // move at full speed
  digitalWrite(In1L, LOW);  // It is low and the other one is high so the motor will move counterclockwise
  digitalWrite(In2L, HIGH);
  analogWrite(EnL, 255);  // move at full speed
}

// backwards
void goBackward() {
  digitalWrite(In1R, LOW);  // It is low and the other one is high so the motor will move
  // counterclockwise
    digitalWrite(In2R, HIGH);
  analogWrite(EnR, 255);    // move at full speed
  digitalWrite(In1L, LOW);  // It is low and the other one is high so the motor will move
  // counterclockwise
    digitalWrite(In2L, HIGH);
  analogWrite(EnL, 255);  // move at full speed
}

//rotate
void rotate() {
  digitalWrite(In1R, HIGH);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2R, LOW);
  analogWrite(EnR, 255);     // move at full speed
  digitalWrite(In1L, HIGH);  // It is high and the other one is high so the motor will stop
  digitalWrite(In2L, HIGH);
  analogWrite(EnL, 255);  // we can write 0 instead of 255 but since the both pins in this motor are high, the motor will stop
}

// stop
void stop() {
  digitalWrite(In1R, HIGH);  // It is high and the other one is low so the motor will move clockwise
  digitalWrite(In2R, HIGH);
  analogWrite(EnR, 255);     // move at full speed
  digitalWrite(In1L, HIGH);  // It is high and the other one is high so the motor will stop
  digitalWrite(In2L, HIGH);
  analogWrite(EnL, 255);  // we can write 0 instead of 255 but since the both pins in this motor are high, the motor will stop
}
bool floor(uint32_t cmd){ //Function for QTR sensor
  if (cmd=="front"){
    // has to be a function that uses FRONT qtr sensor
    
  }
  else if(cmd=="back"){
    // has to be a function that uses BACK qtr sensor
  }
}
// Main loop ////////////////////////////////////////////////////////////
void loop() {   

}

