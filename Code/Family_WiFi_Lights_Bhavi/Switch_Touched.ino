void HomeSwitchTouched()
{
  Serial.println("CALLING HOME");

  //Touch Detected Indication
  for(int i = 0; i < 5; i++)
  {
    digitalWrite(HomeLED, HIGH);
    delay(400);
    digitalWrite(HomeLED, LOW);
    delay(400);
  }

  //Adafruit Publish
  HomeLightPub.publish("ON");
  delay(1000);
  HomeLightPub.publish("OFF");
}

void RithuSwitchTouched()
{
  Serial.println("CALLING RITHIKA");

  //Touch Detected LED Indication
  for(int i = 0; i < 5; i++)
  {
    digitalWrite(RithuLED, HIGH);
    delay(400);
    digitalWrite(RithuLED, LOW);
    delay(400);
  }

  //Adafruit Publish
  RithuLightPub.publish("ON");
  delay(2000);
  RithuLightPub.publish("OFF");
}
