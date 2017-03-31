#include <DS1302.h>
uint8_t CE_PIN = 24;
uint8_t IO_PIN = 23;
uint8_t SCLK_PIN = 22;
Time t;
DS1302  rtc(CE_PIN, IO_PIN, SCLK_PIN);
//DHT
void Timer() {   // กำหนดเวลาให้ระบบ
  t = rtc.getTime();
  Setdata.Timer_day = rtc.getDateStr();
  Setdata.Timer_hour_min_sec = rtc.getTimeStr();
  Setdata.Timer_hour = t.hour;
  Setdata.Timer_min = t.min;
  Setdata.Timer_sec = t.sec;
  Setdata.TimerUse =  Setdata.Timer_hour + "." + Setdata.Timer_min;

}
void SetTIME(){
  //--set mode time
  rtc.halt(false);
  rtc.writeProtect(false);
}
