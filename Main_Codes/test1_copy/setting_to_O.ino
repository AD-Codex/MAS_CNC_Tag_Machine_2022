//#define DIRX 8
//#define PULSX 9
//
//#define DIRY 11
//#define PULSY 12
//
//#define IndX1 21
//#define IndY2 20
//#define IndX2 19
//#define IndY1 18
//
//
//int X_frequency = 100;// 65 speed
//int Y_frequency = 40;// 15 speed
//
//bool X_Point_1 = 1;
//bool X_Point_2 = 1;
//bool Y_Point_1 = 1;


void setting0(){
  //setting X
  digitalWrite(DIRX, 1);
  for(long int i=0; i<3000; i++){
    digitalWrite(PULSX,HIGH);
    delayMicroseconds(X_frequency);
    digitalWrite(PULSX,LOW);
    delayMicroseconds(50);
  }
  delay(1000);
  digitalWrite(DIRX, 0);
  while( X_Point_1 == 1 ){
    digitalWrite(PULSX, HIGH);
    delayMicroseconds(X_frequency);
    digitalWrite(PULSX,LOW);
    delayMicroseconds(50);
  }
  
  //setting Y
  delay(500);
  
  digitalWrite(DIRY, 0);
  for(long int i=0; i<18000; i++){
    digitalWrite(PULSY,HIGH);
    delayMicroseconds(Y_frequency);
    digitalWrite(PULSY,LOW);
  }
  delay(1000);
  digitalWrite(DIRY, 1);
  Y_Point_1 == 1;
  while( Y_Point_1 == 1 ){
    digitalWrite(PULSY, HIGH);
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
    delayMicroseconds(50);
  }
  delay(1000);
  digitalWrite(DIRX, 0);
  while( X_Point_1 == 1 ){
    digitalWrite(PULSX, HIGH);
    delayMicroseconds(X_frequency);
    digitalWrite(PULSX,LOW);
    delayMicroseconds(50);
  }
  
  //setting Y
  delay(500);
  
  digitalWrite(DIRY, 0);
  for(long int i=0; i<9000; i++){
    digitalWrite(PULSY,HIGH);
    delayMicroseconds(Y_frequency);
    digitalWrite(PULSY,LOW);
  }
  delay(1000);
  digitalWrite(DIRY, 1);
  Y_Point_1 == 1;
  while( Y_Point_1 == 1 ){
    digitalWrite(PULSY, HIGH);
    delayMicroseconds(Y_frequency);
    digitalWrite(PULSY,LOW);
  }
  
}
