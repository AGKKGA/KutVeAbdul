// PinOut

// QTR

int QTR_F = 5;  //The FRONT QTR-1A sensor, we will use it as a digital pin
int QTR_B = 6;  // The BACK QTR-1A sensor, we will use it as a digital pin

//Ultrasonic
// Vcc->5V 
int HC_TRIG = 4;  // Trigger pin for the front sensor
int HC_ECHO = 3;     // Echo pin for the front sensor

// Motor (Right)
int In1R = 10;  // Input 1 for the right DC motor to control the direction of the motor
int In2R = 11;  // Input 2 for the right DC motor to control the direction of the motor
int EnR = 12;   // Enable pin for the right DC motor to control the speed of the motor

// Motor (Left)
int In1L = 7;  // Input 1 for the left DC motor to control the direction of the motor
int In2L = 8;  // Input 2 for the left DC motor to control the direction of the motor
int EnL = 9;   // Enable pin for the left DC motor to control the speed of the motor

// Pins for 3 ultrasonic sensors 
int USS_trig[] = {13,15,16}; // Trigger for each sensor {left, front, right} NEED TO CHANGE PINS
int USS_echo[] = {17,18,19}; // Echo pins for each sensor {left front, right} NEED TO CHANGE PINS
// distance of each sensor showing
int USS_dist[] = {0,0,0}; // Distance value for each sensor {left, front, right}

// Setup
void setup() {
  Serial.begin(9600);
  pinMode(HC_TRIG, OUTPUT); // trig output
  pinMode(HC_ECHO, INPUT);  // echo input
}
// Function for measuring distance in cm by UltraSonic Sensor 
float getDist(int trig, int echo) {
  // Impulse 10 Microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Measuring time of signal treveling 
  uint32_t us = pulseIn(echo, HIGH);
  // Calculating distance (in cm) and returning
  return (us * 0.034 / 2); 
}
void dist_update(){ //this function
  for (int i=0; i<=2; i++){
    USS_dist[i]=getDist(USS_trig[i],USS_echo[i]);
  }
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
bool floor(uint32_t sensor){ //Function for QTR sensor
  if (sensor=="front"){
    // has to be a function that uses FRONT qtr sensor
    
  }
  else if(sensor=="back"){
    // has to be a function that uses BACK qtr sensor
  }
}
// Main loop ////////////////////////////////////////////////////////////
void loop() {   

}

