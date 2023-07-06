//mofifunoluwa.k.control_car
//2023 work
float controlpwm = 0.00;
float kp = 3.00;
float error = 0.00;
float desired = 20.00;
float actual = 0.00;
int TRIG = 4;
int ECHO = 5;
int IN1 = 13;
int IN2 = 12;
int IN3 = 8;
int IN4 = 7;
int ENA = 11;
int ENB = 10;
float timeduration;
float distance;
float distance_cm;
I 




void setup() {




  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  delay(1000);
}




void loop() {
  actual = get_distance();
  error = desired - actual;
  controlpwm = kp * error;
  movePID(controlpwm);
  distance_cm = get_distance();
  Serial.print("distance:");
  Serial.println(distance_cm);

  // if (distance_cm > 25.0) {
  //   forward();
  // } else {
  //   stop();
  // }
}





float get_distance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  //  delayMicroseconds(2);
  timeduration = pulseIn(ECHO, HIGH);
  distance = (timeduration / 2) * 0.034;


  return (distance);
}



void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}



void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void right(int Speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed / 2);
}


void left(int Speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, Speed / 2);
  analogWrite(ENB, Speed);
}


void reverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}



void movePID(float speed) {
  int signpwm;
  if (speed >= 0) {
    signpwm = 1;
    speed = speed * 4;
  } else {
    signpwm = -1;
  }
  int magpwm = constrain(abs(speed), 0, 150);
  analogWrite(ENA, magpwm);
  analogWrite(ENB, magpwm);
  if (signpwm == -1) {
    forward();
  } else {
    reverse();
  }
}