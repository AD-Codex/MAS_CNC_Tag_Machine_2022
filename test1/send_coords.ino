////int myArray[2];
////int myArray_X[30];
////int myArray_Y[30];
////byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
////size_t pcDataLen = sizeof(myArray);
//
//
//void checkForNewData () {
//  
//  int count = 0;  
//  while( true){
//    
//    if (Serial.available() >= pcDataLen ){
//      byte inByte;
//      for( byte n=0; n<pcDataLen; n++){
//        ddata [n] = Serial.read();
//      }
//      while(Serial.available() > 0){
//        byte dumpByte = Serial.read();
//      }
//
//      delay(1000);
//
//      if( count > 0 ){
//        if( myArray_X[count-1] == myArray[0]){
//          if( myArray_Y[count-1] != myArray[1]){
//            myArray_X[count] = myArray[0];
//            myArray_Y[count] = myArray[1];
//            count = count + 1;
//          }
//        }
//        else{
//          myArray_X[count] = myArray[0];
//          myArray_Y[count] = myArray[1];
//          count = count + 1;
//        }
//      }
//      else{
//        myArray_X[count] = myArray[0];
//        myArray_Y[count] = myArray[1];
//        count = count + 1;
//      }
//      
//      Serial.println(0);   
//    }
//
//    if( myArray[0] == 9999 && myArray[1] == 9999 ){
//      break;
//    }
//  }
//}
