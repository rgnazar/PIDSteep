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
  if (PIDaz < (MinTimer * 3)) {
    PIDaz = MinTimer * 3;
  }
  PIDalt = abs(Palt + Ialt + Dalt);
  if (PIDalt < (MinTimer * 3)) {
    PIDalt = MinTimer * 3;
  }
}

void acionamotor() {

  if ((millis() - intervalpulseaz) > (PIDaz))

  {
    intervalpulseaz = millis();
    gotoAz();
  }

  if ((millis() - intervalpulsealt) > (PIDalt))

  {
    intervalpulsealt = millis();
    gotoAlt();
  }
}

int gotoAlt()
{
  erroaltprevious = erroalt;
  erroalt = ALTmount -  ALTmountAlvo;
  if (erroalt > 1) {
    digitalWrite(DirAltpino, HIGH);
    digitalWrite(PassoAltpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(MinTimer);          // wait for a second
    digitalWrite(PassoAltpino, LOW);    // turn the LED off by making the voltage LOW
    ALTmount--;
    return abs(erroalt);

  } else
  {
    if (erroalt < 1) {
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
  erroazprevious = erroaz;
  erroaz = AZmount -  AZmountAlvo;
  if (erroaz > 1) {
    digitalWrite(DirAzpino, HIGH);
    digitalWrite(PassoAzpino, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(10);            // wait for a second
    digitalWrite(PassoAzpino, LOW);    // turn the LED off by making the voltage LOW
    AZmount--;
    return abs(erroaz);
  } else
  {
    if (erroaz < 1) {
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
