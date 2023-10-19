#define bocina PD_0
#define SW1 PUSH1

void setup() {
  // put your setup code here, to run once:
  pinMode(SW1, INPUT_PULLUP);
  pinMode(bocina, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly: 
  if(SW1 == LOW){
    digitalWrite(bocina,HIGH);
  }else{
    digitalWrite(bocina,LOW);
  }
}
