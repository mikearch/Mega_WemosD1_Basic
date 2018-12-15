/*
  Multiple Serial test

  Prints a incremented bit of data to main serial port and
  Serial Port 1  use.

  This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc.

  The circuit:
  - any serial device attached to Serial port 1
  - Serial Monitor open on Serial port 0

Array Index Keys
arrayBooleam[]
  0 status_Home = whether current status is Home or Away

arrayFloat[]
  0 temp_Bar = temperature in Bar
  1 temp_HtOn = set temperature degC for Away Heat On

arrayLongUs[]
  0 time_HeatCycle = set time in seconds for HeatOn during Away
  1 time_CycleRem = time in seconds remaining in curr HeatCycle

*/
//Defines lengths of arrays, change when new pubsub data added
const int arraySize_boolean = 1;
const int arraySize_float = 2;
const int arraySize_longUsInt = 2;

//Defines arrays for pubsub
float arrayFloat[arraySize_float] = {20.3, 21.7};
boolean arrayBoolean[arraySize_boolean] = {false};
unsigned long arrayLongUs[arraySize_longUsInt] = {456789, 123456};

//Array identifier Variables
String arrayFloatVars ="f";
String arrayBoolVars ="b";
String arrayLongUSVars ="l";

//************Transmit Variables******************************************
String begOfLine = "<";
String endOfLine = ">";
String delim =",";

int n = 0;     //initializes array print counter

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
//Float array variable transmision
  for (n=0; n <= arraySize_float - 1; n++ ) {
    Serial1.print (begOfLine);
    Serial1.print (arrayFloatVars);
    Serial1.print(delim);
    Serial1.print(n);
    Serial1.print(delim);
    Serial1.print(arrayFloat[n]);
    Serial1.print(endOfLine);
    Serial1.flush();
    delay(1000);
  }

//Boolean array variable transmision
  for (n=0; n <= arraySize_boolean - 1; n++ ) {
    Serial1.print (begOfLine);
    Serial1.print (arrayBoolVars);
    Serial1.print(delim);
    Serial1.print(n);
    Serial1.print(delim);
    Serial1.print(arrayBoolean[n]);
    Serial1.print(endOfLine);
    Serial1.flush();
    delay(1000);
  }

//Unsigned Long array variable transmision
  for (n=0; n <= arraySize_longUsInt - 1; n++ ) {
    Serial1.print (begOfLine);
    Serial1.print (arrayLongUSVars);
    Serial1.print(delim);
    Serial1.print(n);
    Serial1.print(delim);
    Serial1.print(arrayLongUs[n]);
    Serial1.print(endOfLine);
    Serial1.flush();
    delay(1000);
  }

delay(35000);

}
