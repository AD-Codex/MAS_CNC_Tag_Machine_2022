// Receiving coordinates from python
// An array with 30 int values received at per time in this way
// Then the sum of receive value send to pc again to check
// If value is same, ready to receive another data set
// Else stay in current loop until correct data set
// If there is half of data -1 sore in free place in array
// 30 size array of -1 sending by python to arduino to know that ready to receive coorct array


//----------------------------- veriable--------------------------------//
//int myArray_X[100];   x value stored array
//int myArray[30];    resived data stored array
//int myArray_Y[100];   y value stored array
//byte* ddata = reinterpret_cast<byte*>(&myArray);    pointer for transferData()
//size_t pcDataLen = sizeof(myArray);
//bool newData=false;
//---------------------------------------------------------------------------------


void checkNewSend2() {
  
  int count = 0;
  int Acount =0;
  while( true){        
    if (Serial.available() >= pcDataLen){
      // store receive data    
      byte inByte;
      for( byte n=0; n<pcDataLen; n++){
        ddata [n] = Serial.read();
      }
      while(Serial.available() > 0){
        byte dumpByte = Serial.read();
      }
      delay(100);

      if ( myArray[0] == -1 ){
        if (count>15){
        count = count - 15;
        }
      }
      else{
        Acount = Acount +1;
        long int sum =0;        
        for ( int j=0; j<30; j=j+2){
          myArray_X[count] = myArray[j];
          myArray_Y[count] = myArray[j+1];
          count = count + 1;
        }        
        for ( int j=0; j<30; j=j+1) {
          if (myArray[j] == -1){
            count = count-2;
            sum = sum - (30 - j);
            break;
          }
          else{
            sum = sum + myArray[j];
          }
        }
        // send sum of the data back to python by serial communication      
        Serial.println(sum);

        if ( myArray[29] == -1){
          break;
        }
        else{
          if ( Acount >= NumOfArray ){
//            Serial.println("shnlinfhyuie ehnrshclger dhlseib");
            myArray_X[count] = -1;
            myArray_Y[count] = -1;
            break;
          }
        }
        
      }
      
    }

  }
}
