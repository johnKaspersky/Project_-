void isTX(int Tx){
  Serial1.write(Tx);
}
void isTX(char Tx){
  Serial1.write(Tx);
}
//void isTX(const char *Tx){
//  Serial1.write(Tx);
//  Serial.println(Tx);
//}

void isTX( String str){
 int i = 0,j=0;
 while(str[i]!='\0'){
   Serial1.write(str[i]); 
   
  i++;
    
 }
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
  String str;
 
  str = "50.6:13.2:1:1:8.4";
isTX(str);
delay(30);
  isTX('X');
      delay(2000);

}               

