#include "MPublic.h"
#include <TimerOne.h>
#include "Relay.h"

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
  Timer1.initialize(1000000);         // set timer=1000000 us = 1s 
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
  fRelayRun();
}

void fTimerIsr(void) {

  schZone = false;
  //fTestRun();
  fRelayRun();
}



