#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define WS2812_PIN0 4   //D2
#define WS2812_PIN1 0   //D3
//#define WS2812_PIN2 2   //D4
//#define WS2812_PIN3 15  //D8
//#define WS2812_PIN4 13  //D7
//#define WS2812_PIN5 12  //D6 

#define LED_WLAN 13 // GPIO13 oder D7 auf dem NodeMCU
 
#define NUMPIXELS_0 16
#define NUMPIXELS_1 16

#define RED 3
#define GREEN 5
#define BLUE 6
#define GND 4

#define DEBUG true
#define SSID "2.4GHz"
//define SSID config_json.wifi_ssid
#define PASSWORD ""
//#define PASSWORD config_json.wifi_pass

//Alternative Progmem: Converted with http://www.percederberg.net/tools/text_converter.html to C-String Text and saved as char
const char site[] PROGMEM = {
  "<HTML><HEAD>"
    "<link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\">"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=2.0, user-scalable=yes\">"
    "<title>RGB LED</title>"
  "</HEAD>"
  "<BODY bgcolor=\"#FFFF99\" text=\"#000000\">"
    "<FONT size=\"6\" FACE=\"Verdana\">Select Color</FONT>"
      "<HR><BR><FONT size=\"3\" FACE=\"Verdana\">Change the Color<BR>of the RGB-LED<BR><BR>"
      "<form method=\"GET\"><input type=\"color\" name=\"rgb\" onchange=\"this.form.submit()\"><BR></form>"
      "<HR>\n<BR>\n<FONT size=\"3\" FACE=\"Verdana\">"
      "Change the Color<BR>of the RGB-LED 2<BR><BR>"
      "<form method=\"GET\"><input type=\"color\" name=\"rgb_2\" onchange=\"this.form.submit()\"><BR></form>"
      "<HR><BR>"
    "</font>"
  "</HTML>"
};

#define PIXEL_STRIPE_COUNT 2
Adafruit_NeoPixel pixels[PIXEL_STRIPE_COUNT] =
{
    Adafruit_NeoPixel(NUMPIXELS_0, WS2812_PIN0, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS_1, WS2812_PIN1, NEO_GRB + NEO_KHZ800)
};
 
int ledPin = LED_WLAN;
ESP8266WebServer server(80);

void setup()
{
    Serial.begin(115200);
    delay(10);

    for(int i = 0; i < PIXEL_STRIPE_COUNT; i++)
    {
        pixels[i].begin();
        pixels[i].show();
    }


    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
 
    // Connect to WiFi network
    Serial.println();
    Serial.println();

    yield();
    IPAddress myIP;
/*    if(!strcmp(config_json.wifi_mode, "AP"))
    {
        Serial.print("Configuring access point...\n");
        WiFi.softAP(SSID, PASSWORD); //You can remove the password parameter if you want the AP to be open.
        myIP = WiFi.softAPIP();
    } else*/
    {
        Serial.print("\nConnecting to SSID ");
        Serial.println(SSID);
        WiFi.begin(SSID, PASSWORD);
        // Wait for connection
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        myIP = WiFi.localIP();
    }
 
    Serial.print("Local IP address: ");
    Serial.println(myIP);


    // Start the server
    server.on("/",              serve__root);
    
    
    server.begin();
    Serial.println("Server started");
   
    // Print the IP address
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");

}
static void serve__root()
{
  
    Serial.println("serve_root");
    if(server.hasArg("rgb"))
    {
        String rgb = server.arg("rgb");
        //input validation!?!?

        long number = (long) strtol( &rgb[1], NULL, 16); //Convert String to Hex http://stackoverflow.com/questions/23576827/arduino-convert-a-sting-hex-ffffff-into-3-int
        // Split them up into r, g, b values
        int r = number >> 16;
        int g = number >> 8 & 0xFF;
        int b = number & 0xFF;

        for(int i=0;i<NUMPIXELS_0;i++)
        {
            pixels[0].setPixelColor(i, pixels[0].Color(r, g, b));
        }
        pixels[0].show();
    }


    if(server.hasArg("rgb_2"))
    {
        String rgb = server.arg("rgb_2");
        //input validation!?!?

        long number = (long) strtol( &rgb[1], NULL, 16); //Convert String to Hex http://stackoverflow.com/questions/23576827/arduino-convert-a-sting-hex-ffffff-into-3-int
        // Split them up into r, g, b values
        int r = number >> 16;
        int g = number >> 8 & 0xFF;
        int b = number & 0xFF;

        for(int i = 0; i<NUMPIXELS_1; i++)
        {
            pixels[1].setPixelColor(i, pixels[1].Color(r, g, b));
        }
        pixels[1].show();
    }

    server.send_P(200, "text/html", site, sizeof(site));
}

void loop()
{
    // Check if a client has connected
    server.handleClient();
 
}
 
