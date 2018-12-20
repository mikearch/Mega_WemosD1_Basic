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
//***********Defines lengths of arrays********************************
// change when new pubsub data added
const int arraySize_boolean = 1;
const int arraySize_float = 2;
const int arraySize_longUsInt = 2;

//************Defines arrays for pubsub*********************************
float arrayFloat[arraySize_float] = {20.3, 21.7};
boolean arrayBoolean[arraySize_boolean] = {false};
unsigned long arrayLongUs[arraySize_longUsInt] = {7200, 5600};

//************Array identifier Variables*********************************
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

printFloat();    //Float array variable transmision
printBoolean();  //Boolean array variable transmision
printLongUsInt();  //Unsigned Long array variable transmision

delay(35000);

}
