DHT dht(DHTPIN, DHTTYPE);
float temp=0,humi=0; 
float getTemp(){
  temp = dht.readTemperature();
  humi = dht.readHumidity();
  delay(300);
  if(isnan(temp)||isnan(humi)){
    Serial.println("DHT faild to read.......");
    }else{
     Serial.println("DHT to start");
     Serial.println(temp);
     Serial.println(humi); 
     }
  return temp,humi; 
}
byte checkTemp(){
  if(temp>30){
  m_relay.state = 0;
  schoOne = false;
   }
 }
