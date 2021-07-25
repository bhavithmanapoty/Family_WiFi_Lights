void checkIfBhaviLightOn()
{
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &BhaviLightSub)
    {
      if (!strcmp((char*) BhaviLightSub.lastread, "ON"))
      {
        //Switch ON LED
        Serial.println("Home LED ON");
        for(int i = 0; i < 5; i++){
        digitalWrite(BhaviLight, HIGH);
        delay(800);
        digitalWrite(BhaviLight, LOW);
        delay(500);
        }
      }
      else if (!strcmp((char*) BhaviLightSub.lastread, "OFF"))
      {
        //Switch OFF LED
        digitalWrite(BhaviLight, LOW);
        Serial.println("Home LED OFF");
      }
      else
      {
        Serial.println("ERROR");
      }
    }
  }
}
