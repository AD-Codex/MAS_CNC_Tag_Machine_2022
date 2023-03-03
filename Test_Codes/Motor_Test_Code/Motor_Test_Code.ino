#define DIRX 8
#define PULSX 9

#define DIRY 11
#define PULSY 12


int frequency = 65;
int frequency2 = 15;

bool XDir = 1;
bool YDir = 0;

long int Xsteps = 77700;
long int Ysteps = 90000;

void Tag ( long int X , long int Y )
{ 
      
    digitalWrite(DIRX,XDir);
    digitalWrite(DIRY,YDir);
     
    for ( long int kx =0 ; kx < X ; kx++)
      {
      digitalWrite(PULSX,HIGH);
      delayMicroseconds(frequency);
      digitalWrite(PULSX,LOW);
      delayMicroseconds(50);
      }

//    for ( long int ky =0 ; ky < Y ; ky++)
//      {
//      digitalWrite(PULSY,HIGH);
//      delayMicroseconds(frequency2);
//      digitalWrite(PULSY,LOW);
//      }
 
}

void setup() {
  pinMode(DIRX,OUTPUT);
  pinMode(PULSX,OUTPUT);
  pinMode(DIRY,OUTPUT);
  pinMode(PULSY,OUTPUT);
  Serial.begin(115200);

}

void loop() {
  Tag(Xsteps , Ysteps);
  delay(5000);
}
