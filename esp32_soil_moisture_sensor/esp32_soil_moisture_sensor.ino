#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

const int soil_sensor1 = 36;  // Analog input pin that the soil moisture sensor is attached to
const int soil_sensor2 = 27;
const int soil_sensor3 = 26;
const int soil_sensor4 = 39;
int sensorValue1 = 0;         // store sensor input value
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);  // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); //while OLED is running, must set GPIO16 to high 
  Wire.begin(4, 15);  //Wire.begin(4,15); (4 = SDA 15 SCL)
  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(0,0);              // Set cursor position, start of line 0
  oled.putString("VEC SMART FARM");
  oled.setTextXY(1,0);              // Set cursor position, start of line 1
  oled.putString("IOT VEC Training");
  oled.setTextXY(2,0);              // Set cursor position, start of line 2
  oled.putString("Power by SMART GROUP");
}


void loop() {
  // read the sensor:
  sensorValue1 = analogRead(soil_sensor1);  
  sensorValue2 = analogRead(soil_sensor2);
  sensorValue3 = analogRead(soil_sensor3);
  sensorValue4 = analogRead(soil_sensor4);          
  
  // print the sensor results to the serial monitor:
  Serial.print("Moisture Value1 = " );                       
  Serial.println(sensorValue1);  
  oled.setTextXY(0,1);              // Set cursor position, start of line 0
  oled.putString("soil1 : ");
  oled.setTextXY(8,1);              // Set cursor position, start of line 1   
  oled.putNumber(sensorValue1); 
  Serial.print("Moisture Value2 = " );                       
  Serial.println(sensorValue2);  
  oled.setTextXY(0,2);              // Set cursor position, start of line 0
  oled.putString("soil2 : ");
  oled.setTextXY(8,2);              // Set cursor position, start of line 1   
  oled.putNumber(sensorValue2);     
  Serial.print("Moisture Value3 = " );  
  Serial.println(sensorValue3); 
  oled.setTextXY(0,3);              // Set cursor position, start of line 0
  oled.putString("soil1 : ");
  oled.setTextXY(8,3);              // Set cursor position, start of line 1   
  oled.putNumber(sensorValue3);                      
  Serial.print("Moisture Value4 = " );                       
  Serial.println(sensorValue4);     
  oled.setTextXY(0,4);              // Set cursor position, start of line 0
  oled.putString("soil1 : ");
  oled.setTextXY(8,4);              // Set cursor position, start of line 1   
  oled.putNumber(sensorValue4); 

  // delay of one second
  delay(1000);                     
}
