#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#define wifi_ssid "$ssid"
#define wifi_password "$pw"

#define mqtt_server "$brokeradress"
#define mqtt_port 1883
#define mqtt_user "$username"
#define mqtt_password "$password"

#define in_topic "LED/#"
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

#define NUMPIXELS_0 16
#define NUMPIXELS_1 16

WiFiClient espClient;
PubSubClient client;

#define PIXEL_STRIPE_COUNT 2
Adafruit_NeoPixel pixels[PIXEL_STRIPE_COUNT] =
{
    Adafruit_NeoPixel(NUMPIXELS_0, WS2812_PIN0, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS_1, WS2812_PIN1, NEO_GRB + NEO_KHZ800)
};

int ledPin = LED_WLAN;

void setup() {
  Serial.begin(115200);
  setup_wifi();

  for(int i = 0; i < PIXEL_STRIPE_COUNT; i++)
  {
        pixels[i].begin();
        pixels[i].show();
  }


    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
  
  client.setClient(espClient);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(in_led, OUTPUT);
  digitalWrite(in_led, HIGH);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
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
  
  for(int i=0;i<NUMPIXELS_0;i++)
        {
            pixels[0].setPixelColor(i, pixels[0].Color(r, g, b));
        }
        
        pixels[0].show();
  }

 

Serial.println();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // Publishes a random 0 and 1 like someone switching off and on randomly (random(2))
  client.publish(out_topic, String(random(2)).c_str(), true);
  delay(1000);
  client.subscribe(in_topic);
  delay(1000);
}
