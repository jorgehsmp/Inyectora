#define OpenMaxTime  10000
#define CloseMaxTime 10000

unsigned long timeCount;

int clampingInit()
{
  if (digitalRead(OpenEndStop_pin) == 0)
  {
    Serial.print(F("\n\nComprobando cierre\n"));
    digitalWrite(Close_pin, LOW);
    delay(2000);
    digitalWrite(Close_pin, HIGH);
    
    if (digitalRead(OpenEndStop_pin) == 0)
    {
        Serial.print(F("\n\nERROR EN APERTURA\n"));
        return 1;
    }
    
    delay(250);
    Serial.print(F("\n\nComprobando apertura\n"));
    digitalWrite(Open_pin, LOW);

    timeCount = millis();
    while(digitalRead(OpenEndStop_pin) == 1)
    {
      digitalWrite(Open_pin, LOW);
      if (((millis() - timeCount) > (OpenMaxTime/2)))
      {
        Serial.print(F("\n\nERROR EN APERTURA\n"));
        digitalWrite(Open_pin, HIGH);
        return 1;
      }
    }
    digitalWrite(Open_pin, HIGH);
    delay(250);
  }
  else
  {
    Serial.print(F("\n\nComprobando apertura\n"));
    timeCount = millis();
    while(digitalRead(OpenEndStop_pin) == 1)
    {
      digitalWrite(Open_pin, LOW);
      if (((millis() - timeCount) > OpenMaxTime))
      {
        Serial.print(F("\n\nERROR EN APERTURA\n"));
        digitalWrite(Open_pin, HIGH);
        return 1;
      }
    }
    digitalWrite(Open_pin, HIGH);
    delay(250);
  }
  return 0;
}

int closeInjUnit()
{
    timeCount = millis();
    while(digitalRead(CloseEndStop_pin) == 1)
    {
      digitalWrite(Close_pin, LOW);
      if (((millis() - timeCount) > CloseMaxTime))
      {
        Serial.print(F("\n\nERROR EN EL CIERRE\n"));
        digitalWrite(Close_pin, HIGH);
        return 1;
      }
    }
    digitalWrite(Close_pin, HIGH);
    delay(250);
    return 0;
}

int openInjUnit()
{
    timeCount = millis();
    while(digitalRead(OpenEndStop_pin) == 1)
    {
      digitalWrite(Open_pin, LOW);
      if (((millis() - timeCount) > OpenMaxTime))
      {
        Serial.print(F("\n\nERROR EN LA APERTURA\n"));
        digitalWrite(Open_pin, HIGH);
        return 1;
      }
    }
    digitalWrite(Open_pin, HIGH);
    delay(250);
    return 0;
}
