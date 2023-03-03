int myArray[31];
byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
size_t pcDataLen = sizeof(myArray);
bool newData=false;

void setup() {
    Serial.begin(115200);//baudrate
}

void loop() {

  
    checkForNewData();
    
    if (newData == true) {
      for (int j=0; j<31; j=j+1){
      Serial.println(myArray[j]);
    }
    Serial.println(0);
    Serial.end();
    }

    
}
      
void checkForNewData () {
    if (Serial.available() >= pcDataLen && newData == false) {
        byte inByte;
        for (byte n = 0; n < pcDataLen; n++) {
            ddata [n] = Serial.read();
        }
        while (Serial.available() > 0){
          byte dumpByte = Serial.read();
        }
        newData = true;
    }
}
