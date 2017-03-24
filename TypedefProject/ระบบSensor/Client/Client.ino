#include <DS1302.h>
// CE/RST
// I/O or data
// CLK/SCLK
uint8_t CE_PIN = 22;
uint8_t IO_PIN = 23;
uint8_t SCLK_PIN = 24;
Time t;
DS1302  rtc(CE_PIN, IO_PIN, SCLK_PIN);
float dataRec[] = {0, 0, 0, 0, 0};
char ch = ' ';
//Trydef Status

typedef struct {    // เรียกใช้แบบ Status.DHT1 = true
  boolean PinBluetooth;
  boolean DHT1;
  boolean DHT2;
  boolean DHT3;
  boolean Realy1;//ปั้ม
  boolean Realy2;//พัดลม
  boolean Realy3;
  boolean Realy4;
} STATUS;
STATUS Status = {false, false, false, false, false, false, false, false};

typedef struct {
  float DHT1; // GET DATA
  float DHT2;
  float DHT3;
  float WaterFan;
  float volt;
} GETDATA;
GETDATA  Getdata = {0.0, 0.0, 0.0};

typedef struct {            //  ยังไม่มีระบบสั่งเปิดปิดเรียลทาร์ม
  String Timer_day;
  String Timer_hour;
  String Timer_min;
  String Timer_sec;
  String Timer_hour_min_sec;
  } SETDATA;
SETDATA Setdata = { " ", " "," ", " "," "};  // Set อีกครั้งตอนได้ Function มา
//////////////////////////////////////////////////////////////////////////////////////////////////
void Timer() {   // กำหนดเวลาให้ระบบ
    t = rtc.getTime();
  Setdata.Timer_day = rtc.getDateStr();
  Setdata.Timer_hour_min_sec = rtc.getTimeStr();
  Setdata.Timer_hour = t.hour;
  Setdata.Timer_min = t.min;
  Setdata.Timer_sec = t.sec; 
  
}
/////////////////////////////////////////////////////////////////////////////////////////////////

/// Typedef ส่ง 
typedef struct {            //  รับมาจาก GET ละส่ง
  String SumDHT;
  String SumStatus;
  String volt;
  String SumData;
} TRANFER;
TRANFER Tranfer = { " ", " "," "," "};  // Set อีกครั้งตอนได้ Function มา

//////////////////////////////////////////////////////////////////////////////////////////
// Tranfer and  receive + SumData

//Tranfer
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

////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {            //  รับมาจาก GET ละส่ง
  String Time_ON1_SET;
  String Time_OFF1_SET;
   String Time_ON2_SET;
  String Time_OFF2_SET;
   String Time_ON3_SET;
  String Time_OFF3_SET;
 // String str;
 }RECEIVE ;
RECEIVE receive = { "8.00", "8.05 ","12.00","12.05","17.00","17.05"};  
int isRX() {
  int Rx = 0;
  if (Serial1.available()) {
    Rx = Serial1.read();
    return Rx;
  }
}

void String_(char abc) {
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void setup() {
  //--set mode time
  rtc.halt(false);
  rtc.writeProtect(false);
  //--serial set
  Serial.begin(9600);
  Serial.println("Time statr..");
}
void loop() {
// รันเวลาขึ้นก่อนเริ่มโปรแกรมไดๆ
Timer();  
Serial.println(Setdata.Timer_hour_min_sec); 









  delay(1000);
}











