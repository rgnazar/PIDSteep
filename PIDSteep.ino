#include <DueTimer.h>

#define MicroPassoAltpino 5
#define MicroPassoAzpino 9
#define DirAltpino 7
#define DirAzpino 11
#define PassoAltpino 6
#define PassoAzpino 10
#define MinTimer 35

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
//Variaveis globais de posição fisica do telescopio  ----------------------------------------------------------------------------------------------------------------
double eixoAltGrausDecimal = 0.0;
double eixoAzGrausDecimal = 0.0;
double RAmount = 0.0;
double DECmount = 0.0;
double AZmount = 0.0;
double ALTmount = 0.0;
double AZmountAlvo = 0.0;
double ALTmountAlvo = 0.0;
double erroAZ, erroALT;

//PID Variaveis
float Palt = 0, Paz = 0;
float Ialt = 0, Iaz = 0;  
float Dalt = 0, Daz = 0;
float Accelalt=10000, Accelaz=10000;
float kP = 0.12;     
float kI = 0.430;
float kD = 0.20;



double erroaltprevious, erroalt, erroazprevious, erroaz, PIDalt, PIDaz;

double intervalpid = millis();
double intervalpulseaz = intervalpid, intervalpulsealt = intervalpid;

void setup() {
  Timer3.attachInterrupt(acionamotor);  // initialize serial:
  Serial.begin(9600);
  inputString.reserve(200);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    char buf[inputString.length()];
    inputString.toCharArray(buf, inputString.length() + 1);
    double val = atof(buf);
    AZmount = val;
    ALTmount = val;
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}
