void checkIfRithuLightOn()
{
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &RithuLightSub)
    {
      if (!strcmp((char*) RithuLightSub.lastread, "ON"))
      {
        //Switch ON LED
        Serial.println("Rithika Light ON");
        for(int i = 0; i < 5; i++){
        digitalWrite(RithuLight, HIGH);
        delay(800);
        digitalWrite(RithuLight, LOW);
        delay(500);
        }
      }
      else if (!strcmp((char*) RithuLightSub.lastread, "OFF"))
      {
        //Switch OFF LED
        digitalWrite(RithuLight, LOW);
        Serial.println("Rithika Light OFF");
      }
      else
      {
        Serial.println("ERROR");
      }
    }
  }
}
