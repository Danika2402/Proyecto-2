#include <esp_now.h>
#include <WiFi.h>

#include <ezButton.h>

// definiendo los pines para cambio de posicion
#define VRX_PIN  36 // ESP32 pin GPIO36 (ADC0) connected to VRX pin
#define VRY_PIN  39 // ESP32 pin GPIO39 (ADC0) connected to VRY pin
#define SW_PIN   33 // ESP32 pin GPIO17 connected to SW  pin

int valueX = 0; // to store the X-axis value
    int valueY = 0; // to store the Y-axis value
    int bValue = 0; // To store value of the button 
ezButton button(SW_PIN);

// REPLACE WITH THE RECEIVER'S MAC Address
uint8_t broadcastAddress[] = {0x30, 0x83, 0x98, 0xA2, 0x00, 0x4A};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
    int valueX = 0; // to store the X-axis value
    int valueY = 0; // to store the Y-axis value
    int bValue = 0; // To store value of the button
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  button.setDebounceTime(50);         // set debounce time to 50 milliseconds

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  button.loop(); // MUST call the loop() function first
  
  // Set values to send
  //myData.id = 1;
  myData.valueX = analogRead(VRX_PIN);
  myData.valueY = analogRead(VRY_PIN);
  myData.bValue = digitalRead(SW_PIN);
  
  // Read the button value
  bValue = button.getState();
  if (button.isPressed()) {
    Serial.println("The button is pressed");  // TODO do something here
  }
  if (button.isReleased()) {
    Serial.println("The button is released");  // TODO do something here
  }

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(300);
}
