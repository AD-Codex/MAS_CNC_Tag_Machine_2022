#define DIRX 8
#define PULSX 9

#define DIRY 11
#define PULSY 12

#define IndX1 21
#define IndX2 20
#define IndX3 19
#define IndY1 18


// x-steps 77937
// 2500 +x to check

int X_frequency = 65;
int Y_frequency = 15;

bool X_Point_1 = 0;
bool X_Point_2 = 1;
bool X_Point_3 = 1;
bool Y_Point = 0;

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
    delayMicroseconds(50);
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


void setup(){
  // put your setup code here, to run once:
  pinMode(DIRX,OUTPUT);
  pinMode(PULSX,OUTPUT);
  pinMode(DIRY,OUTPUT);
  pinMode(PULSY,OUTPUT);
  pinMode(IndX1, INPUT);
  pinMode(IndX2, INPUT);
  pinMode(IndX3, INPUT);
  pinMode(IndY1, INPUT);
  
  Serial.begin(115200);

}


void loop(){
  // put your main code here, to run repeatedly:
  runX(2500);
//  delay(1000);
//  runY(-90000);
//  delay(1000);
//  runX(-77700);
//  delay(1000);
//  runY(90000);
  delay(5000);
  
}
