
=======
// PinOut
#define HC_TRIG 9
#define HC_ECHO 10

// Variables
float distFilt = 0; //distance filtering value 
// Setup
void setup() {
  Serial.begin(9600);
  pinMode(HC_TRIG, OUTPUT); // trig output
  pinMode(HC_ECHO, INPUT);  // echo input
}
// Function for measuring distance in cm by UltraSonic Sensor
float getDist() {
  // Impulse 10 Microseconds
  digitalWrite(HC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_TRIG, LOW);
  // Measuring time of signal treveling 
  uint32_t us = pulseIn(HC_ECHO, HIGH);
  // Calculating distance (in cm) and returning
  return (us / 58.3);
}
// Exponential filtering function for distance
float distFiltered(){
  float dist = getDist();       // getting distance   
  distFilt += (dist - distFilt) * 0.2;  // filtering
  return (distFilt); // returning
}
// Main loop ////////////////////////////////////////////////////////////
void loop() {  
  
}

