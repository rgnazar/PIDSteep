#include <DueTimer.h>

#define MicroPassoAltpino 5
#define MicroPassoAzpino 9
#define DirAltpino 7
#define DirAzpino 11
#define PassoAltpino 6
#define PassoAzpino 10
#define MinTimer 33
#define MaxPassoAlt 1286400
#define MaxPassoAz 1286400


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
float Accelalt = MaxPassoAlt, Accelaz = MaxPassoAz;
float kP = 0.75;
float kI = 0;
float kD = 0;


double erroaltprevious, erroalt, erroazprevious, erroaz, PIDalt, PIDaz;

double intervalpid = millis();
double timerpid = millis();
double intervalpulseaz = intervalpid, intervalpulsealt = intervalpid;



unsigned long previousMillis = 0;        // will store last time LED was updated
// constants won't change :
const long interval = 1000;

void setup() {
  
  Timer3.attachInterrupt(acionamotor);  // initialize serial:
  Serial.begin(9600);
  inputString.reserve(200);
  iniciapmotores();
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '#') {
      stringComplete = true;
    }
  }
}

void loop() {
   PIDCalc();
  // print the string when a newline arrives:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    Serial.println("PIDalt");
    Serial.println(PIDalt);
    Serial.println("erroalt");
    Serial.println(erroalt);
       Serial.println("Accelalt");
    Serial.println(Accelalt);
    
    Serial.println("PIDaz");
    Serial.println(PIDaz);
    Serial.println("erroaz");
    Serial.println(erroaz);
    Serial.println("Accelaz");
    Serial.println(Accelaz);

    Serial.println("intervalpid");
    Serial.println(intervalpid);


  }
  if (stringComplete) {
    Serial.println(inputString);
    char buf[inputString.length()];
    inputString.toCharArray(buf, inputString.length() + 1);
    double val = atof(buf);
    Serial.println("val");
    Serial.println(val);
    AZmountAlvo = val;
    ALTmountAlvo = val;
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}
