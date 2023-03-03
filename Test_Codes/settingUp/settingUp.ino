#define DIRX 8
#define PULSX 9

#define DIRY 11
#define PULSY 12

#define IndX2 21
#define IndY2 20
#define IndX1 19
#define IndY1 18


// x-steps 77937
// 2500 +x to check

int X_frequency = 65;// 65 speed
int Y_frequency = 15;// 15 speed

bool X_Point_1 = 1;
bool X_Point_2 = 1;
bool Y_Point_1 = 1;

bool Out = 0;

bool X1_pass = 0;
bool X2_pass = 0;


long int X = 0;
long int Y = 0;

long int X_Step = 77700;
long int Y_Step = 90000;






void runX(long int x){
  if ( 0 < x ){
    digitalWrite(DIRX,1);
  }
  else{
    digitalWrite(DIRX,0);
  }
  
  for(long int i=0; i<abs(x); i++){
    digitalWrite(PULSX,HIGH);
    delayMicroseconds(X_frequency);
    digitalWrite(PULSX,LOW);
    delayMicroseconds(80);
  }
  
}

void runY(long int y){
  if ( 0 < y ){
    digitalWrite(DIRY,1);
  }
  else{
    digitalWrite(DIRY,0);
  }
  
  for(long int i=0; i<abs(y); i++){
    digitalWrite(PULSY,HIGH);
    delayMicroseconds(Y_frequency);
    digitalWrite(PULSY,LOW);
  }
  
}

void setting(){

  //setting X
  digitalWrite(DIRX, 1);
    for(long int i=0; i<3000; i++){
    digitalWrite(PULSX,HIGH);
    delayMicroseconds(X_frequency);
    digitalWrite(PULSX,LOW);
    delayMicroseconds(80);
  }
  delay(2000);
  digitalWrite(DIRX, 0);
  while( X_Point_1 == 1 ){
    digitalWrite(PULSX, HIGH);
    delayMicroseconds(X_frequency);
    digitalWrite(PULSX,LOW);
    delayMicroseconds(80);
  }
  delay(1000);
  
  //setting Y
  digitalWrite(DIRY, 0);
    for(long int i=0; i<9000; i++){
    digitalWrite(PULSY,HIGH);
    delayMicroseconds(Y_frequency);
    digitalWrite(PULSY,LOW);
  }
  delay(2000);
  digitalWrite(DIRY, 1);
  while( Y_Point_1 == 1 ){
    digitalWrite(PULSY, HIGH);
    delayMicroseconds(Y_frequency);
    digitalWrite(PULSY,LOW);
  }
  delay(1000);
  
}



void setup(){
  // put your setup code here, to run once:
  pinMode(DIRX,OUTPUT);
  pinMode(PULSX,OUTPUT);
  pinMode(DIRY,OUTPUT);
  pinMode(PULSY,OUTPUT);
  pinMode(IndX1, INPUT);
  pinMode(IndX2, INPUT);
  pinMode(IndY2, INPUT);
  pinMode(IndY1, INPUT);

  attachInterrupt(digitalPinToInterrupt(IndX1),X1_CH,FALLING);
  attachInterrupt(digitalPinToInterrupt(IndX2),X2_CH,FALLING);

  attachInterrupt(digitalPinToInterrupt(IndY1),Y1_CH,FALLING);
  attachInterrupt(digitalPinToInterrupt(IndY2),Y2_CH,FALLING);
  
  Serial.begin(115200);

}


void loop(){
  // put your main code here, to run repeatedly:
  setting();

  delay(5000);
  
}


void X1_CH(){
  noInterrupts();
  X_Point_1 = 0;
  Serial.println("X1_CH");
  interrupts();  
}
void X2_CH(){
  noInterrupts();
  Serial.println("X2_CH");
//  Out = 1;
  interrupts();  
}

void Y1_CH(){
  noInterrupts();
  Y_Point_1 = 0;
  Serial.println("Y1_CH");
  interrupts();  
}
void Y2_CH(){
  noInterrupts();
  Serial.println("Y2_CH");
//  Out = 1;
  interrupts();  
}
