#define DIRX 8
#define PULSX 9

#define DIRY 11
#define PULSY 12


int X_frequency = 105; // 80 - 105 better
int Y_frequency = 5; // 15 better

long int step_x = 200;
int step_y = 300;

bool XDir = 0;
bool YDir = 0;


void Tag( int x, int y){
  digitalWrite(DIRX,XDir);
  digitalWrite(DIRY,YDir);

//  for ( long int X=0; X<x*100; X=X+1 ){
//    digitalWrite(PULSX, HIGH);
//    delayMicroseconds(X_frequency);
//    digitalWrite(PULSX,LOW);
//    delayMicroseconds(100);
//  }

  for ( long int Y=0; Y<y*100; Y=Y+1 ){
    digitalWrite(PULSY, HIGH);
    delayMicroseconds(Y_frequency);
    digitalWrite(PULSY,LOW);
  }

//  delay(5000);

  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(DIRX,OUTPUT);
  pinMode(PULSX,OUTPUT);
  pinMode(DIRY,OUTPUT);
  pinMode(PULSY,OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println(X_frequency);
  Serial.println(Y_frequency);
  
  Tag( step_x, step_y );
  delay(1000);
  X_frequency = X_frequency + 5;
  Y_frequency = Y_frequency + 5;
  

  if (XDir) {
    XDir = 0;
    YDir = 0;
  }
  else{
    XDir = 1;
    YDir = 1;
  }
  
}
