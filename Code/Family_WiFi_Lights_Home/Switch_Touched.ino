void HomeSwitchTouched(int state)
{
  
  if(state == 1)
  {
    LED_On('w');
    Serial.println("LIGHT ON");
  }
  else if(state == 0)
  {
    LED_On('0');
    Serial.println("LIGHT OFF");
  }
}
void BhaviSwitchTouched()
{
  Serial.println("CALLING BHAVITH");

  //Touch Detected LED Indication
  for (int i = 0; i < 5; i++)
  {
    LED_On('r');
    delay(400);
    LED_On('0');
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
  for (int i = 0; i < 5; i++)
  {
    LED_On('r');
    delay(400);
    LED_On('0');
    delay(400);
  }

  //Adafruit Publish
  RithuLightPub.publish("ON");
  delay(2000);
  RithuLightPub.publish("OFF");
}

void LED_On(char color)
{
  int r, g, b;
  switch (color)
  {
    //COLORS OF RAINBOW
    case 'v': //VIOLET
      r = 127;
      g = 0;
      b = 255;
      break;
    case 'i': //INDIGO
      r = 75;
      g = 0;
      b = 130;
      break;
    case 'b': //BLUE
      r = 0;
      g = 0;
      b = 255;
      break;
    case 'g': //GREEN
      r = 0;
      g = 255;
      b = 0;
      break;
    case 'y': //YELLOW
      r = 255;
      g = 255;
      b = 0;
      break;
    case 'o': //ORANGE
      r = 255;
      g = 165;
      b = 0;
      break;
    case 'r': //RED
      r = 255;
      g = 0;
      b = 0;
      break;

    //EXTRA COLORS
    case 'c': //CYAN
      r = 0;
      g = 255;
      b = 255;
      break;
    case 'p': //PURPLE
      r = 191;
      g = 64;
      b = 191;
      break;
    case 'w': //WHITE
      r = 255;
      g = 255;
      b = 255;
      break;
    case 'a': //AQUAMARINE
      r = 127;
      g = 255;
      b = 212;
      break;

    //SWITCH OFF LED
    case '0': //OFF
      r = 0;
      g = 0;
      b = 0;
      break;
    default:
      r = 0;
      g = 0;
      b = 0;
      break;
  }

  for (int i = 0; i <= NUM_LEDS; i++)
  {
    Light1[i] = CRGB(r, g, b);
    Light2[i] = CRGB(r, g, b);

  }
  FastLED.show();
  delay(500);
}
