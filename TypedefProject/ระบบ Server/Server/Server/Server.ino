#include <DS1302.h>
uint8_t CE_PIN = 22;
uint8_t IO_PIN = 23;
uint8_t SCLK_PIN = 24;
Time t;
DS1302  rtc(CE_PIN, IO_PIN, SCLK_PIN);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {            // เซ็ตเวลาของระบบ
  String Timer_day;
  String Timer_hour;
  String Timer_min;
  String Timer_sec;
  String Timer_hour_min_sec;
  String  TimerUse;
} SETDATA;
SETDATA Setdata = { " ", " ", " ", " ", " "}; // Set อีกครั้งตอนได้ Function มา

void Timer() {   // กำหนดเวลาให้ระบบ
  t = rtc.getTime();
  Setdata.Timer_day = rtc.getDateStr();
  Setdata.Timer_hour_min_sec = rtc.getTimeStr();
  Setdata.Timer_hour = t.hour;
  Setdata.Timer_min = t.min;
  Setdata.Timer_sec = t.sec;
  Setdata.TimerUse =  Setdata.Timer_hour + "." + Setdata.Timer_min;

}
//////////////////////////////////////////////////////////////////////////////////////
// Test send data by serial2 -> to RX TX nodeMCU
//Tranfer bluetooth
void isTX(int Tx) {
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

//Tranfer  NodeMCU/////////////////////////////////////////
void nodeisTX(int Tx) {
  Serial2.write(Tx);
}
void nodeisTX(char Tx) {
  Serial2.write(Tx);
}

void nodeisTX( String str) {
  int i = 0, j = 0;
  while (str[i] != '\0') {
    Serial2.write(str[i]);

    i++;

  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {    // เรียกใช้แบบ Status.DHT1 = true
  boolean PinBluetooth;
  boolean Bluetooth;
} STATUS;
STATUS Status = {false, false};

//Check PinState and Check TX//RX
boolean isConnection() {
  Status.PinBluetooth = digitalRead(2);
  if (Status.PinBluetooth ) {
    //  Serial.println(" Connection Sucefull ");
    return true;
  }

  else  {
    // Serial.println(" Connection Error ");
    return  false;
  }
}

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
  // isconection = 1
  //  Serial.println(" Connection Sucefull ");
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
  //Serial.println(cRX);
  if (cRX == 'B') {

    return true;

  }
  else {
    return false;
  }

}
boolean checkbluetooth() { // Check Connection Complete
  if (isConnection() && CheckTxRx_()) {
    Status.Bluetooth = true;
    return true;
  }
  else {
    Status.Bluetooth = false;
    return false;
  }
}
int isRX() {
  int Rx = 0;
  if (Serial1.available()) {
    Rx = Serial1.read();
    return Rx;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  //--serial set
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  nodeisTX('A');
  delay(1000);

}
