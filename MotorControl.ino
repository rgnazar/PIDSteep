void iniciapmotores()
{
  pinMode(MicroPassoAzpino, OUTPUT);
  pinMode(MicroPassoAltpino, OUTPUT);
  pinMode(DirAltpino, OUTPUT);
  pinMode(DirAzpino, OUTPUT);
  pinMode(PassoAltpino, OUTPUT);
  pinMode(PassoAzpino, OUTPUT);
  digitalWrite(MicroPassoAzpino, HIGH);
  digitalWrite(MicroPassoAltpino, HIGH);
  digitalWrite(DirAltpino, HIGH);
  digitalWrite(DirAzpino, HIGH);
  Timer3.start(MinTimer);

}


void PIDCalc()
{
  intervalpid = millis() - intervalpid;
  Palt = erroalt / kP;
  Paz = erroaz / kP;
  Ialt = Ialt + (Palt * intervalpid) / kI;
  Iaz = Iaz + (Palt * intervalpid) / kI;
  Dalt = (erroalt - erroaltprevious) / intervalpid / kD;
  Daz = (erroaz - erroazprevious) / intervalpid / kD;
  PIDaz = Paz + Iaz + Daz;
  PIDalt = Palt + Ialt + Dalt;

}

void acionamotor() {
  erroazprevious = erroaz;
  erroaz = AZmount -  AZmountAlvo;
  erroaltprevious = erroalt;
  erroalt = ALTmount -  ALTmountAlvo;
  PIDCalc();
  if (PIDaz == 0)
  {
    if (millis() > intervalpulseaz)
    {
      intervalpulseaz = Accelaz + millis();
      gotoAz();
    }
  }
  else 
  {
    if (millis() > intervalpulseaz)
    {
      Accelaz = MinTimer*(3+(1/abs(PIDaz));
      intervalpulseaz = Accelaz + millis();
      gotoAz();
    }

  }
  
   if (PIDalt == 0)
  {
    if (millis() > intervalpulsealt)
    {
      intervalpulsealt = Accelalt + millis();
      gotoAlt();
    }
  }
  else 
  {
    if (millis() > intervalpulsealt)
    {
      Accelalt = MinTimer*(3+(1/abs(PIDalt));
      intervalpulsealt = Accelalt + millis();
      gotoAlt();
    }

  }
  
  
  
}





int gotoAlt()
{

  if (PIDalt > 0) {
    digitalWrite(DirAltpino, HIGH);
    digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer);          // wait for a second
    digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
    ALTmount--;
    return abs(erroalt);
  }
  if (PIDalt < 0) {
    digitalWrite(DirAltpino, LOW);
    digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer);          // wait for a second
    digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
    ALTmount++;
    return abs(erroalt);
  }
  if (PIDalt = 0) {
    digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer);          // wait for a second
    digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
    if (PassoAltpino == HIGH)
    {
      ALTmount--;
    }
    else
    {
      ALTmount++;
    }
    return abs(erroalt);
  }
}


int gotoAz()
{

  if (PIDaz > 0) {
    digitalWrite(DirAzpino, HIGH);
    digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer);            // wait for a second
    digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
    AZmount--;
    return abs(erroaz);
  }
  if (PIDaz < 0) {
    digitalWrite(DirAzpino, LOW);
    digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer);            // wait for a second
    digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
    AZmount++;
    return abs(erroaz);

  }
  if (PIDaz == 0) {
    digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer);            // wait for a second
    digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
    if (DirAzpino == HIGH)
    {
      AZmount--;
    }
    else
    {
      AZmount++;
    }
    return abs(erroaz);
  }
}
