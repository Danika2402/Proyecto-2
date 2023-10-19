#include <SoftwareSerial.h>
SoftwareSerial SerialESP8266(PD_6,PD_7); // RX,TX

char data;

void setup(){
  Serial.begin(115200);
  SerialESP8266.begin(115200);
  }

void loop(){
  checkSerialCom();
  delay(350);  
}

void checkSerialCom(){
  if(SerialESP8266.available() > 0){
    Serial.println("Recibido ");
    while(SerialESP8266.available()>0){
      data = SerialESP8266.read();
      Serial.println(data);
    }
  }
}
