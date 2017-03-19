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
float Temp_convert(String str){
  int i = 0;
   while(str[i]!='\0'){
    if(str[0]>='1' && str[0]<= '9' ){
      
        Serial.print(str[0]);
    }
    i++;
   }
  
}

void SubStringtofloat(String ch) {
int i=0;

String Temp = "";
String Hundi = "";
String Realy = "";
String volt = "";



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




 i++;
}
Serial.print(" ");

// Temp_convert(Temp);
 
 Serial.print(Temp);
  
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
   // Serial.println(S);
   //  Serial.print(" ");
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

