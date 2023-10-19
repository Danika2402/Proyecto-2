#include <ESP8266WiFi.h>
#include <espnow.h>

 int valorx = 16;
 int valory = 5;
 int boton = 4;

int ValorX = 0;
int ValorY = 0;
int Boton = 0;


//Structure example to receive data
//Must match the sender structure
typedef struct test_struct {
  int valueX;
  int valueY;
  int bValue;
} test_struct;

 
void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  while(!Serial);

  Serial.println();
  
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Get Mac Add
 Serial.print("Mac Address: ");
 Serial.println(WiFi.macAddress());
 
  //Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

  //////////////////
  /////////////////
  pinMode(valorx, OUTPUT);
  pinMode(valory, OUTPUT);
  pinMode(boton, OUTPUT);
}

// MAC ADDRESS ESP8266
uint8_t myMAC[] = {0x30, 0x83, 0x98, 0xA2, 0x00, 0x4A};

test_struct myData;     //Create a struct_message called myData

//callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received:   \n");
  //Serial.println(len);
  Serial.print("x: ");
  Serial.println(myData.valueX);
  Serial.print("y: ");
  Serial.println(myData.valueY);
  //Serial.println();
  Serial.print("button: ");
  Serial.println(myData.bValue);
  Serial.println();
}

void loop() {

  ValorX = myData.valueX;
  ValorY = myData.valueY;
  Boton = myData.bValue;

/*  valorx = analogWrite(ValorX);
  valory = analogWrite(ValorY);
  boton = Boton;*/
  analogWrite(valorx, ValorX);
  analogWrite(valory, ValorY);
  digitalWrite(boton, Boton);
  delay(350);

}
