#include <DS1302.h>
// CE/RST
// I/O or data
// CLK/SCLK
uint8_t CE_PIN = 22;
uint8_t IO_PIN = 23;
uint8_t SCLK_PIN = 24;
Time t;
DS1302  rtc(CE_PIN, IO_PIN, SCLK_PIN);
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
  float Vote
} GETDATA;
GETDATA  Getdata = {0.0, 0.0, 0.0};

typedef struct {            //  ยังไม่มีระบบสั่งเปิดปิดเรียลทาร์ม
  String Timer_day;
  String Timer_hour;
  String Timer_min;
  String Timer_sec;
  String Timer_hour_min_sec;
  String Time_on; // SET DATA
  String Time_off;
} SETDATA;
SETDATA Setdata = { " ", " "," ", " "," ", "22.10.22","22.12.22"};  // Set อีกครั้งตอนได้ Function มา

void setup() {
  //--set mode time
  rtc.halt(false);
  rtc.writeProtect(false);
  //--serial set
  Serial.begin(9600);
  Serial.println("Time statr..");
}
void Timer() {
    t = rtc.getTime();
  Setdata.Timer_day = rtc.getDateStr();
  Setdata.Timer_hour_min_sec = rtc.getTimeStr();
  Setdata.Timer_hour = t.hour;
  Setdata.Timer_min = t.min;
  Setdata.Timer_sec = t.sec; 
  
}

void loop() {
// รันเวลาขึ้นก่อนเริ่มโปรแกรมไดๆ
Timer();  
//Serial.println(Setdata.Time_on); 









  delay(1000);
}



