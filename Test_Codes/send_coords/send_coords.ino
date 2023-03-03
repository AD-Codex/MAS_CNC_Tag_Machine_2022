int myArray_X[30];
int myArray[2];
int myArray_Y[30];
int OArray[5];
byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
size_t pcDataLen = sizeof(myArray);
bool newData=false;




void checkForNewData () {
  
  int count = 0;  
  while( true){
    
    if (Serial.available() >= pcDataLen && newData == false){
      byte inByte;
      for( byte n=0; n<pcDataLen; n++){
        ddata [n] = Serial.read();
      }
      while(Serial.available() > 0){
        byte dumpByte = Serial.read();
      }

      delay(1000);

      if( count > 0 ){
        if( myArray_X[count-1] == myArray[0]){
          if( myArray_Y[count-1] != myArray[1]){
            myArray_X[count] = myArray[0];
            myArray_Y[count] = myArray[1];
            count = count + 1;
          }
        }
        else{
          myArray_X[count] = myArray[0];
          myArray_Y[count] = myArray[1];
          count = count + 1;
        }
      }
      else{
        myArray_X[count] = myArray[0];
        myArray_Y[count] = myArray[1];
        count = count + 1;
      }
      
      Serial.println(0);   
    }

    if( myArray[0] == 9999 && myArray[1] == 9999 ){
      break;
    }
  }
}


void setup(){
  Serial.begin(115200);

}


void loop(){

  delay(1000);

  checkForNewData();

  int i=0;
  while(true){
    Serial.print("The list  ");
    Serial.print(i);
    Serial.print(". X element: ");
    Serial.print(myArray_X[i]);
    Serial.print(", Y element: ");
    Serial.println(myArray_Y[i]);

    if( myArray_X[i] == 9999){
      break;
    }

    i=i+1;
  }
  
  Serial.println();//print a \n and \r character 
  newData = false;
  
  delay(1000);
  Serial.println("done................");

  delay(8000);
  
}
