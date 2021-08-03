void checkIfRithuLightOn()
{
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(1500)))
  {
    if (subscription == &RithuLightSub)
    {
      if (!strcmp((char*) RithuLightSub.lastread, "ON"))
      {
        //Switch ON LED
        Serial.println("Rithu Light ON");
        rainbow_wave(25, 10);
        FastLED.show();
        delay(5000);
        FastLED.clear();
      }
      else if (!strcmp((char*) RithuLightSub.lastread, "OFF"))
      {
        //Switch OFF LED
        Serial.println("Rithu Light OFF");
        FastLED.clear();
      }
      else
      {
        Serial.println("ERROR");
      }
    }
  }
}

void rainbow_wave(uint8_t thisSpeed, uint8_t deltaHue) {

// uint8_t thisHue = beatsin8(thisSpeed,0,255);
 uint8_t thisHue = beat8(thisSpeed,255);
  
 fill_rainbow(Light1, NUM_LEDS, thisHue, deltaHue);
 fill_rainbow(Light2, NUM_LEDS, thisHue, deltaHue);

}
