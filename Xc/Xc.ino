 //Static value  test
 float temp = 35.2;
 float humi = 54.3;
 boolean  Realy1 = 1;
  boolean  Realy2 = 0;
  float Volte = 7.5;


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
//void SumString(char ch) {
//  String S = "";
//  while (ch != 'X') {
//    S +=  ch;
//    ch = isRX();
//    delay(10);
//  }
//
//  delay(2000);
//  if (sizeof(S) == 6 && ch != NULL) {
//      Serial.println(S);
//    //    gg(S);
//    //  Serial.print(" ");
//    // SubStringtofloat(S);
//  }
//  //else SumString(ch);
//
//
//}

void setup() {

  Serial.begin(9600);
  Serial1.begin(38400);
}

void loop() {
  String x = String(temp) + ":" +String(humi)+ ":"+String(Realy1)+":"+String(Realy2)+":"+String(Volte);
 
 Serial.println(x);
isTX(x);
delay(30);
  isTX('X');
      delay(2000);

}               

