#include <Wire.h>
#include <MicroGear.h>
#include "WiFi.h"
#include <U8x8lib.h>
#include <ACROBOTIC_SSD1306.h>
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11


#define dht_dpin 14
DHT dht(dht_dpin, DHTTYPE); 

// the OLED used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

const int soil_sensor1 = 36;  // Analog input pin that the soil moisture sensor is attached to
const int soil_sensor2 = 27;
const int soil_sensor3 = 26;
const int soil_sensor4 = 39;
const int fan = 5;

const int vav1 = 21;
const int vav2 = 22;
const int vav3 = 19;
const int vav4 = 23;
const int pump = 18;

int sensorValue1 = 0;         // store sensor input value
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;

float h;
float t;

const char* ssid     = "tom";
const char* password = "aaaaabbbb1";

WiFiClient client;

int timer = 0;
char str[32];
MicroGear microgear(client);

/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
      msg[msglen] = '\0';

      char strState[msglen];
      for (int i = 0; i < msglen; i++) 
      {
        strState[i] = (char)msg[i];
        Serial.print((char)msg[i]);
      }
     
      Serial.println();
    
      String stateStr = String(strState).substring(0, msglen);

    if (stateStr == "SW1ON") 
      {
       Serial.println("SW1 On");
         digitalWrite(ledPin1, LOW);
          microgear.chat("sw1", "ON"); 
      }      
      else if (stateStr == "SW1OFF") 
      {
        digitalWrite(ledPin1, HIGH);
        microgear.chat("sw1", "OFF");       
      }

     if (stateStr == "SW2ON") 
      {
       Serial.println("SW2 On");
         digitalWrite(ledPin2, LOW);
          microgear.chat("sw2", "ON"); 
      }      
      else if (stateStr == "SW2OFF") 
      {
        digitalWrite(ledPin2, HIGH);
        microgear.chat("sw2", "OFF");       
      }

     if (stateStr == "SW3ON") 
      {
       Serial.println("SW3 On");
         digitalWrite(ledPin3, LOW);
          microgear.chat("sw3", "ON"); 
      }      
      else if (stateStr == "SW3OFF") 
      {
        digitalWrite(ledPin3, HIGH);
        microgear.chat("sw3", "OFF");       
      }

     if (stateStr == "SW4ON") 
      {
       Serial.println("SW4 On");
         digitalWrite(ledPin4, LOW);
          microgear.chat("sw4", "ON"); 
      }      
      else if (stateStr == "SW4OFF") 
      {
        digitalWrite(ledPin4, HIGH);
        microgear.chat("sw4", "OFF");       
      }
      
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}


void vav1On(){
  digitalWrite(vav1,HIGH);
  }


void vav2On(){
  digitalWrite(vav2,HIGH);
  }


void vav3On(){
  digitalWrite(vav3,HIGH);
  }


void vav4On(){
  digitalWrite(vav4,HIGH);
  }

void pumpOn(){
  digitalWrite(pump,HIGH);
  }

void fanOn(){
  digitalWrite(fan,LOW);
  }

void vav1Off(){
  digitalWrite(vav1,LOW);
  }


void vav2off(){
  digitalWrite(vav2,LOW);
  }


void vav3Off(){
  digitalWrite(vav3,LOW);
  }


void vav4Off(){
  digitalWrite(vav4,LOW);
  }

void pumpOff(){
  digitalWrite(pump,LOW);
  }

void fanOff(){
  digitalWrite(fan,HIGH);
  }

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200); 
  
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
    //oled.setTextXY(1,0);              // Set cursor position, start of line 1
    //oled.putString("WiFi Connecting...");
    u8x8.drawString(4, 3, "WiFi");
    u8x8.drawString(2, 4, "Connecting..");
    u8x8.clearDisplay();
  }
 
    Serial.println("Connected to the WiFi network");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    unsigned char ip = WiFi.localIP();
    Serial.println(ip);
    u8x8.drawString(1, 2, "WiFi Connected");
    //oled.setTextXY(1,0);              // Set cursor position, start of line 1
    //oled.putString("WiFi Connected");
    //oled.setTextXY(2,0);              // Set cursor position, start of line 2
    //oled.putNumber(ip);
    u8x8.setCursor(0, 6);
    u8x8.print(ip);
    delay(3000);
  
  pinMode(fan, OUTPUT);
  pinMode(13, INPUT);
  dht.begin();
  
  pinMode (vav1, OUTPUT);
  pinMode (vav2, OUTPUT);
  pinMode (vav3, OUTPUT);
  pinMode (vav4, OUTPUT);
  pinMode (pump, OUTPUT);
  
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
  delay(2000);
  oled.clearDisplay();              // Clear screen
}


void loop() {

  oled.setTextXY(0,0);              // Set cursor position, start of line 0
  oled.putString("VEC SMART FARM");
  
  // read the sensor:
  sensorValue1 = analogRead(soil_sensor1);  
  sensorValue2 = analogRead(soil_sensor2);
  sensorValue3 = analogRead(soil_sensor3);
  sensorValue4 = analogRead(soil_sensor4);          
  
  // print the sensor results to the serial monitor:
  Serial.print("Moisture Value1 = " );                       
  Serial.println(sensorValue1);  
  oled.setTextXY(1,0);              // Set cursor position, start of line 0
  oled.putString("soil1:");
  oled.setTextXY(1,6);              // Set cursor position, start of line 1   
  oled.putNumber(sensorValue1); 
  Serial.print("Moisture Value2 = " );                       
  Serial.println(sensorValue2);  
  oled.setTextXY(2,0);              // Set cursor position, start of line 0
  oled.putString("soil2:");
  oled.setTextXY(2,6);              // Set cursor position, start of line 1   
  oled.putNumber(sensorValue2);     
  Serial.print("Moisture Value3 = " );  
  Serial.println(sensorValue3); 
  oled.setTextXY(3,0);              // Set cursor position, start of line 0
  oled.putString("soil3:");
  oled.setTextXY(3,6);              // Set cursor position, start of line 1   
  oled.putNumber(sensorValue3);                      
  Serial.print("Moisture Value4 = " );                       
  Serial.println(sensorValue4);     
  oled.setTextXY(4,0);              // Set cursor position, start of line 0
  oled.putString("soil4:");
  oled.setTextXY(4,6);              // Set cursor position, start of line 1   
  oled.putNumber(sensorValue4); 

  h = dht.readHumidity();
  t = dht.readTemperature();         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    oled.setTextXY(5,0);              // Set cursor position, start of line 0
    oled.putString("Temp: ");
    oled.setTextXY(5,5);              // Set cursor position, start of line 1   
    oled.putNumber(t); 
    oled.setTextXY(6,0);              // Set cursor position, start of line 0
    oled.putString("Humid: ");
    oled.setTextXY(6,6);              // Set cursor position, start of line 1   
    oled.putNumber(h); 
//      u8x8.setCursor(0, 6);
//      u8x8.print(t);
//      u8x8.setCursor(0, 7);
//      u8x8.print(h);
      delay(2000);
  
  // delay of one second
  //delay(500);            

//  digitalWrite(fan, HIGH);
//  delay(500);
//  digitalWrite(fan, LOW);
//  delay(500);
   // decision();
}

void decision(){
  if (t>23){
      vav1On();
      vav2On();
      vav3On();
      vav4On();
      pumpOn();
      fanOn();
    }
  }
