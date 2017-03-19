void isTX(int Tx){
  Serial1.write(Tx);
}
void isTX(char Tx){
  Serial1.write(Tx);
}

void isTX( const char *Tx){
  
 Serial1.write(Tx); 
 Serial.println(Tx);

  
}

// Prototype Function Regisver Data is Status  //  รับละมาแปลงชนิดข้อมูลอีกที
int isRX(){
  int Rx = 0;
  
  if(Serial1.available()){
  Rx = Serial1.read();
      return Rx;
 }
 
}
void setup() {

  Serial.begin(9600);
  Serial1.begin(38400);
}

void loop() {
isTX("23.21:80.1:1:0:7.5:420.1");
delay(30);
  isTX('X');
  
  delay(2000);

}               

