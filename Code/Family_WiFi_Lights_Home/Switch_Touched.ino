void BhaviSwitchTouched()
{
  Serial.println("CALLING BHAVITH");
    BhaviLightPub.publish("ON");
    delay(1000);
    BhaviLightPub.publish("OFF");
}

void RithuSwitchTouched()
{
  Serial.println("CALLING RITHIKA");
    RithuLightPub.publish("ON");
    delay(1000);
    RithuLightPub.publish("OFF");
}
