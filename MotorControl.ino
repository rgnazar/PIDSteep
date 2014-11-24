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
  PIDaz = abs(Paz + Iaz + Daz);
  PIDalt = abs(Palt + Ialt + Dalt);

}

void acionamotor() {
  erroazprevious = erroaz;
  erroaz = AZmount -  AZmountAlvo;
  erroaltprevious = erroalt;
  erroalt = ALTmount -  ALTmountAlvo;
  PIDCalc();
  if (PIDaz == 0)
  {
    if (millis() > (intervalpulseaz - 1))
    {
      gotoAz();
    }
    else
    {
      intervalpulseaz = millis() + MinTimer * (3 + (1 / abs(PIDaz)));
      gotoAz();
    }
  }


  if (PIDalt == 0)
  {
    if (millis() > (intervalpulsealt - 1))
    {
      gotoAlt();
    }
    else
    {
      intervalpulsealt = millis() + MinTimer * (3 + (1 / abs(PIDalt)));
      gotoAlt();
    }
  }





}

int gotoAlt()
{

  if (PIDalt >= 0) {
    digitalWrite(DirAltpino, HIGH);
    digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer);          // wait for a second
    digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
    ALTmount--;
    return abs(erroalt);

  } else
  {
    if (PIDalt < 0) {
      digitalWrite(DirAltpino, LOW);
      digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
      delayMicroseconds(MinTimer);          // wait for a second
      digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
      ALTmount++;
      return abs(erroalt);

    } else
    {
      return (0);
    }
  }
}


int gotoAz()
{

  if (PIDaz >= 0) {
    digitalWrite(DirAzpino, HIGH);
    digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(10);            // wait for a second
    digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
    AZmount--;
    return abs(erroaz);
  } else
  {
    if (PIDaz < 0) {
      digitalWrite(DirAzpino, LOW);
      digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
      delayMicroseconds(10);            // wait for a second
      digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
      AZmount++;
      return abs(erroaz);

    } else
    {
      return (0);
    }
  }
}
