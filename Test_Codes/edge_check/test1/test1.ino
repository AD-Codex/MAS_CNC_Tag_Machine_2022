#define DIRX 8
#define PULSX 9

#define DIRY 11
#define PULSY 12

#define IndX1 21
#define IndX2 20
#define IndX3 19
#define IndY1 18


// x-steps 77700
// Y-steps 89849

int X_frequency = 65;
int Y_frequency = 15;

bool X_Point_1 = 0;
bool X_Point_2 = 1;
bool X_Point_3 = 1;
bool Y_Point = 1;

long int X_Step = 0;
long int Y_Step = 0;




void measure(){
  
//  while( X_Point_1 == 0 ){
//    digitalWrite(DIRX, 1);
//    
//    digitalWrite(PULSX, HIGH);
//    delayMicroseconds(X_frequency);
//    digitalWrite(PULSX,LOW);
//    delayMicroseconds(50);
//  }
//
//  delay(5000);
//  Serial.println("X_Point 1");
//
//  while ( X_Point_3 == 1){
//    digitalWrite(DIRX, 1);
//    
//    digitalWrite(PULSX, HIGH);
//    delayMicroseconds(X_frequency);    
//    digitalWrite(PULSX,LOW);
//    delayMicroseconds(50);
//
//    X_Step = X_Step + 1;
//  }
//
//  Serial.println("X_POINT_3");
//
//  Serial.print("Total Step ");
//  Serial.println(X_Step);
//  delay(5000);


  while( Y_Point == 1){
    digitalWrite(DIRY, 1);
    
    digitalWrite(PULSY, HIGH);
    delayMicroseconds(Y_frequency);    
    digitalWrite(PULSY,LOW);

    Y_Step = Y_Step + 1;
  }

  Serial.print("Total Step ");
  Serial.println(Y_Step);
  delay(5000);


  
  
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


  attachInterrupt(digitalPinToInterrupt(IndX1),X1_CH,CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(IndX3),X3_CH,CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(IndY1),Y1_CH,CHANGE);

  
  Serial.begin(115200);
  pinMode(13,OUTPUT);

}


void loop(){
  // put your main code here, to run repeatedly:
  measure();
  delay(5000);
  
}




void X1_CH(){
  noInterrupts();
  if (X_Point_1){
    X_Point_1 = 0;
  }
  else{
    X_Point_1 = 1;
  }
  Serial.println("X1_CH");
  interrupts();  
}

void X3_CH(){
  noInterrupts();
  if (X_Point_3){
    X_Point_3 = 0;
  }
  else{
    X_Point_3 = 1;
  }
  Serial.println("X3_CH");
  interrupts();  
}

void Y1_CH(){
  noInterrupts();
  if (Y_Point){
    Y_Point = 0;
  }
  else{
    Y_Point = 1;
  }
  interrupts();
}
