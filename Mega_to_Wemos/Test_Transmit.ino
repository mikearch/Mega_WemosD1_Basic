/*
  Multiple Serial test

  Prints a incremented bit of data to main serial port and
  Serial Port 1  use.

  This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc.

  The circuit:
  - any serial device attached to Serial port 1
  - Serial Monitor open on Serial port 0



*/
int c = 1;     //initializes counter

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  Serial.println (c);
  Serial1.print ("<");
  Serial1.print(c);
  Serial1.print(">");
  delay(5000);
  c = c+1;
}
