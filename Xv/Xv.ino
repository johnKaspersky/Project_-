#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
char ch = ' ';


void isTX(int Tx) {
  Serial1.write(Tx);
}
void isTX(char Tx) {
  Serial1.write(Tx);
}

int isRX() {
  int Rx = 0;

  if (Serial1.available()) {
    Rx = Serial1.read();
    return Rx;
  }

}

String SubStringtofloat(String ch) {
int i=0;

String Temp = "";
String Hundi = "";
String Realy = "";
String volt = "";
String Amp = "";


while(ch[i]!='\0'){
  
//  if(ch[i]!= ':'){
//    Serial.print(ch[i]);
//  }
//  Serial.print(" ");
//  
if(i%23 == 0 || i%23 == 1  || i%23 == 2 || i%23 == 3){
  Temp+=ch[i];
}
else if( i%23 == 5 || i%23 == 6|| i%23 == 7|| i%23 == 8){
  Hundi+=ch[i];
}
else if( i%23 == 10 || i%23 == 12){
  Realy+=ch[i];
}
else if( i%23 == 14 || i%23 == 15|| i%23 == 16){
 volt+=ch[i];
}
else if(i%23 == 18 || i%23 == 19|| i%23 == 20 || i%23 == 21|| i%23 == 22){
 
   
    Amp+=ch[i];
   
}

Serial.print(Temp);

 i++;
}
  
  return Temp,Hundi,Realy,volt, Amp;
}
void SumString(char ch) {
  String S = "";
  while (ch != 'X') {
    S +=  ch;
    ch = isRX();
    delay(10);
  }

  delay(2000);
  if(sizeof(S)==6&&ch!=NULL){
   SubStringtofloat(S);
  }
  //else SumString(ch);
  

}
void setup() {
  Serial.begin(9600);
  Serial1.begin(38400);
  // Start LCD
  lcd.begin();
  lcd.backlight();



}
void loop() {
  ch = isRX();
 

SumString(ch);
 
}

