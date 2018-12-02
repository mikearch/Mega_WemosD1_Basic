/*
  Multiple Serial test

  Prints a incremented bit of data to main serial port and
  Serial Port 1  use.

  This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc.

  The circuit:
  - any serial device attached to Serial port 1
  - Serial Monitor open on Serial port 0



*/

//************Transmit Variables******************************************
string begOfLine = "<";
string endOfLine = ">";
string delim =",";
//**********Heating Group 1 Transmit Codes*******************************
string burnState = "a";             //burner on/off state
string pumpState = "b";             //pump on/off state
string indrTemp =  "c";             //Curr indoor temp
string htgHold = "d";               //Away heating hold time
string lowTemp = "e";               //Min indoor set temp
string delayTime = "f";             //Delay time set point
//**********Power Group Transmit Codes**********************************
string powerStatus = "g";           //status of house power

//**********Test Variables************************************************
boolean burner = false;
boolean pump = false;
float inTemp = 21.3;
boolean HHold = false;
float mTemp = 10;
int dTime = 120;
boolean powerState= false;

int c = 1;     //initializes counter

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {

  Serial1.print (begOfLine);
  Serial1.print (c);
  Serial1.print(delim);
  Serial1.print(burnState);
  Serial1.print(delim);
  Serial1.print(burner);
  Serial1.print(delim);
  Serial1.print(indrTemp);
  Serial1.print(delim);
  Serial1.print(inTemp);
  Serial1.print(delim);
  Serial1.print(endOfLine);
  delay(5000);
  c = c+1;
}
