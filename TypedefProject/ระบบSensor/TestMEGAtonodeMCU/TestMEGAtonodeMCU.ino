int i_data = 1234;

float f_data = 567.89;

#include <SoftwareSerial.h>

SoftwareSerial NanoSerial(10, 11); // RX | TX

void setup()

{  

  pinMode(10,INPUT);

  pinMode(11,OUTPUT);

  Serial.begin(9600);

  NanoSerial.begin(57600);           

}

void loop() {

  Serial.print(i_data); Serial.print("\t");

  Serial.println(f_data);

  NanoSerial.print(i_data); NanoSerial.print(" ");

  NanoSerial.print(f_data); NanoSerial.print("\n");

  delay(100);

}
