//Include required libraries
#include <ESP8266WiFi.h>
#include <FastLED.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Connect Adafruit Account
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "tstark20486"
#define MQTT_PASS "API KEY"

//Adafruit Ping
#define MQTT_KEEP_ALIVE 300
unsigned long previousTime = 0;
int state = 0;

//ADD WIFI DETAILS
//#define WIFI_SSID "PLUSNET-GFMNNG"
//#define WIFI_PASS "d3f3df47fc"

#define WIFI_SSID "OnePlus 6"
#define WIFI_PASS "fuggoff123"

//Define Hardware Setup
//LIGHTS
#define HomeLight1 D2
#define HomeLight2 D3

//SWITCHES
#define BhaviTouchSw D7
#define RithuTouchSw D5
#define LightOnSw D8

//LED Strip Setup
#define FASTLED_ALLOW_INTERRUPTS 0
#define NUM_LEDS 15
struct CRGB Light1[NUM_LEDS];
struct CRGB Light2[NUM_LEDS];

//Initialize Connection to Adafruit
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

//Adafruit Subscription Feeds
Adafruit_MQTT_Subscribe HomeLightSub = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/HomeLightState");

//Adafruit Publishing Feeds
Adafruit_MQTT_Publish BhaviLightPub = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/BhaviLightState");
Adafruit_MQTT_Publish RithuLightPub = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/RithuLightState");

void setup() {
  //Begin Serial Connection
  Serial.begin(9600);

  //Hardware Setup
  pinMode(BhaviTouchSw, INPUT);
  pinMode(RithuTouchSw, INPUT);
  pinMode(LightOnSw, INPUT);

  //Connect to  WiFi
  Serial.print("\n\nConnecting Wifi>");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(">");
    delay(50);
  }
  Serial.println("OK!");

  //Subscribe to Adafruit Feeds
  mqtt.subscribe(&HomeLightSub);

  //LED Strip Setup
  LEDS.addLeds<WS2812, HomeLight1, GRB>(Light1, NUM_LEDS);
  LEDS.addLeds<WS2812, HomeLight2, GRB>(Light2, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.clear();
}

void loop() {

   //Connect/Reconnect to MQTT Server
  if(!mqtt.connected()){
    MQTT_connect();
  }
  
  //If Touch Light Switch
  if (digitalRead(LightOnSw))
  {
    if(state == 0){
    HomeSwitchTouched(1);
    state = 1;
    }
    else 
    {
     HomeSwitchTouched(0);
     state = 0;
    }
  }
  //If Touch Bhavith Switch
  if (digitalRead(BhaviTouchSw))
  {
    BhaviSwitchTouched();
  }

  //If Touch Rithu Switch
  if (digitalRead(RithuTouchSw))
  {
    RithuSwitchTouched();
  }

  //Checks is someone is contacting Home light
  //checkIfHomeLightOn();
}
