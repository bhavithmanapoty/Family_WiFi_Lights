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
