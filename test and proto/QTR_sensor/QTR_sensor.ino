int line=5;
int vcc = 4;
unsigned long color_val, time_1, time_2;
unsigned long WHITE=3000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(vcc, OUTPUT);
  digitalWrite(vcc, HIGH);
  Serial.println("Hello, programm started working");

}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(line, OUTPUT);
  digitalWrite(line,HIGH);
  delay(1);
  pinMode(line, INPUT);
  time_1=micros();

  while (digitalRead(line)==HIGH){
    delayMicroseconds(5);
  }
  time_2=micros();
  color_val=time_2-time_1;
  Serial.println(color_val);
  if (color_val<WHITE){
    Serial.println("TURN BACK");
  }
  delay(500);
}
