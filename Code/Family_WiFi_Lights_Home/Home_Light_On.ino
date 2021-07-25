void checkIfHomeLightOn()
{
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &HomeLightSub)
    {
      if (!strcmp((char*) HomeLightSub.lastread, "ON"))
      {
        //Switch ON LED
        Serial.println("Home LED ON");
        for(int i = 0; i < 5; i++){
        digitalWrite(HomeLight, HIGH);
        delay(800);
        digitalWrite(HomeLight, LOW);
        delay(500);
        }
      }
      else if (!strcmp((char*) HomeLightSub.lastread, "OFF"))
      {
        //Switch OFF LED
        digitalWrite(HomeLight, LOW);
        Serial.println("Home LED OFF");
      }
      else
      {
        Serial.println("ERROR");
      }
    }
  }
}
