/*  Power by Mr. Pornchai Thong-in */
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

void setup()
{
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);  // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); //while OLED is running, must set GPIO16 to high 
  Wire.begin(4, 15);	//Wire.begin(4,15); (4 = SDA 15 SCL)
  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(0,0);              // Set cursor position, start of line 0
  oled.putString("VEC SMART FARM");
  oled.setTextXY(1,0);              // Set cursor position, start of line 1
  oled.putString("IOT VEC Training");
  oled.setTextXY(2,0);              // Set cursor position, start of line 2
  oled.putString("Power by SMART GROUP");
}

void loop()
{
}
