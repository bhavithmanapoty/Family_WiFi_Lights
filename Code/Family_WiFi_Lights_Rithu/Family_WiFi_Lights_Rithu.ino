//Include required libraries
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Connect Adafruit Account
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "tstark20486"
#define MQTT_PASS "API KEY"

//ADD WIFI DETAILS
#define WIFI_SSID "PLUSNET-GFMNNG"
#define WIFI_PASS "d3f3df47fc"

//Define Hardware Setup
//LIGHTS
#define BhaviLED D3
#define HomeLED D4
#define RithuLight D5
//SWITCHES
#define HomeTouchSw D6
#define RithuTouchSw D7


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
  pinMode(HomeTouchSw, INPUT);
  pinMode(RithuTouchSw, INPUT);
  pinMode(HomeLED, OUTPUT);
  pinMode(RithuLight, OUTPUT);
  pinMode(BhaviLED, OUTPUT);

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
}

void loop() {
  //Connect/Reconnect to MQTT Server
  MQTT_connect();

  //Checks is someone is contacting this light
  checkIfRithuLightOn();

  //If Touch Bhavith Switch
  if (digitalRead(HomeTouchSw))
  {
    HomeSwitchTouched();
  }

  //If Touch Rithu Switch
  if (digitalRead(RithuTouchSw))
  {
    BhaviSwitchTouched();
  }
}
