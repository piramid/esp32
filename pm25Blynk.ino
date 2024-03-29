#define BLYNK_TEMPLATE_ID "TMPLr8OVB2sS"
#define BLYNK_DEVICE_NAME "technocom PM25"
#define BLYNK_AUTH_TOKEN "khmF7-n01UV__dzKOT_xvxygZ6lUIe6i"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "PMS.h"

PMS pms(Serial2);
PMS::DATA data;

#include <DHT.h>

#define DHTPIN 15      // pin for Dustation Devkit v2
#define DHTTYPE DHT22  // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

int32_t PM1, PM2, PM10;
float_t TEMP, HUMI;

#define RELAY 23

BLYNK_WRITE(V5) // Executes when the value of virtual pin 0 changes
{
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(RELAY,HIGH);  // Set digital pin 23 HIGH
  }
  else
  {
    // execute this code if the switch widget is now OFF
    digitalWrite(RELAY,LOW);  // Set digital pin 23 LOW    
  }
}

#define OLED_RESET -1

// this is the bitmap, change this variable for your specification.
const unsigned char myBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xbf, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xc1, 0xf8, 0x7f, 0x0f, 0xfc, 
  0x3f, 0xfe, 0x3f, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xf8, 0x0f, 0x00, 0x78, 0x3e, 0x0f, 0xfc, 
  0x3f, 0xfe, 0x3f, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xf1, 0xfe, 0x1c, 0x38, 0x3e, 0x0f, 0xfc, 
  0x3f, 0xf8, 0x0f, 0x0f, 0xc1, 0x88, 0xf1, 0x0f, 0xc3, 0xe3, 0xfc, 0x3e, 0x38, 0x3c, 0x0f, 0xfc, 
  0x3f, 0xf8, 0x0c, 0x07, 0x81, 0x80, 0x70, 0x07, 0x00, 0xe3, 0xfc, 0x7e, 0x39, 0x1c, 0x8f, 0xfc, 
  0x3f, 0xfe, 0x3c, 0x63, 0x1d, 0x8c, 0x31, 0xc6, 0x38, 0xc7, 0xfc, 0x7e, 0x19, 0x1c, 0x8f, 0xfc, 
  0x3f, 0xfe, 0x38, 0xf2, 0x3f, 0x8e, 0x31, 0xc6, 0x3c, 0x47, 0xfc, 0x7f, 0x19, 0x98, 0x8f, 0xfc, 
  0x3f, 0xfe, 0x38, 0x02, 0x3f, 0x8e, 0x31, 0xc6, 0x3c, 0x47, 0xfc, 0x7f, 0x19, 0x89, 0x8f, 0xfc, 
  0x3f, 0xfe, 0x38, 0x02, 0x3f, 0x8e, 0x31, 0xc6, 0x3c, 0x43, 0xfc, 0x7e, 0x39, 0x89, 0x8f, 0xfc, 
  0x3f, 0xfe, 0x38, 0xfe, 0x3f, 0x8e, 0x31, 0xc6, 0x3c, 0x63, 0xfc, 0x3e, 0x39, 0xc1, 0x8f, 0xfc, 
  0x3f, 0xfe, 0x3c, 0x7f, 0x1d, 0x8e, 0x31, 0xc6, 0x38, 0xe1, 0xfe, 0x1c, 0x79, 0xc3, 0x8f, 0xfc, 
  0x3f, 0xfe, 0x0c, 0x07, 0x01, 0x8e, 0x31, 0xc7, 0x00, 0xf0, 0x0f, 0x00, 0x79, 0xc3, 0x8f, 0xfc, 
  0x3f, 0xff, 0x0f, 0x07, 0xc1, 0x8e, 0x31, 0xc7, 0x83, 0xfc, 0x0f, 0xc1, 0xf9, 0xe3, 0x8f, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 
  0x3f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

Adafruit_SSD1306 display(OLED_RESET);

#define SSD130_MODLE_TYPE   1   // 0 : GEOMETRY_128_64  // 1: GEOMETRY_128_32

// Your WiFi ssid and password
char ssid[] = "Tc";
char password[] = "aaaaabbbbb";

int state;
int pinValue;

void myTimerEvent()
{
  dht.begin();
  PM1 = data.PM_AE_UG_1_0;
  PM2 = data.PM_AE_UG_2_5;
  PM10 = data.PM_AE_UG_10_0;
  TEMP = dht.readTemperature();
  HUMI = dht.readHumidity();

  Blynk.virtualWrite(V0, PM2);
  Blynk.virtualWrite(V1, PM1);
  Blynk.virtualWrite(V2, PM10);
  Blynk.virtualWrite(V3, TEMP);
  Blynk.virtualWrite(V4, HUMI);
}

BLYNK_WRITE(V6) // Executes when the value of virtual pin 0 changes
{
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    state = 1;
  }
  else
  {
    // execute this code if the switch widget is now OFF
    state = 0;  
  }
}

BLYNK_WRITE(V7)
{
  pinValue = param.asInt(); // assigning incoming value from pin V7 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
//  Serial.print("V7 Slider value is: ");
//  Serial.println(pinValue);
}


void dhtLoop(void) {
  // read temperature and humidity

  TEMP = dht.readTemperature();
  HUMI = dht.readHumidity();

  if (isnan(TEMP) || isnan(HUMI)) {
    Serial.println("AM2302 Failed");
  }

  Serial.print("Temp:");
  Serial.println(TEMP);
  Serial.print("Humid:");
  Serial.println(HUMI);
  showTemp(TEMP, HUMI, data.PM_AE_UG_2_5);
}

void readpm(){
  if (pms.read(data))
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();
  }
}

void showTemp(float temp,float hud, float pm25) {
// text display tests
  //display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("** Manual Mode **");
  display.print("T : ");
  display.print(temp);
  display.println(" C");
  display.print("H : ");
  display.print(hud);
  display.println(" %");
  display.print("PM 2.5 : ");
  display.print(data.PM_AE_UG_2_5);
  display.println(" ug/m3");
  display.display();
  display.clearDisplay();
}

void showAuto(float temp,float hud, float pm25) {
// text display tests
  //display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("*** Auto Mode ***");
  display.print("T : ");
  display.print(temp);
  display.println(" C");
  display.print("H : ");
  display.print(hud);
  display.println(" %");
  display.print("PM 2.5 : ");
  display.print(data.PM_AE_UG_2_5);
  display.println(" ug/m3");
  display.display();
  display.clearDisplay();
}

void automode(int s, int pin){
  if(s == 1){
    showAuto(TEMP, HUMI, data.PM_AE_UG_2_5);
    int pm25;
    Serial.println("state =");
    Serial.println(s);
    pm25 = data.PM_AE_UG_2_5;
    Serial.println(pm25);
    Serial.println(TEMP);
    Serial.print("V7 Slider value is: ");
    Serial.println(pin);
  
      if(pm25 > pin){
        digitalWrite(RELAY,HIGH);
        Blynk.virtualWrite(V5, 1);
      }else{
        digitalWrite(RELAY,LOW);
        Blynk.virtualWrite(V5, 0);
      }       
   }else
   {
     Serial.print("state =");
     Serial.println(s);
     loop();
   }
}

void setup() {
  Serial2.begin(9600);   // GPIO1, GPIO3 (TX/RX pin on ESP-12E Development Board)
  Serial.begin(9600);  // GPIO2 (D4 pin on ESP-12E Development Board)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
  display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด

  display.drawBitmap(0, 0, myBitmap, 128, 32, WHITE);
  display.display();
  delay(4000);
  display.clearDisplay();
  
  PM1 = 0;
  PM2 = 0;
  PM10 = 0;
  TEMP = 0;
  HUMI = 0;
  pinMode(RELAY, OUTPUT);
  Blynk.begin(auth, ssid, password);
  Blynk.virtualWrite(V5, 0);
  Blynk.virtualWrite(V6, 0);
  timer.setInterval(5000L, myTimerEvent);
}

void loop() {
  readpm();
  if (state == 1){
    automode(state, pinValue);
  }else{  
    dhtLoop();
  }
 Blynk.run();  
 timer.run(); 
}
