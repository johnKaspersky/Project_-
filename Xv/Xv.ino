#include <Wire.h>
#include <String.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
float dataRec[] = {0, 0, 0, 0, 0};
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

//float Temp_convert(String str){   // 50.3
// float i = 0,j =0 ;
//   while(str[i]!='\0'){
//             switch(str[i]){
//
//              if(i==0){
//             case '1' : j+10.0;break;
//              case '2' : j+20.0;break;
//              case '3' : j+30.0;break;
//              case '4' : j+40.0;break;
//              case '5' : j+50.0;break;
//              case '6' : j+60.0;break;
//              case '7' : j+70.0;break;
//              case '8' : j+80.0;break;
//              case '9' : j+90.0;break;
//              case '.' : j+0.0;break;
//              }
//              else if(i==1){
//              case '1' : j+1.0;break;
//              case '2' : j+2.0;break;
//              case '3' : j+3.0;break;
//              case '4' : j+4.0;break;
//              case '5' : j+5.0;break;
//              case '6' : j+6.0;break;
//              case '7' : j+7.0;break;
//              case '8' : j+8.0;break;
//              case '9' : j+9.0;break;
//              case '.' : j+.0;break;
//
//              }
//              else if(i==2){
//
//              case '.' : j+0.0;break;
//              }
//              i++;
//   }
//}
//}
//
//
//void SubStringtofloat(String ch) {
//  int i = 0;
//
//  String Temp = "";
//  String Hundi = "";
//  String Realy = "";
//  String volt = "";
//
//
//
//  while (ch[i] != '\0') {
//
//    //  if(ch[i]!= ':'){
//    //    Serial.print(ch[i]);
//    //  }
//    //  Serial.print(" ");
//    //
//    if (i % 23 == 0 || i % 23 == 1  || i % 23 == 2 || i % 23 == 3) {
//      Temp += ch[i];
//    }
//    else if ( i % 23 == 5 || i % 23 == 6 || i % 23 == 7 || i % 23 == 8) {
//      Hundi += ch[i];
//    }
//    else if ( i % 23 == 10 || i % 23 == 12) {
//      Realy += ch[i];
//    }
//    else if ( i % 23 == 14 || i % 23 == 15 || i % 23 == 16) {
//      volt += ch[i];
//    }
//
//
//
//
//    i++;
//  }
//  Serial.print(" ");
//
//  //Temp_convert(Temp);
//
//  //Serial.print(Temp);
//
//}
void gg(char abc) {
  String S[5]; //array string for data
  int i = 0;
  while (ch != 'X') {
    if (ch != ':') //check dif value
      S[i] +=  ch;
    else
  
      i++; //increase i
      ch = isRX();
  }
  delay(2000);
  for (int i = 0; i < 5; i++) {
    dataRec[i] =  S[i].toFloat(); //convers array string to array float
    Serial.print(S[i] + " ");
    Serial.print("Float :  ");
    Serial.print(dataRec[i]);
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
  // Start LCD
  lcd.begin();
  lcd.backlight();



}
void loop() {
  ch = isRX();

//SumString(ch);
  gg(ch);

}

