

//Run Program On Mega 2560 
//Com 7
// LiquidCrystal
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Bluetooth  
boolean State_bluetooth = false;

// Local Value TX&RX
int iTX = 0; // ส่ง int 
int iRX = 0;  //  รับ  int
char cTX = ' '; //  ส่ง char 
char cRX  = ' ';  //  รับ char 


// Prototype Function Buletooth 
boolean isConnection(){
 // Serial.println("Start Connection Bluetooth Mega 2650 to Nano ");
    State_bluetooth = digitalRead(2);
    if(State_bluetooth){
     // Serial.println(" Connection Sucefull ");
      return true;
    }
    
else  {
 // Serial.println(" Connection Error "); 
  return  false;    
      }
}




boolean check_Mode_1(){  
  // Local Value TX&RX
int iTX = 0; // ส่ง int 
int iRX = 0;  //  รับ  int
char cTX = ' '; //  ส่ง char 
char cRX  = ' ';  //  รับ char 
int i = 256,j = 256;
    // isconection = 1 
   Serial.println(" Connection Sucefull ");
   cRX = isRX(); 
   while(cRX!='A'&&i){
     cRX = isRX(); 
     i--;
   }
    delay(10);
      isTX('B'); 
    delay(10);
   while(cRX!='C'&&j){
     cRX = isRX(); 
     j--;
     
   }
   
    Serial.println(cRX);
    if(cRX=='C'){
      
  return true;
 }
 else {
  return false;
 }
 
}


boolean check_Mode_0(){
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
void isTX(const char  * Tx){
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
  
 // Start Serial 
  Serial.begin(9600);
 // Start Bluetooth
  pinMode(2,INPUT);  //  pin 2  State Bluetooth  pin RX1  TX1 = TX RX Bluetooth 
  Serial1.begin(38400);
  // Start LCD 
   lcd.begin();
   lcd.backlight();
   

}

void loop() {
  if(isConnection()){
  check_Mode_1();
}
else {
   check_Mode_0();
}




// Stop Loop
//while(1);
delay(100);
 
}
