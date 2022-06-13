#define MicroStepINIT       100
#define MicroStepPurge      30000
#define MicroStepInjBack    250
#define MicroStepInjection  20000
#define Forward   LOW
#define Backward  HIGH

int steps = 0;

void screwInit()
{
  digitalWrite(DIR_pin, Forward);
  // Movimiento en una dirección
  for (steps = 0; steps <= MicroStepINIT; steps += 1)
  {
    digitalWrite(PWM_pin, HIGH);
    delayMicroseconds(250);
    digitalWrite(PWM_pin, LOW);
    delayMicroseconds(250);
  }

  digitalWrite(DIR_pin, Backward);
  delay(500);
  //Movimiento en la dirección contraria
  for (steps = 0; steps <= MicroStepINIT; steps += 1)
  {
    digitalWrite(PWM_pin, HIGH);
    delayMicroseconds(250);
    digitalWrite(PWM_pin, LOW);
    delayMicroseconds(250);
  }

}

void purgeBarrel()
{
  digitalWrite(DIR_pin, Forward);
  // Movimiento en una dirección
  for (steps = 0; steps <= MicroStepPurge; steps += 1)
  {
    digitalWrite(PWM_pin, HIGH);
    delayMicroseconds(125);
    digitalWrite(PWM_pin, LOW);
    delayMicroseconds(125);
  }
  //Cambio de dirección
  digitalWrite(DIR_pin, Backward);
  delay(500);
  //Movimiento en la dirección contraria
  for (steps = 0; steps <= MicroStepInjBack; steps += 1)
  {
    digitalWrite(PWM_pin, HIGH);
    delayMicroseconds(50);
    digitalWrite(PWM_pin, LOW);
    delayMicroseconds(50);
  }
}

void heatingMaterial()
{
  Serial.print("Calentando el material");
  digitalWrite(DIR_pin, Forward);
  // Movimiento en una dirección
  for (steps = 0; steps <= 1250; steps += 1)
  {
    digitalWrite(PWM_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(PWM_pin, LOW);
    delayMicroseconds(500);
  }
  //Cambio de dirección
  digitalWrite(DIR_pin, Backward);
  delay(100);
  //Movimiento en la dirección contraria
  for (steps = 0; steps <= 1000; steps += 1)
  {
    digitalWrite(PWM_pin, HIGH);
    delayMicroseconds(250);
    digitalWrite(PWM_pin, LOW);
    delayMicroseconds(250);
  }
}

void injectingMaterial()
{
  digitalWrite(DIR_pin, Forward);
  // Movimiento en una dirección
  for (steps = 0; steps <= MicroStepInjection; steps += 1)
  {
    digitalWrite(PWM_pin, HIGH);
    delayMicroseconds(75);
    digitalWrite(PWM_pin, LOW);
    delayMicroseconds(75);
  }
  //Cambio de dirección
  digitalWrite(DIR_pin, Backward);
  delay(100);
  //Movimiento en la dirección contraria
  for (steps = 0; steps <= MicroStepInjBack; steps += 1)
  {
    digitalWrite(PWM_pin, HIGH);
    delayMicroseconds(50);
    digitalWrite(PWM_pin, LOW);
    delayMicroseconds(50);
  }
}
