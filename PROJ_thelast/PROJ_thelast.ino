#include "MPublic.h"
#include <TimerOne.h>
#include "Relay.h"
// Static value 
 
  float Volte = 0;
  
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

String SumFloat() {
String S = "";
 S  =  String(temp)+":"+String(humi)+":"+String(statRelay1)+":"+String( statRelay2)+":"+String(Volte);
 return S;
}
void isString_Float(){
   delay(2000);
   isTX(SumFloat());
  delay(30);
  isTX('X');
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//--mappin
#define vcc1 12
#define vcc2 11
#define vcc3 10
void fTimerIsr(void);

void setup() {
  //-----setpin
  pinMode(vcc1,OUTPUT);pinMode(vcc2,OUTPUT);pinMode(vcc3,OUTPUT);
  digitalWrite(vcc1,HIGH);
  digitalWrite(vcc2,HIGH);
  digitalWrite(vcc3,HIGH);
  Serial.begin(9600);
  Serial1.begin(38400);
  Timer1.initialize(5000000);         // set timer=1000000 us = 1s 
  Timer1.attachInterrupt(fTimerIsr);  // attach ISR here 
  //------------

  //fTestOpen();
  fRelayOpen();
}

void loop() {


  
  
  schZone = true;
  //fTestRun();
getsec();
getTemp();
 //Serial.println(check);
 fRelayRun();
    
 Serial.println(SumFloat() );
  isString_Float();





    
}

void fTimerIsr(void) {

  schZone = false;
  //fTestRun();
  fRelayRun();
}



