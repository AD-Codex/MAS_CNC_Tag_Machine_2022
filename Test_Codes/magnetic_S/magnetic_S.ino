#define MagentS_Up 4
#define MagentS_Down 5

//#define Solonoid 24
//
//#define Relay1 22

void setup() {
  // put your setup code here, to run once:
  pinMode(MagentS_Up, INPUT);
  pinMode(MagentS_Down, INPUT);
//  pinMode(Relay1, OUTPUT);
//  pinMode(Solonoid, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Reading........");

  if (digitalRead(MagentS_Up) == HIGH){
    Serial.println("Magnet Down");
  }

  if (digitalRead(MagentS_Down) == HIGH){
    Serial.println("Magnet Up");
  }

  delay(1000);
  
//  if( digitalRead(ReedUp) == 1 ){
//    Serial.println("UP_HIGH");
//  }
//  else{
//    Serial.println("UP_LOW");
//  }
//
//  if( digitalRead(ReedDown) == 1 ){
//    Serial.println("Down_HIGH");
//  }
//  else{
//    Serial.println("Down_LOW");
//  }

//  digitalWrite(Relay1, HIGH);
//  Serial.println("HIGH");
//  delay(4000);
//  digitalWrite(Relay1, LOW);
//  Serial.println("LOW");
//  delay(4000);

}
