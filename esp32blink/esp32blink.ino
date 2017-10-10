const int led1 = 21;
const int led2 = 22;
const int led3 = 19;
const int led4 = 23;
const int led5 = 18;

void setup() {
  // put your setup code here, to run once:
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  pinMode (led4, OUTPUT);
  pinMode (led5, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (led1, HIGH);  // turn on the LED
  digitalWrite (led2, HIGH);  // turn on the LED
  digitalWrite (led3, HIGH);  // turn on the LED
  digitalWrite (led4, HIGH);  // turn on the LED
  digitalWrite (led5, HIGH);  // turn on the LED
  delay(500); // wait for half a second or 500 milliseconds
  digitalWrite (led1, LOW); // turn off the LED
  digitalWrite (led2, LOW); // turn off the LED
  digitalWrite (led3, LOW); // turn off the LED
  digitalWrite (led4, LOW); // turn off the LED
  digitalWrite (led5, LOW); // turn off the LED
  delay(500); // wait for half a second or 500 milliseconds
}
