//------------ veriable---------------//
//int start[2];
//byte* sdata = reinterpret_cast<byte*>(&start); // pointer for transferData()
//size_t startDataLen = sizeof(start);

void check_start(){

  

  while( true){
    if ( digitalRead(Button) == HIGH) {

    Serial.println(111);
    
    if (Serial.available() >= startDataLen){
      // store receive data
      byte inByte;
      for( byte n=0; n<startDataLen; n++){
        sdata [n] = Serial.read();
      }
      while(Serial.available() > 0){
        byte dumpByte = Serial.read();
      }

      delay(100);
//      Serial.print("data------------------");
//      Serial.println(start[1]);
      if ( start[1] == 111){
          Serial.println("button check");
          break;
      }
      
    }
    break;
  }
  delay(500);
  }
}
