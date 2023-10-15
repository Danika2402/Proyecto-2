
int p = 0;
String data;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200); 
}

void loop() {
  if(Serial.available()>0){
    data = Serial.read();          
  }
  Serial.print(data);           
}
