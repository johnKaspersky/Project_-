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

void String_to_float(char abc) {
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
  //  Serial.println(dataRec[i]);
  }
}
void getData_float(){
   int i=0;
  while(i<sizeof((dataRec[i]))){
    Serial.println(dataRec[i]);
    i++;
  }
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
  String_to_float(ch);
}

