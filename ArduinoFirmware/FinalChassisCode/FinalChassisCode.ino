int F_IN1 = 32;   
int F_IN2 = 34;

int F_IN3 = 36;
int F_IN4 = 38; 

int F_ENA = 35;
int F_ENB = 37;

int B_IN1 = 22;
int B_IN2 = 24;

int B_IN3 = 26;
int B_IN4 = 28;

int B_ENA = 25;
int B_ENB = 27;


void setup() {
  // put your setup code here, to run once:
  pinMode(F_IN1, OUTPUT);
  pinMode(F_IN2, OUTPUT);
  pinMode(F_IN3, OUTPUT);
  pinMode(F_IN4, OUTPUT);
  pinMode(F_ENA, OUTPUT);
  pinMode(F_ENB, OUTPUT);
  
  pinMode(B_IN1, OUTPUT);
  pinMode(B_IN2, OUTPUT);
  pinMode(B_IN3, OUTPUT);
  pinMode(B_IN4, OUTPUT);
  pinMode(B_ENA, OUTPUT);
  pinMode(B_ENB, OUTPUT);
}

void forward(){
//front left motor
  digitalWrite(F_IN1, HIGH);
  digitalWrite(F_IN2, LOW);
//front right motor
  digitalWrite(F_IN3, HIGH);
  digitalWrite(F_IN4, LOW);
  
  digitalWrite(F_ENA, HIGH);
  digitalWrite(F_ENB, HIGH);

//back left motor
  digitalWrite(B_IN1, HIGH);
  digitalWrite(B_IN2, LOW);
//back right motor
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, LOW); 

  digitalWrite(B_ENA, HIGH);
  digitalWrite(B_ENB, HIGH);

}

void backward(){
//front left motor
  digitalWrite(F_IN1, LOW);
  digitalWrite(F_IN2, HIGH);
//front right motor
  digitalWrite(F_IN3, LOW);
  digitalWrite(F_IN4, HIGH);
  
  digitalWrite(F_ENA, HIGH);
  digitalWrite(F_ENB, HIGH);

//back left motor
  digitalWrite(B_IN1, LOW);
  digitalWrite(B_IN2, HIGH);
//back right motor
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, HIGH); 

  digitalWrite(B_ENA, HIGH);
  digitalWrite(B_ENB, HIGH);
  
}

void leftMov(){
  //front left motor forward
  digitalWrite(F_IN1, LOW);
  digitalWrite(F_IN2, HIGH);
  // front left motor backward
  digitalWrite(F_IN3, HIGH);
  digitalWrite(F_IN4, LOW);

  digitalWrite(F_ENA, HIGH);
  digitalWrite(F_ENB, HIGH);
  
  //back left motor backward
  digitalWrite(B_IN1, HIGH);
  digitalWrite(B_IN2, LOW);
  //back right motor forward
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, HIGH);

  digitalWrite(B_ENA, HIGH);
  digitalWrite(B_ENB, HIGH);
  }

void rightMov(){
  //front left motor forward
  digitalWrite(F_IN1, HIGH);
  digitalWrite(F_IN2, LOW);
  // front left motor backward
  digitalWrite(F_IN3, LOW);
  digitalWrite(F_IN4, HIGH);

  digitalWrite(F_ENA, HIGH);
  digitalWrite(F_ENB, HIGH);
  //back left motor backward
  digitalWrite(B_IN1, LOW);
  digitalWrite(B_IN2, HIGH);
  //back right motor forward
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, LOW);

  digitalWrite(B_ENA, HIGH);
  digitalWrite(B_ENB, HIGH);
  }


void stopMotors() {
  digitalWrite(F_ENA, LOW);
  digitalWrite(F_ENB, LOW);
  digitalWrite(B_ENA, LOW);
  digitalWrite(B_ENB, LOW);
  
}

void loop() {
forward();
delay(1000);
stopMotors();
delay(1000);
backward();
delay(1000);
leftMov();
delay(1000);
rightMov();
delay(1000);
  

}
