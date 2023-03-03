// Set arm to O location(0,0)
// To detect the sensor, first arms are move to forward direction and then move back

void setting(){

  if ( setTo0 == 0) {

    //setting X
    // moving 3000 steps forward 
    digitalWrite(DIRX, 1);
    for(long int i=0; i<3000; i++){
      digitalWrite(PULSX,HIGH);
      delayMicroseconds(X_frequency);
      digitalWrite(PULSX,LOW);
      delayMicroseconds(40);
    }
    delay(500);
//    digitalWrite(DIRX, 0);
//    for(long int i=0; i<3000; i++){
//      digitalWrite(PULSX,HIGH);
//      delayMicroseconds(X_frequency);
//      digitalWrite(PULSX,LOW);
//      delayMicroseconds(40);
//    }
    // move backward until sensor detect
    digitalWrite(DIRX, 0);
    while( X_Point_1 == 1 ){
      digitalWrite(PULSX, HIGH);
      delayMicroseconds(X_frequency);
      digitalWrite(PULSX,LOW);
      delayMicroseconds(40);
    }
    
    
    // setting Y 
    // moving 9000 steps forward 
    digitalWrite(DIRY, 0);
    for(long int i=0; i<9000; i++){
      digitalWrite(PULSY,HIGH);
      delayMicroseconds(Y_frequency);
      digitalWrite(PULSY,LOW);
    }
    delay(500);
//    digitalWrite(DIRY, 1);
//    for(long int i=0; i<9000; i++){
//      digitalWrite(PULSY,HIGH);
//      delayMicroseconds(Y_frequency);
//      digitalWrite(PULSY,LOW);
//    }
    // move backward until sensor detect
    digitalWrite(DIRY, 1);
    while( Y_Point_1 == 1 ){
      digitalWrite(PULSY, HIGH);
      delayMicroseconds(Y_frequency);
      digitalWrite(PULSY,LOW);
    }
 

    delay(500);
  
    X_Point_1 = 1;
    Y_Point_1 = 1;

    setTo0 == 1;
  
  }
  
}

// move arms to (0,0) at the end
void setting1(){  
  runY(current_Y *(-10));
  runX(current_X *(-10));
  
}
