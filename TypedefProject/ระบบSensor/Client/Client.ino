#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "DHT.h"
#define DHT1_PIN 26
#define DHT2_PIN 27
#define DHT3_PIN 28
#define DHTTYPE DHT22
DHT dht1(DHT1_PIN, DHTTYPE);
DHT dht2(DHT2_PIN, DHTTYPE);
DHT dht3(DHT3_PIN, DHTTYPE);
//Realy
#define REALY1 30
#define REALY2 31
#define REALY3 32
#define REALY4 33
//Value Static
char ch = ' ';


typedef struct { // GET DATA Send to isTX
  float TDHT1;
  float TDHT2;
  float TDHT3;
  float HDHT1;
  float HDHT2;
  float HDHT3;
  float T_ALLDHT;  // sum of ALL T DHT
  float H_ALLDHT;  // sum of ALL  H DHT
   float volt;
   int DHT_Count;
  String SumData;
} GETDATA;
GETDATA  Getdata = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0,0, "0.0"};
typedef struct {            // เซ็ตเวลาของระบบ
  String Timer_day;
  String Timer_hour;
  String Timer_min;
  String Timer_sec;
  String Timer_hour_min_sec;
  String  TimerUse;
} SETDATA;
SETDATA Setdata = { " ", " ", " ", " ", " "}; // Set อีกครั้งตอนได้ Function มา

typedef struct {            //ใช้เช็ตเวลาเปิด / ปิด
  String Time_ON1;  // ดีฟอลต์  ON1-OFF3
  String Time_ON2;
  String Time_ON3;
  String Time_ON_OFF[10];     // แบบเซ็ตลงมาจากโหนด  เซ็ตได้  มากถึง20 เปิด 10 ปิด 10
  String str[10];
} RECEIVE ;
RECEIVE receive = { "8.00", "12.00 ", "17.00"};


//Trydef Status

typedef struct {    // เรียกใช้แบบ Status.DHT1 = true
  boolean nodeMCU;
  boolean DHT1;
  boolean DHT2;
  boolean DHT3;
  boolean Realy1;//ปั้ม
  boolean Realy2;//พัดลม
  boolean Realy3;
  boolean Realy4;
} STATUS;
STATUS Status = {false, false, false, false, false, false, false, false};
//Check PinState and Check TX//RX
// เทสการส่งดาต้า
// 'A' = ส่งข้อมูล
// 'B' = รับข้อมูล
// 'C' =  ยืนยัน
boolean CheckTxRx_() {
  int iTX = 0;
  int iRX = 0;
  char cTX = ' ';
  char cRX = ' ';
  int i = 256;
  isTX('A');
  delay(10);
  cRX = isRX();
  while (cRX != 'B' && i) {
    cRX = isRX();
    i--;
  }
  delay(10);
  isTX('C');
  delay(10);
  if (cRX == 'B') {
    Status.nodeMCU = true;
    return true;
  }
  else {
    Status.nodeMCU = false;
    return false;
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Get DATA
void ADHT1() {
  delay(200);
  float h = dht1.readHumidity();
  float t = dht1.readTemperature();
  float f = dht1.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Status.DHT1 = false;
    Getdata.TDHT1 =  0.0;
    Getdata.HDHT1 =   0.0;
  }

  else
  {
    Getdata.TDHT1 =  t;
    Getdata.HDHT1 =   h;
    Status.DHT1 = true;


  }

}
void ADHT2() {
  delay(200);
  float h = dht2.readHumidity();
  float t = dht2.readTemperature();
  float f = dht2.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Status.DHT2 = false;
    Getdata.TDHT2 =  0.0;
    Getdata.HDHT2 =   0.0;
  }
  else
  {
    Status.DHT2 = true;
    Getdata.TDHT2 =  t;
    Getdata.HDHT2 =   h;
  }
}
void ADHT3() {
  delay(200);
  float h = dht3.readHumidity();
  float t = dht3.readTemperature();
  float f = dht3.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Getdata.TDHT3 =  0.0;
    Getdata.HDHT3 =   0.0;
    Status.DHT3 = false;


  }

  else
  {
    Getdata.TDHT3 =  t;
    Getdata.HDHT3 =   h;
    Status.DHT3 = true;
  }
}

void SumData() {
  Getdata.SumData = " " ;
  Getdata.SumData = String(Getdata.TDHT1) + ":" + String(Getdata.HDHT1) + ":" + String(Getdata.TDHT2) + ":" +
                    String(Getdata.HDHT2) + ":" + String(Getdata.TDHT3) + ":" + String(Getdata.HDHT3) + ":" + String(Status.Realy1) + ":"
                    + String(Status.Realy2) + ":" + String(Status.Realy3) + ":" + String(Status.Realy4) + ":" + String(Getdata.volt);
}
void getALLDHT() {
  float T_DHT = 0.0;
  float H_DHT = 0.0;
 int  count  = 0;
  if(Status.DHT1&&Status.DHT2&&Status.DHT3){
   T_DHT = Getdata.TDHT1+Getdata.TDHT2+Getdata.TDHT3;
  count = 3;
   }
   else if(Status.DHT1&&Status.DHT2){
     T_DHT = Getdata.TDHT1+Getdata.TDHT2;
      count = 2;
   }
   else if(Status.DHT1&&Status.DHT3){
         T_DHT = Getdata.TDHT1+Getdata.TDHT3;
        count = 2;
   }
      else if(Status.DHT2&&Status.DHT3){
         T_DHT = Getdata.TDHT2+Getdata.TDHT3;
        count = 2;
      }
      else  {
        T_DHT = Getdata.TDHT1+Getdata.TDHT2+Getdata.TDHT3;
        if(Status.DHT1||Status.DHT2||Status.DHT3)
         count = 1;
         else 
            count = 0;
      }


      Getdata.T_ALLDHT = (T_DHT/count);
       Getdata.T_ALLDHT = (H_DHT/count);
       Getdata.DHT_Count = count;
      
      
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Tranfer to TX nodeMCU

void isTX(int Tx) {
  Serial1.write(Tx);
}
void isTX(long Tx) {
  Serial1.write(Tx);
}
void isTX(char Tx) {
  Serial1.write(Tx);
}
void isTX( String str) {
  int i = 0, j = 0;
  while (str[i] != '\0') {
    Serial1.write(str[i]);

    i++;

  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void SetTime_ON_OFF() {
  int i = 0;
  while (receive.str[i] != '\0') {
    receive.Time_ON_OFF[i] = receive.str[i];
  }

}

int isRX() {
  int Rx = 0;
  if (Serial1.available()) {
    Rx = Serial1.read();
    return Rx;
  }
}
void String_(char abc) {   // ส่งดาต้ามาในรูปแบบ  String On1 = 21.10  off 1 = 21.15  Str = 21.10:21.15
  String S[5]; //array string for data
  int i = 0;
  while (ch != 'X') {
    if (ch != '.') //check dif value
      S[i] +=  ch;
    else
      i++; //increase i
    ch = isRX();
  }
  delay(2000);
  for (int i = 0; i < 5; i++) {
    receive.str[i] =  S[i]; // โยนค่าจาก ที่แยกเป็นแต่ละตัวได้ เก็บไว้ใน Typedef เอาไว้เซ็ตเวลา
    //  Serial.println(dataRec[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function Control
boolean Check_TimerOn_Pump() {
  if (receive.Time_ON1 == Setdata.TimerUse || receive.Time_ON2 == Setdata.TimerUse || receive.Time_ON3 == Setdata.TimerUse) {
    return true;
  }
  else {
    return false;
  }
}
void Pump_ON() {
  delay(10);
  Realy1_ON();//

}
void FAN_ON() {
  delay(10);
  Realy2_ON();//

}

void Pump_OFF() {
  delay(10);
  Realy2_OFF();//

}

void FAN_OFF() {
  delay(10);
  Realy2_ON();//

}

void Realy1_ON() {
  digitalWrite(REALY1, HIGH);
  delay(10);

}
void Realy1_OFF() {
  digitalWrite(REALY1, LOW);

}
void Realy2_ON() {
  digitalWrite(REALY2, HIGH);
  delay(10);

}
void Realy2_OFF() {
  digitalWrite(REALY2, LOW);

}
void Realy3_ON() {
  digitalWrite(REALY3, HIGH);
  delay(10);

}
void Realy3_OFF() {
  digitalWrite(REALY3, LOW);

}
void Realy4_ON() {
  digitalWrite(REALY4, HIGH);
  delay(10);

}
void Realy4_OFF() {
  digitalWrite(REALY4, LOW);

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mode_Offline(){
  Timer();
  delay(20);
  if(Check_TimerOn_Pump()){
    if(receive.str[0]!='\0'){
      SetTime_ON_OFF();
      
      
    }
    
  }
  
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  //--serial set
  Serial.begin(9600);
  Serial1.begin(9600);
  SetTIME();
  //--DHT set
  dht1.begin();
  dht2.begin();
  dht3.begin();
  //Serial.println("Time statr..");
  lcd.begin();
}
void loop() {
  // รันเวลาขึ้นก่อนเริ่มโปรแกรมใดๆ
  Timer();
  

  
  delay(1000);
}











