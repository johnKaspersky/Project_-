// Traffic light module
// D11 -> Red LED, D10 -> Yellow LED, D9 -> Green LED
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>
#define Relay 9
#define TimeOn 10
Time getT;
tFloat temp=0,humi=0;
tString str,check;
DS1302 rtc(8, 7, 6);
DHT dht(DHTPIN, DHTTYPE);
typedef struct {
  tByte   state;
  tByte   cntOn;
  tByte   cnt;
} tRelay;

tRelay  m_Relay;
//---------------------------functions----------------------------
tFloat getTemp(void){
temp = dht.readTemperature();
humi = dht.readHumidity();
  if(isnan(temp)||isnan(humi)){
   Serial.println("DHT faild to read.......");
    }else{
     Serial.println("DHT to start");
     Serial.println(temp);
      Serial.println(humi);
      }
     return temp,humi;
 }
tString getsec(void){
  getT = rtc.getTime();
  str=rtc.getTimeStr();
  check=getT.sec;
 //check=getT.min;
 //check=getT.hour;
  Serial.println(getT.sec, DEC);
  //erial.println("s");
  return check;
}
//- State Machine ----------------------------------
//--relay off
tByte fRelayState100(tRelay *m) {

   digitalWrite(Relay,HIGH);
    if (check=="10"||check=="30"||check=="50") {
    m->cnt=0;
    m->state=101;
    } 
    if(temp>27){
      m->cnt=0;
      m->state=102;
    }else m->cnt++;
  return 0;
} 
//--relay on state 1
tByte fRelayState101(tRelay *m) {

  digitalWrite(Relay,LOW);
  if (m->cnt>m->cntOn) {
      m->cnt=0;
      m->state=100;
  } else m->cnt++;    
  return 0;
}
//--relay on state 2
tByte fRelayState102(tRelay *m){
  //--relay addjust 
  digitalWrite(Relay,LOW);
  if (m->cnt>m->cntOn)
  {   if(temp<27){
      m->cnt=0;
      m->state=100;}
  } else m->cnt++;    
  return 0;
  }

tByte fRelayEntry(tRelay *m) {

  if (schZone) { // running in normal scheduling
    
  } else {       // running in timer scheduling
    switch (m->state) {
      case 100 : fRelayState100(m); break;
      case 101 : fRelayState101(m); break;
      case 102 : fRelayState102(m); break;
      default : break;
    }
  }
  return 0;
}

//--------------------------------------------------

tByte fRelayOpen(void) {
   
  //- Set 3 outputs
  pinMode(Relay,OUTPUT);
  //- Set delay time
  digitalWrite(Relay,LOW);
  m_Relay.cntOn=TimeOn;
  m_Relay.cnt=0;
  //-------------------------
  m_Relay.state=100;

  return 0;
}

void fRelayRun(void) {

  fRelayEntry(&m_Relay);
}
