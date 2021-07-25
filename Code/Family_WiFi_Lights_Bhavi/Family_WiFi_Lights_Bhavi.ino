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
#define HomeTouchSw D6
#define RithuTouchSw D7
#define LED D5

//Initialize Connection to Adafruit
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

Adafruit_MQTT_Subscribe BhaviLightSub = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/BhaviLightState");
Adafruit_MQTT_Publish HomeLightPub = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/HomeLightState");
Adafruit_MQTT_Publish RithuLightPub = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/RithuLightState");

void setup() {
  //Begin Serial Connection
  Serial.begin(9600);

  //Hardware Setup
  pinMode(HomeTouchSw, INPUT);
  pinMode(RithuTouchSw, INPUT);
  pinMode(LED, OUTPUT);

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
  mqtt.subscribe(&BhaviLightSub);
}

void loop() {
  //Connect/Reconnect to MQTT Server
  MQTT_connect();

  //Checks is someone is contacting this light
  checkIfBhaviLightOn();

  //If Touch Bhavith Switch
  if (digitalRead(HomeTouchSw))
  {
    HomeSwitchTouched();
  }

  //If Touch Rithu Switch
  if (digitalRead(RithuTouchSw))
  {
    //RithuSwitchTouched();
  }
}
