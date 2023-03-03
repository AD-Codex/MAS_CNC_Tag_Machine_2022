// CNC ultrasonic tag machine with image processing
// Arduino mega ADK
// 2022/08/08
// MAS Machine Build

// X-axis arm ---> X-arm steps 0 to 77700
// Y-axis arm ---> Y-arm steps 0 to -90000



#define DIRX 8  // x-motor DIR
#define PULSX 9 // x-motor PLS

#define DIRY 11 // y-motor DIR
#define PULSY 12  // y-motor PLS

 
#define IndY1 19  // Y = 0 sensor 18 19
#define IndX1 18  // X = 0 sensor 20 18

#define IndY2 20  // Y = -162 sensor
#define IndX2 21  // X = 628 sensor

#define Relay1 24 // ultrasonic gun attached relay
#define Solonoid 22 // solonoid attached relay

#define MagentS_Up 4 // top magnetic switch
#define MagentS_Down 5  // bottom magnetic switch

#define Button 52



////------------------------------------------------------------------------////

// x-steps 77937
// 2500 +x to check

int X_frequency = 65;// 65 speed
int Y_frequency = 10;// 15 speed

// start up settings-----------
bool X_Point_1 = 1;
bool X_Point_2 = 1;
bool Y_Point_1 = 1;
bool Y_Point_2 = 1;

bool Out = 0;
bool setTo0 = 0;

bool X1_pass = 0;
bool X2_pass = 0;

long int current_X = 0;
long int current_Y = 0;

long int X_Step = 77700;  // number of x steps considering
long int Y_Step = 90000;  // number of y steps considering

int myArray_X[100];  // x value stored array
int myArray[30];  // resived data stored array
int myArray_Y[100];  // y value stored array
byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
size_t pcDataLen = sizeof(myArray);
bool newData=true;

int tagTime[2];  
int timeu;  // tagging time (ms)
byte* tdata = reinterpret_cast<byte*>(&tagTime); // pointer for transferData()
size_t tagDataLen = sizeof(tagTime);
int NumOfArray;

int start[2];
byte* sdata = reinterpret_cast<byte*>(&start); // pointer for transferData()
size_t startDataLen = sizeof(start);

////--------------------------------------------------------------------////


// Move the X-arm by given steps
void runX(long int x){
  // checking the direction and set DIR value
  if ( 0 < x ){
    digitalWrite(DIRX,1);
  }
  else{
    digitalWrite(DIRX,0);
  }
  // move the X-arm
  for(long int i=0; i<abs(x); i++){
    digitalWrite(PULSX,HIGH);
    delayMicroseconds(X_frequency);
    digitalWrite(PULSX,LOW);
    delayMicroseconds(40);
  }  
}


// Move the Y-arm by given steps
void runY(long int y){
  // checking the direction and set DIR value
  if ( 0 < y ){
    digitalWrite(DIRY,1);
  }
  else{
    digitalWrite(DIRY,0);
  }
  // move the Y-arm
  for(long int i=0; i<abs(y); i++){
    digitalWrite(PULSY,HIGH);
    delayMicroseconds(Y_frequency);
    digitalWrite(PULSY,LOW);
  }  
}


// Move arms to given coordinates
void set_point(){
  if(newData == true) {
  int i=0;
  long int set_point_X = 0;
  long int set_point_Y = 0;
  while(true){
    if( myArray_X[i] == -1 ){
      Serial.println("----------task done------------");
      break;
    }
    else{
      set_point_X = myArray_X[i] - current_X;
      set_point_Y = myArray_Y[i] - current_Y;

      // move x-arm to given x-coordinate
      runX(set_point_X*10);
      // move y-arm to given y-coordinate  
      runY(set_point_Y*10);

      // move ultrasonic gun to down
      digitalWrite(Solonoid, HIGH);
      delay(500);

      // active ultrasonic gun only when gun at down position
      while( true){
        if (digitalRead(MagentS_Up) == HIGH){
          digitalWrite(Relay1,HIGH);
          // active ultrasonic given time
          delay(timeu);
          digitalWrite(Relay1,LOW);
          break;
        }
      }

      // move ultrasonic gun to up
      digitalWrite(Solonoid, LOW);
      delay(500);

      // wait until ultrasonic gun move up
      while( true){
        if( digitalRead(MagentS_Down) == HIGH){
          break;
        }
      }
      
      current_X = myArray_X[i];
      current_Y = myArray_Y[i];
      
    }

    i=i+1;
  }
  }
}


void setup(){


  
  pinMode(DIRX,OUTPUT);
  pinMode(PULSX,OUTPUT);
  pinMode(DIRY,OUTPUT);
  pinMode(PULSY,OUTPUT);
  pinMode(IndX1, INPUT);
  pinMode(IndX2, INPUT);
  pinMode(IndY1, INPUT);
  pinMode(IndY2, INPUT);
  
  pinMode(Solonoid, OUTPUT);
  pinMode(Relay1, OUTPUT);

  pinMode(MagentS_Up, INPUT);
  pinMode(MagentS_Down, INPUT);

  pinMode(Button, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(IndX1),X1_CH,FALLING);
  attachInterrupt(digitalPinToInterrupt(IndY1),Y1_CH,FALLING);
  
  Serial.begin(115200);
    Serial.println("reset");

}



void loop(){
 
  
  check_start();

  // setting arms to (0,0)
  setting();

  // receive the tagging time
  check_tag();

  // receive the coordinates
  checkNewSend2();

  // print given coordinates
  int j=0;
  while (true) {
    Serial.println(myArray_X[j]);
    Serial.println(myArray_Y[j]);

    if ( myArray_X[j] == -1){
      break;
    }
    j = j+1;
  }

  // move arms to given coordinates
  set_point();
  
  Serial.println("done..........................");

  // set arms at (0,0) at the end
  setting1();
  
  delay(1000000);
  
}



//------------------- interrupt functions--------------------//
void X1_CH(){
  noInterrupts();
  X_Point_1 = 0;
//  Serial.println("X1_CH");
  interrupts();
}


//void X2_CH(){
//  noInterrupts();
////  Out = 1;
//  Serial.println("X2_CH");
//  interrupts();  
//}

//void Y2_CH(){
//  noInterrupts();
//  Y_Point_1 = 0;
////  Serial.println("Y2_CH");
//  interrupts();
//}


void Y1_CH(){
  noInterrupts();
//  Y_Point_1 = 0;
  if (X_Point_1 == 0){
    Y_Point_1 = 0;
  }
//  Y_Point_1 = 0;
//  Serial.println("Y1_CH");
  interrupts();  
}

//----------------------------------------------------------------//
