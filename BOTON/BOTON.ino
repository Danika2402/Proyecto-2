
#define VALORX PE_2
#define VALORY PE_3
#define BOTON PF_1

int datox = 0;
int datoy = 0;
int datob = 0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  pinMode(VALORX, INPUT);
  pinMode(VALORY, INPUT);
  pinMode(BOTON, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly: 
  datox = analogRead(VALORX);
  datoy = analogRead(VALORY);
  datob = digitalRead(BOTON);
  delay(50);
    
  Serial.println(datox);
  Serial.println(datoy);
  Serial.println(datob);
}
