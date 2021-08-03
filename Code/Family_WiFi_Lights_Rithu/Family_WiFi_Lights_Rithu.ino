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

//Light State
int LightState = 0;

//ADD WIFI DETAILS
#define WIFI_SSID "PLUSNET-GFMNNG"
#define WIFI_PASS "d3f3df47fc"

//#define WIFI_SSID "OnePlus 6"
//#define WIFI_PASS "fuggoff123"

//Define Hardware Setup
//LIGHTS
#define RithuLight1 D2
#define RithuLight2 D3
//SWITCHES
#define BhaviTouchSw D5
#define HomeTouchSw D6
#define LightOnSw D7

//LED Strip Setup
#define FASTLED_ALLOW_INTERRUPTS 0
#define NUM_LEDS 15
struct CRGB Light1[NUM_LEDS];
struct CRGB Light2[NUM_LEDS];

//Initialize Connection to Adafruit
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

//Adafruit Subscription Feeds
Adafruit_MQTT_Subscribe RithuLightSub = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/RithuLightState");

//Adafruit Publishing Feeds
Adafruit_MQTT_Publish HomeLightPub = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/HomeLightState");
Adafruit_MQTT_Publish BhaviLightPub = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/BhaviLightState");

void setup() {
  //Begin Serial Connection
  Serial.begin(9600);

  //Hardware Setup
  pinMode(BhaviTouchSw, INPUT_PULLUP);
  pinMode(HomeTouchSw, INPUT_PULLUP);
  pinMode(LightOnSw, INPUT_PULLUP);

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
  mqtt.subscribe(&RithuLightSub);

  //LED Strip Setup
  LEDS.addLeds<WS2812, RithuLight1, GRB>(Light1, NUM_LEDS);
  LEDS.addLeds<WS2812, RithuLight2, GRB>(Light2, NUM_LEDS);
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
  if (!digitalRead(LightOnSw))
  {
    if(LightState == 0){
    LightState = 1;
    }
    else 
    {
     LightState = 0;
    }
  }
  //If Touch Bhavith Switch
  else if (!digitalRead(BhaviTouchSw))
  {
    BhaviSwitchTouched();
  }

  //If Touch Rithu Switch
  else if (!digitalRead(HomeTouchSw))
  {
    HomeSwitchTouched();
  }
  
  //Checks is someone is contacting Home light
  else
  {
    checkIfRithuLightOn();
  }

  //Turn on Light depending on current state
  RithuSwitchTouched(LightState);
}
