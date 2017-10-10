const int fan = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(fan,OUTPUT );

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(fan, HIGH);
  delay(500);
  digitalWrite(fan, LOW);
  delay(500);
}
