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

void BhaviSwitchTouched()
{
  Serial.println("CALLING BHAVITH");

  //Touch Detected LED Indication
  for(int i = 0; i < 5; i++)
  {
    digitalWrite(BhaviLED, HIGH);
    delay(400);
    digitalWrite(BhaviLED, LOW);
    delay(400);
  }
  
  //Adafruit Publish
  BhaviLightPub.publish("ON");
  delay(2000);
  BhaviLightPub.publish("OFF");
}
