////int myArray[30];
////byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
////size_t pcDataLen = sizeof(myArray);
////bool newData=false;
//
//
//
//void checkNewSend() {
//  while(true) {
//    checkForNewData();
//
//    if(newData){
//      int count = 0;
//      for (int j=0; j<30; j=j+2){
//        myArray_X[count] = myArray[j];
//        myArray_Y[count] = myArray[j+1];
//        count =count +1;
//      }
//      
//    }
//    break;
//  }
//  
//}
//      
//void checkForNewData () {
//    if (Serial.available() >= pcDataLen && newData == false) {
//        byte inByte;
//        for (byte n = 0; n < pcDataLen; n++) {
//            ddata [n] = Serial.read();
//        }
//        while (Serial.available() > 0){
//          byte dumpByte = Serial.read();
//        }
//        newData = true;
//    }
//}
