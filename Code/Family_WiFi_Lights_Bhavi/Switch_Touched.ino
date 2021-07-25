void HomeSwitchTouched()
{
  Serial.println("CALLING HOME");
  HomeLightPub.publish("ON");
  delay(1000);
  HomeLightPub.publish("OFF");
}

void RithuSwitchTouched()
{
  Serial.println("CALLING RITHIKA");
  RithuLightPub.publish("ON");
  delay(1000);
  RithuLightPub.publish("OFF");
}
