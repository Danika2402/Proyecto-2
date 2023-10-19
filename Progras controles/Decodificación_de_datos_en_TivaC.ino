#define pino1 28
#define pino2 29
#define pino3 30

char datox = 0;
char datoy = 0;
char datob = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pino1, INPUT);
  pinMode(pino2, INPUT);
  pinMode(pino3, INPUT);

}
/*int mapValues(int value, bool reverse)
{
  if (value >= 2200){
    value = map(value, 2200, 4095, 127, 254);
  }
  else if (value <= 1800){
    value = (value == 0 ? 0 : map(value, 1800, 0, 127, 0));  
  }
  else{
    value = 127;
  }

  if (reverse){
    value = 254 - value;
  }
  //Serial.println(value);  
  return value;
}*/

void loop() {
  datox = analogRead(pino1);
  datoy = analogRead(pino2);
  datob = digitalRead(pino3);
  delay(350);
  Serial.print("x: ");
  Serial.println(datox);
  Serial.print("Y: ");
  Serial.println(datoy);
  Serial.print("Boton: ");
  Serial.println(datob);
  
}
