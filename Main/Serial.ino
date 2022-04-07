bool injState = false, Lista = false, checked = false, m_rep = false;

void menu() 
{
  if (!m_rep)
  {
    Serial.print(F("\n\tMÁQUINA DE INYECCIÓN DE PLÁSTICOS"));
    Serial.print(F("\n\tSelección de programa: "));
    
    switch (state)
    {
      case 0:
        Serial.print(F("\n\tEstado actual: INICIO"));
        Serial.print(F("\n\t1 - Comprobar periféricos"));
        break;
        
      case 2:
        Serial.print(F("\n\tEstado actual: MÁQUINA ACTIVADA"));
        Serial.print(F("\n\t0 - Desarmar máquina"));
        Serial.print(F("\n\t3 - Activar Unidad de Inyección"));
        break;
  
      case 3:
        Serial.print(F("\n\tEstado actual: UNIDAD DE INYECCIÓN ACTIVADA"));
        Serial.print(F("\n\t4 - Desactivar Unidad de Inyección"));
        Serial.print(F("\n\t5 - Purgar Unidad de Inyección"));
        if (purge)
        {
          Serial.print(F("\n\t6 - Ciclo de Inyección"));
        }
        break;
        
      default:
        break;
    }
    Serial.println();
    Serial.print(F("\n\nPulse tecla + INTRO\n"));
    Serial.flush();
    m_rep = true;
  }
}

void leerSerial() 
{
  if (Serial.available()) 
  {
    char desireState = Serial.read();
  
    switch (desireState) 
    {
      case '0':
        if (state == 2)
        {
          Serial.print(F("\n\nDesarmando Máquina...\n"));
          delay(2000);
          state = 0;
          m_rep = false;
        }
        else{
          Serial.print(F("\n\nEstado deseado incorrecto\n"));
        }
        break;
        
      case '1':
        if (state == 0)
        {
          Serial.print(F("\n\nOpción escogida: comprobación de periféricos\n"));
          state = 1;
        }
        else{
          Serial.print(F("\n\nEstado deseado incorrecto\n"));
        }
        break;
        
      case '3':
        if (state == 2)
        {
          Serial.println(F("\n\nOpción escogida: activar unidad de inyección\n"));
          Serial.print(F("\n\tActivando unidad de inyección..."));
          delay(2000);
          state = 3;
          m_rep = false;
        }
        else{
          Serial.print(F("\n\nEstado deseado incorrecto\n"));
        }
        break;

      case '4':
        if (state == 3)
        {
          Serial.print(F("\n\nOpción escogida: desactivar unidad de inyección\n"));
          state = 4;
        }
        else{
          Serial.print(F("\n\nEstado deseado incorrecto\n"));
        }
        break;

      case '5':
        if (state == 3)
        {
          Serial.print(F("\n\nOpción escogida: purgar unidad de inyección\n"));
          state = 5;
        }
        else{
          Serial.print(F("\n\nEstado deseado incorrecto\n"));
        }
        break;

      case '6':
        if (state == 3)
        {
          Serial.print(F("\n\nOpción escogida: Iniciar ciclo de inyección\n"));
          state = 6;
        }
        else{
          Serial.print(F("\n\nEstado deseado incorrecto\n"));
        }
        break;
 
      default:
        Serial.print(F("\n\nEstado deseado incorrecto\n"));
        break;
    }
  }
}
