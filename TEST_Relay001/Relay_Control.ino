String timeSet[20];
char inchar =-1;
byte index=0;
String SetMode;
byte fRelayState0(){
   relay_2_on();
   if(temp<30){
    m_relay.state = 1;
    }
}
byte fRelayState1(){
   relay_2_off();
}
byte fRelayState100(){
  //relay on
  unsigned long time1 = millis()/1000;
  unsigned long  timeset = 10;//settime delay sec
   relay_1_on(); //relay 1 on
   if(time1>timeset){
     m_relay.cnt =0;
     m_relay.state =101;
  }
}
byte fRelayState101(){
    relay_1_off(); //relay 1 off
}
void setTimeDelay(byte t){
  
}
String setRelayWork(String h,String m,String s){
  ////00.00.00
      return h+'.'+m+'.'+s;
}
void getString(){
  while(Serial.available()>0){
    delay(5);
    inchar =Serial.read();
    timeSet[index]=inchar;
    index++;
    timeSet[index]= ' \0';
    }
  }
void Settime(){  
}
byte entery(){
  if(schoZone==true){
    //----
      }else if(schoZone==false){
          switch(m_relay.state){
            case 100 : fRelayState100();break;
            case 101 : fRelayState101();break;
            default : break;
         }
      }
     if(schoOne==true){
      //----
      }else if(schoOne==false){
           switch(m_relay.state){
            case 0 : fRelayState0();break;
            case 1 : fRelayState1();break;
            default : break;
           }
         }
    return 0;
  }
byte checkTime(){
//  if(){
//    schoZone =false;
//    m_relay.state=100;
//    }
  }
byte setMode(){
  m_relay.state=101;
  m_relay.cntOn=TimeOn;
  m_relay.cnt = 0;
 }
byte runMode(){
  entery();
  //Serial.println(m_Delay.state);
 }
// mode relay 
void relay_1_off(){
  StatusR1 = false;
  digitalWrite(RELAY1_PIN,HIGH);
}
void relay_1_on(){
  StatusR1 = true;
  digitalWrite(RELAY1_PIN,LOW);
}
void relay_2_off(){
  StatusR2 = false;
  digitalWrite(RELAY2_PIN,HIGH);
}
void relay_2_on(){
  StatusR2 = true;
  digitalWrite(RELAY2_PIN,LOW);
}
void relay_3_off(){
  StatusR3 = false;
  digitalWrite(RELAY3_PIN,HIGH);
}
void relay_3_on(){
  StatusR3 = true;
  digitalWrite(RELAY3_PIN,LOW);
}
void relay_4_off(){
  StatusR4 = false;
  digitalWrite(RELAY4_PIN,HIGH);
}
void relay_4_on(){
  StatusR1 = true;
  digitalWrite(RELAY4_PIN,LOW);
}
