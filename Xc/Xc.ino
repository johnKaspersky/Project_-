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

String SumFloat() {
String S = "";
 S  =  String(temp)+":"+String(humi)+":"+String( Realy1)+":"+String( Realy2)+":"+String(Volte);
 return S;
}
void isString_Float(){
   delay(2000);
   isTX(SumFloat());
  delay(30);
  isTX('X');
}





void setup() {

  Serial.begin(9600);
  Serial1.begin(38400);
}

void loop() {
   Serial.println(SumFloat() );
  isString_Float();
}               

