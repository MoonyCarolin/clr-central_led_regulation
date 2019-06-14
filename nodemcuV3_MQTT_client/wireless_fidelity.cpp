#include <ESP8266WiFi.h>
#include "json_model.h"
#include "spiffs.h"

typedef struct
{
    char mode[4];
    char ssid[32];
    char pass[32];
} wifi_config_json_t;

static wifi_config_json_t wifi_config = {0};
static WiFiEventHandler stationModeConnected;
static WiFiEventHandler stationModeDisconnected;
static WiFiEventHandler stationModeGotIP;
static WiFiEventHandler stationModeDHCPTimeout;
static WiFiEventHandler softAPModeStationConnected;
static WiFiEventHandler softAPModeStationDisconnected;
/*
WiFiEventHandler  onStationModeConnected (std::function< void(const WiFiEventStationModeConnected &)>) 
WiFiEventHandler  onStationModeDisconnected (std::function< void(const WiFiEventStationModeDisconnected &)>) 
WiFiEventHandler  onStationModeAuthModeChanged (std::function< void(const WiFiEventStationModeAuthModeChanged &)>) 
WiFiEventHandler  onStationModeGotIP (std::function< void(const WiFiEventStationModeGotIP &)>) 
WiFiEventHandler  onStationModeDHCPTimeout (std::function< void(void)>) 
WiFiEventHandler onSoftAPModeProbeRequestReceived(std::function<void(const WiFiEventSoftAPModeProbeRequestReceived&)>);
*/

static String macToString(const unsigned char* mac)
{
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}

static String ipToString(const IPAddress addr)
{
  char buf[16];
  snprintf(buf, sizeof(buf), "%u.%u.%u.%u",
           addr[0], addr[1], addr[2], addr[3]);
  return String(buf);
}

static void onStationModeConnected(const WiFiEventStationModeConnected& evt)
{
  Serial.print("; WiFi connected. ssid=");
  Serial.print(evt.ssid);
  Serial.print(", bssid=");
  Serial.print(macToString(evt.bssid));
  Serial.print(", channel=");
  Serial.println(evt.channel);
}

static void onStationModeDisconnected(const WiFiEventStationModeDisconnected& evt)
{
  Serial.print("; WiFi disconnected. ssid=");
  Serial.print(evt.ssid);
  Serial.print(", bssid=");
  Serial.print(macToString(evt.bssid));
  Serial.print(", reason=");
  Serial.println(evt.reason);
}


static void onStationModeGotIP(const WiFiEventStationModeGotIP& evt)
{
  Serial.print("; Local IP address: ");
  Serial.print(ipToString(evt.ip));
  Serial.print(", Netmask: ");
  Serial.print(ipToString(evt.mask));
  Serial.print(", Gateway: ");
  Serial.println(ipToString(evt.gw));
}
static void onStationModeDHCPTimeout(void)
{
  Serial.println("; DHCP timeout.");
}

static void onSoftAPModeStationConnected(const WiFiEventSoftAPModeStationConnected& evt)
{
  Serial.print("; Station connected: ");
  Serial.println(macToString(evt.mac));
}

static void onSoftAPModeStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& evt)
{
  Serial.print("; Station disconnected: ");
  Serial.println(macToString(evt.mac));
}

bool wifi_initialize()
{
  //Start by reading the configuration from SPIFFS
  
    Serial.println("; Reading wireless configuration");
    read_json("/wifi_config.json", &wifi_config, sizeof(wifi_config_json_t), wifi_config_json_desc);

    WiFi.persistent (false);
    yield();
    bool no_pass = strlen(wifi_config.pass) == 0;
    if(no_pass)
        Serial.println("; No wifi password configured.");
    
    if(!strcmp(wifi_config.mode, "AP"))
    {
        Serial.print("; Configuring access point with SSID: ");
        Serial.println(wifi_config.ssid);

        softAPModeStationConnected = WiFi.onSoftAPModeStationConnected(&onSoftAPModeStationConnected);
        softAPModeStationDisconnected = WiFi.onSoftAPModeStationDisconnected(&onSoftAPModeStationDisconnected);

        WiFi.mode(WIFI_AP);
        if(no_pass)   WiFi.softAP(wifi_config.ssid);
        else          WiFi.softAP(wifi_config.ssid, wifi_config.pass);

        IPAddress myIP = WiFi.softAPIP();
        Serial.print("; Local IP address: ");
        Serial.println(myIP);
    } else
    {
        Serial.print("; Connecting to SSID: ");
        Serial.println(wifi_config.ssid);

        stationModeConnected = WiFi.onStationModeConnected(&onStationModeConnected);
        stationModeDisconnected = WiFi.onStationModeDisconnected(&onStationModeDisconnected);
        stationModeGotIP = WiFi.onStationModeGotIP(&onStationModeGotIP);
        stationModeDHCPTimeout = WiFi.onStationModeDHCPTimeout(&onStationModeDHCPTimeout);

        WiFi.mode(WIFI_STA);
        if(no_pass)   WiFi.begin(wifi_config.ssid);
        else          WiFi.begin(wifi_config.ssid, wifi_config.pass);

        // Wait for connection
        /*while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        myIP = WiFi.localIP();*/
    }
    return 1;
}



void wifi_tick()
{
  
}

