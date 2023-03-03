  #define DIRX 8
#define PULSX 9

#define DIRY 11
#define PULSY 12

#define IndX2 21
#define IndY2 20
#define IndX1 19
#define IndY1 18

#define Relay1 22
#define Solonoid 24

#define MagentS_Up 4
#define MagentS_Down 5
//------------------------------------------------------------------------

// x-steps 77937
// 2500 +x to check

int X_frequency = 65;// 65 speed
int Y_frequency = 10;// 15 speed

bool X_Point_1 = 1;
bool X_Point_2 = 1;
bool Y_Point_1 = 1;

bool Out = 0;
bool setToO = 0;

bool X1_pass = 0;
bool X2_pass = 0;

long int current_X = 0;
long int current_Y = 0;

long int X_Step = 77700;
long int Y_Step = 90000;
//-----------------------------------------------------------------------------
//
//int myArray[2];
//int myArray_X[30];
//int myArray_Y[30];
//byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
//size_t pcDataLen = sizeof(myArray);
//----------------------------------------------------------------------------

//// New code with handshake------------
//int myArray[3];
//int myArray_X[50];
//int myArray_Y[50];
//byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
//size_t pcDataLen = sizeof(myArray);
//
//int DataRecived = 1;
//bool newData=false;
//int count = 0;
//int flag;
//int set = 4;
//
//int average_X;
//int average_Y;
//int Sum_X = 0;
//int Sum_Y = 0;
//
////--------------------------------------------------------------------------

//// update with new---------------------------------------------
//int myArray[30];
//int myArray_X[30];
//int myArray_Y[30];
//byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
//size_t pcDataLen = sizeof(myArray);
//bool newData=false;
//-------------------------------------------------------------------

//// update with new 2-------------------------------------------------
int myArray_X[100];
int myArray[30];
int myArray_Y[100];
byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
size_t pcDataLen = sizeof(myArray);
bool newData=true;
//--------------------------------------------------------------------


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
    delayMicroseconds(40);
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

      runX(set_point_X*10);
      
      runY(set_point_Y*10);

      digitalWrite(Solonoid, HIGH);
      delay(1000);

      while( true){
        if (digitalRead(MagentS_Up) == HIGH){
          digitalWrite(Relay1,HIGH);
          delay(500);
          digitalWrite(Relay1,LOW);
          break;
        }
      }

//      digitalWrite(Relay1,HIGH);
//      delay(500);
//      digitalWrite(Relay1,LOW);
      
      digitalWrite(Solonoid, LOW);
      delay(1000);

      while( true){
        if( digitalRead(MagentS_Down) == HIGH){
          break;
        }
      }
      
      current_X = myArray_X[i];
      current_Y = myArray_Y[i];

      // active S and U
      
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

  attachInterrupt(digitalPinToInterrupt(IndX1),X1_CH,FALLING);
  attachInterrupt(digitalPinToInterrupt(IndX2),X2_CH,FALLING);

  attachInterrupt(digitalPinToInterrupt(IndY1),Y1_CH,FALLING);
  attachInterrupt(digitalPinToInterrupt(IndY2),Y2_CH,FALLING);
  
  Serial.begin(115200);

}


void loop(){
  
  setting0();

  checkNewSend2();

  int j=0;
  while (true) {
    Serial.println(myArray_X[j]);
    Serial.println(myArray_Y[j]);

    if ( myArray_X[j] == -1){
      break;
    }
    j = j+1;
  }


  set_point(); 
  Serial.println("done..........................");

//  delay(1000);
  X_Point_1 = 1;
  Y_Point_1 = 1;

  setting();
  
   delay(1000000);
  
}


void X1_CH(){
  noInterrupts();
  X_Point_1 = 0;
//  Serial.println("X1_CH");
  interrupts();  
}
void X2_CH(){
  noInterrupts();
  Out = 1;
  interrupts();  
}

void Y1_CH(){
  noInterrupts();
  Y_Point_1 = 0;
//  Serial.println("Y1_CH");
  interrupts();  
}
void Y2_CH(){
  noInterrupts();
  Out = 1;
  interrupts();  
}
