// Receiving ultrasonic tagging time from python
// Then receive value send to pc again to check
// If value is same return to main loop
// Else stay in current loop until correct value

//------------ veriable---------------//
//int tagTime;
//byte* tdata = reinterpret_cast<byte*>(&tagTime); // pointer for transferData()
//bool newData=false;


void check_tag(){

  while( true){    
    if (Serial.available() >= tagDataLen){
      // store receive data
      byte inByte;
      for( byte n=0; n<tagDataLen; n++){
        tdata [n] = Serial.read();
      }
      while(Serial.available() > 0){
        byte dumpByte = Serial.read();
      }

      delay(100);
      if ( tagTime[0] == -1){
          break;
      }
      else{
        timeu = tagTime[0];
        NumOfArray = tagTime[1];
      }
      
      // send value back to python by serial communication
      Serial.println(timeu);
      Serial.println(NumOfArray );
      
      
    }
  }
  delay(500);
}
