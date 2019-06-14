#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include "json_model.h"
#include "spiffs.h"
#include "wireless_fidelity.h"

typedef struct
{
    char server[32];
    uint16_t port;
    char user[32];
    char pass[32];
} mqtt_config_json_t;

static mqtt_config_json_t mqtt_config = {0};

typedef struct
{
    char position1[32];
    char position2[32];
    char position3[32];
    char position4[32];
    char position5[32];
} position_config_json_t;

static position_config_json_t position_config = {0};


#define out_topic "/light/out"
// Replace by 2 if you aren't enable to use Serial Monitor... Don't forget to Rewire R1 to GPIO2!
#define in_led 0

#define WS2812_PIN0 4   //D2
#define WS2812_PIN1 0   //D3
//#define WS2812_PIN2 2   //D4
//#define WS2812_PIN3 15  //D8
//#define WS2812_PIN4 13  //D7
//#define WS2812_PIN5 12  //D6 

#define LED_WLAN 13 // GPIO13 oder D7 auf dem NodeMCU

#define NUMPIXELS_0 150
#define NUMPIXELS_1 150

WiFiClient espClient;
PubSubClient client;

#define PIXEL_STRIPE_COUNT 2
Adafruit_NeoPixel pixels[PIXEL_STRIPE_COUNT] =
{
    Adafruit_NeoPixel(NUMPIXELS_0, WS2812_PIN0, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS_1, WS2812_PIN1, NEO_GRB + NEO_KHZ800)
};

int ledPin = LED_WLAN;


void setup()
{
  Serial.begin(115200);
  Serial.println(";");
  Serial.println("; esp8266 boot");
  Serial.println(";");
  
  spiffs_initialize();

  wifi_initialize();

  read_json("/mqtt_config.json", &mqtt_config, sizeof(mqtt_config_json_t), mqtt_config_json_desc);
  read_json("/position_config.json", &position_config, sizeof(position_config_json_t), position_config_json_desc);


  for(int i = 0; i < PIXEL_STRIPE_COUNT; i++)
    {
          pixels[i].begin();
          pixels[i].show();
    }

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
      
    client.setClient(espClient);
    client.setServer(mqtt_config.server, mqtt_config.port);
    client.setCallback(callback);
      
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(in_led, OUTPUT);
    digitalWrite(in_led, HIGH);
  
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client", mqtt_config.user, mqtt_config.pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  int pixelstart = 0;
  int pixelend = NUMPIXELS_0;

  if(strcmp(topic, position_config.position1)==0){
    pixelstart = 0;
    pixelend = 30;
  }

  if(strcmp(topic, position_config.position2)==0){
    pixelstart = 30;
    pixelend = 60;
  }
  
  if(strcmp(topic, position_config.position3)==0){
    pixelstart = 60;
    pixelend = 90;
  }

  if(strcmp(topic, position_config.position4)==0){
    pixelstart = 90;
    pixelend = 120;
  }

  if(strcmp(topic, position_config.position5)==0){
    pixelstart = 120;
    pixelend = 150;
  }

  payload[length] = '\0';
  for (int i = 0; i < length; i++) {
  
  // char receivedChar = (char)payload[i];
  // Serial.print(receivedChar);
   String value = String((char*)payload);
   Serial.println(value);
   long number = strtol( &value[0], NULL, 16); //Convert String to Hex http://stackoverflow.com/questions/23576827/arduino-convert-a-sting-hex-ffffff-into-3-int

   int r = number >> 16 & 0xFF;  
   int g = number >> 8 & 0xFF;
   int b = number & 0xFF;
   Serial.println(r);
   Serial.println(g);
   Serial.println(b); 

  
  // long number = strtol( &receivedChar, NULL, 16); //Convert String to Hex http://stackoverflow.com/questions/23576827/arduino-convert-a-sting-hex-ffffff-into-3-int
   //Serial.println(number);
  
   // Split them up into r, g, b values
    
  // int r = receivedChar >> 16 & 0xFF;  
 //  int g = receivedChar >> 8 & 0xFF;
  // int b = receivedChar & 0xFF;
  
   for(int i=pixelstart;i<pixelend;i++)
         {
             pixels[0].setPixelColor(i, pixels[0].Color(r, g, b));
         }
        
         pixels[0].show();
   }

client.publish(out_topic, String(random(2)).c_str(), true);
  

Serial.println();
}


void loop(){
  while (!client.connected()) {
    reconnect();
    client.subscribe(position_config.position1);
    client.subscribe(position_config.position2);
    client.subscribe(position_config.position3);
    client.subscribe(position_config.position4);
    client.subscribe(position_config.position5);
    
  }
  client.loop();

  }

