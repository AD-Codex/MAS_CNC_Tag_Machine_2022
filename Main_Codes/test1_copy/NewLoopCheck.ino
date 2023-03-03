//
//void checkData(){
//
//  while(true){
//    if( DataRecived ){
//      checkForNewData();
//      delay(10);
//
//      if( newData ){
//        myArray_X[count] = myArray[0];
//        myArray_Y[count] = myArray[1];
//        flag = myArray[2];
//
//        Serial.println(int(myArray_X[count]));
//        Serial.println(int(myArray_Y[count]));
//        Serial.println(int( flag));
//
//        if( flag == 1 ) {
//          Sum_X = 0;
//          Sum_Y = 0;
//          for( int j=0; j<=count; j++ ){
//            Sum_X = Sum_X + myArray_X[j];
//            Sum_Y = Sum_Y + myArray_Y[j];
//          }
//          average_X = Sum_X / (count + 1) ;
//          average_Y = Sum_Y / (count + 1) ;
//
//          Serial.println( int(average_X) );
//          Serial.println( int(average_Y) );
//          Serial.println( int(count));
//        }
//
//        if( flag == 2 ){
//          count = count -(set + 1);
//        }
//
//        if( flag == 3){
//          myArray_X[count] = 0;
//          myArray_Y[count] = 0;
//          Sum_X = 0;
//          Sum_Y = 0;
//          for( int j=0; j<=count; j++ ){
//            Sum_X = Sum_X + myArray_X[j];
//            Sum_Y = Sum_Y + myArray_Y[j];
//          }
//          average_X = Sum_X / count ;
//          average_Y = Sum_Y / count ;
//
//          Serial.println( average_X);
//          Serial.println( average_Y);
//          Serial.println( int(count-1));
//
//          count = count - 1;
//        }
//
//        if( flag == 4){
//          count = count - 1;
//          DataRecived = 0;
//          break;
//        }
//
//        newData = false;
//        count = count + 1;
//        delay(10);
//      }
////      count = count + 1;
//      
//    }
//    
//  }
//  
//}
//
//
//void checkForNewData () {
//  if (Serial.available() >= pcDataLen && newData == false) {
//       
//    byte inByte;
//    for (byte n = 0; n < pcDataLen; n++) {
//      ddata [n] = Serial.read();            
//    }
////    while(Serial.available() > 0){
////        byte dumpByte = Serial.read();
////      }
//    newData = true;
//  }
//  
//}
