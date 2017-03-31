#include <ESP8266WiFi.h>
#include <time.h>
#include <FirebaseArduino.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"

ClosedCube_HDC1080 hdc1080;

// Set these to run example.
#define FIREBASE_HOST "test-ce9c3.firebaseio.com"
#define FIREBASE_AUTH "qQj5gkADsPzuY4fxeIsAtW1WxTPNbu4SmO5WMedX"

const char* ssid = "Ollydbg";                  //ใส่ชื่อ SSID Wifi
const char* password = "11223344";          //ใส่รหัสผ่าน

int timezone = 7 * 3600;                    //ตั้งค่า TimeZone ตามเวลาประเทศไทย
int dst = 0;                                //กำหนดค่า Date Swing Time

const String deviceNumber = "DataLogger/TempNode1/24-03-2017";
//struct tm {
//   int tm_sec;         /* วินาที,  range 0 to 59          */
//   int tm_min;         /* นาที, range 0 to 59           */
//   int tm_hour;        /* ชั่วโมง, range 0 to 23             */
//   int tm_mday;        /* วันที่, range 1 to 31  */
//   int tm_mon;         /* เดือน, range 0 to 11             */
//   int tm_year;        /* ปีคริสศักราช ตั้งแต่ 1900   */
//   int tm_wday;        /* วัน, range 0 to 6    */
//   int tm_yday;        /* วันใน 1 ปี, range 0 to 365  */
//   int tm_isdst;       /* daylight saving time             */
//};

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  hdc1080.begin(0x40);
  WiFi.mode(WIFI_STA);                                        //เชื่อมต่อ Wifi
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(",");
    delay(1000);
  }
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");     //ดึงเวลาจาก Server
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  int dataget = Firebase.getInt("setting/LoggerTime");
  
  Firebase.setFloat("Device/Humidity/Node1",hdc1080.readHumidity());
  Firebase.setInt("Device/Humidity/Node2",hdc1080.readHumidity());
  Firebase.setInt("Device/Humidity/Node3",hdc1080.readHumidity());
  Firebase.setFloat("Device/Temp/Node1",hdc1080.readTemperature());
    Firebase.setFloat("Device/Temp/Node2",hdc1080.readTemperature());
      Firebase.setFloat("Device/Temp/Node3",hdc1080.readTemperature());
  //Serial.println(hdc1080.readTemperature());
  /*if ((p_tm->tm_min) % dataget == 0) {
    int randNumber = random(10, 500);
    Firebase.setInt(deviceNumber + "/" + p_tm->tm_hour + ":" + p_tm->tm_min, randNumber);
    Serial.println(dataget);
  }*/

  delay(500);
}

