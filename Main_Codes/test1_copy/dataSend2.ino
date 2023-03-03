//int myArray_X[100];
//int myArray[30];
//int myArray_Y[100];
//byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
//size_t pcDataLen = sizeof(myArray);
//bool newData=false;




void checkNewSend2() {
  
  int count = 0;  
  while( true){
    
    if (Serial.available() >= pcDataLen){
      byte inByte;
      for( byte n=0; n<pcDataLen; n++){
        ddata [n] = Serial.read();
      }
      while(Serial.available() > 0){
        byte dumpByte = Serial.read();
      }

      delay(100);

      if ( myArray[0] == -1 ){
        count = count - 15;
      }
      else{
        long int sum =0;
        
        for ( int j=0; j<30; j=j+2){
          myArray_X[count] = myArray[j];
          myArray_Y[count] = myArray[j+1];
          count = count + 1;
        }
        
        for ( int j=0; j<30; j=j+1) {
          if (myArray[j] == -1){
            sum = sum - (30 - j);
            break;
          }
          else{
            sum = sum + myArray[j];
          }
        }
        
        Serial.println(sum);

        if ( myArray[29] == -1){
          break;
        }
      
      }
      
    }

  }
}
