// QTR

#define QTR_F = 5;  //The FRONT QTR-1A sensor, we will use it as a digital pin
#define QTR_B = 6;  // The BACK QTR-1A sensor, we will use it as a digital pin

//Ultrasonic

int TRIGGER_ULTRASONIC = 4;  // Trigger pin for the front sensor
int ECHO_ULTRASONIC = 3;     // Echo pin for the front sensor

// Motor (Right)
int In1R = 10;  // Input 1 for the right DC motor to control the direction of the motor
int In2R = 11;  // Input 2 for the right DC motor to control the direction of the motor
int EnR = 12;   // Enable pin for the right DC motor to control the speed of the motor

// Motor (Left)
int In1L = 7;  // Input 1 for the left DC motor to control the direction of the motor
int In2L = 8;  // Input 2 for the left DC motor to control the direction of the motor
int EnL = 9;   // Enable pin for the left DC motor to control the speed of the motor

// Variables for the ultrasonic findings...
int distance = 0;  // initilize the distance between the Ultrasonic sensor and the object to be 0
int time_US;       // initilize the time that the Ultrasonic sensor takes to reach the object

// void setup part

void setup() {
  pinMode(QTR_F, INPUT);  // set the FRONT egde senosr as an INPUT
  pinMode(QTR_B, INPUT);  // set the BACK egde senosr as an INPUT

  pinMode(TRIGGER_ULTRASONIC, OUTPUT);  // set the trigger pin of the Ultrasonic sensor as
  an OUTPUT
    pinMode(ECHO_ULTRASONIC, INPUT);  // set the echo pin of the Ultrasonic sensor as an
  INPUTPUT

  pinMode(In1R, OUTPUT);  // set the INPUT1 pin of the right DC motor as an OUTPUT
  pinMode(In2R, OUTPUT);  // set the INPUT2 pin of the right DC motor as an OUTPUT
  pinMode(EnR, OUTPUT);   // set the Enable pin of the right DC motor as an OUTPUT

  pinMode(In1L, OUTPUT);  // set the INPUT1 pin of the left DC motor as an OUTPUT
  pinMode(In2L, OUTPUT);  // set the INPUT2 pin of the left DC motor as an OUTPUT
  pinMode(EnL, OUTPUT);   // set the Enable pin of the left DC motor as an OUTPUT

  // Instead of stopping the whole thing, just stop the motor :)
  analogWrite(EnR, 0);  // Stop the right DC motor by making the speed 0
  analogWrite(EnL, 0);  // Stop the left DC motor by making the speed 0
  delay(5000);          // delay for 5 seconds
}

// loop part
void loop() {

  // We will send a pulse from the ultrasonic to determine the distance between the sensor and the object
  // To fiding the distane between the Ultrasonic senor and the object

  digitalWrite(TRIGGER_ULTRASONIC, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_ULTRASONIC, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_ULTRASONIC, LOW);

  time_US = pulseIn(ECHO_ULTRASONIC, HIGH);  // Here we will determine the time that the pulse takes from the Front sensor to the object
  distance = time_US * 0.034 / 2;            // By using the time that we determined in previous line we will find the distance

  // Now me check if robot is in the ring or out of the ring
  //1 means black, 0 means white
  if (digitalRead(QTR_F) == 1 && digitalRead(QTR_B) == 1) {
    if (distance < 75) { goForward(); }
    else{ rotate(); }
  }

  else if (digitalRead(QTR_F) == 1 && digitalRead(QTR_B) == 0) {
    goForward();
    delay(1000);
    rotate();
  }

  else if (digitalRead(QTR_F) == 0 && digitalRead(QTR_B) == 1) {
    goBackward();
    delay(1000);
    rotate();
  }

  else {
    stop();
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

//Right

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
  delay(100);             // delay for 100 miliseconds
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


// soon will be adding the brake thingy thing
