

//bluetooth 
boolean State_bluetooth = false;
// COM 11

int iTX = 0;
int iRX = 0;
char cTX = ' ';
char cRX = ' ';

// isconction bluetooth 
boolean isConnection(){
   
 // Serial.println("Start Connection Bluetooth Mega 2650 to Nano ");
    State_bluetooth = digitalRead(2);
    if(State_bluetooth){
    //  Serial.println(" Connection Sucefull ");
      return true;
    }
    
else  {
 // Serial.println(" Connection Error "); 
  return  false;    
      }
}

// ตรวจสอบจาก Bluetooth  ถ้า  เป็น 1(เชื่อมต่อได้)  ทำงานปกติ (รับส่งข้อมูลระหว่างตัวรับ - ส่ง)
  // เป็น  0  ทำงานตามค่า ดีฟอลต์(เปิด _ ปิด ปั้มตามเวลา + ตามความชื้นของอากาศและพื้นดิน)
  // 'A' = ส่งข้อมูล
  // 'B' = รับข้อมูล
  // 'C' =  ยืนยัน
  boolean Mode_1(){
 int i = 256;
  // isconection = 1 
   Serial.println(" Connection Sucefull ");
   isTX('A'); 
   delay(10);
    cRX = isRX();
     while(cRX!='B'&&i){
     cRX = isRX(); 
     i--;
   }
    delay(10);
    isTX('C'); 
    delay(10);
 //Serial.println(cRX);
 if(cRX=='B'){
  return true;
 }
 else {
  return false;
 }



 
 
 

}
void Mode_0(){
   // isconection = 0
  Serial.println(" Connection Error "); 
   
}





// Prototype Function Tranfer Data is Operetion int and char Overload function  ตอนส่งพยายามส่งให้ตรงกับรูปแบบข้อมูล
void isTX(int Tx){
  Serial1.write(Tx);
}
void isTX(char Tx){
  Serial1.write(Tx);
}


// Prototype Function Regisver Data is Status  //  รับละมาแปลงชนิดข้อมูลอีกที
int isRX(){
  int Rx = 0;
    if(Serial1.available()){
  Rx = Serial1.read();
  
   return Rx;
  
  
}
}


/*
char int_to_char(int ch){
  if((ch>=65&& ch<=90)||(ch>=97 && ch<=122)){
    return ch;
  }
  else {
    Serial.print("int != char");
  }
 
}

*/





void setup() {
  //Serial COM
 Serial.begin(9600);
 //Serial bluetooth
  Serial1.begin(38400);
  pinMode(2,INPUT);  //  pin 2  State Bluetooth  pin RX1  TX1 = TX RX Bluetooth 
   
  

}

void loop() {
  // put your main code here, to run repeatedly:

if(isConnection()){
  Mode_1();
}
else {
   Mode_0();
}

// Stop Loop
//while(1);
delay(200);



}
