/*

pubsub branch
Wemos evice code which
Enables a Wemos D1 R2 to be a wifi connection and a mosquitto node for an arduino mega.

PubSub Resources for this project provided by Rui Santos
at http://rntLab.comma
*/

//******PubSub Libraries*******************************
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Change the credentials below, so your ESP8266 connects to your router

//RADOVICA logon credentials
const char* ssid = "HUAWEI-E5776-89CD";radovica server
const char* password = "QFYTA2E2";radovica server

//Wife login--comment out all except one location
//lUBLJANA Logon credentials
//const char* ssid = "335C8E";
//const char* password = "EVW32C0N00099679";


// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.1.101"; //use for radovica ip
//const char* mqtt_server = "192.168.0.24"; //use for ljubljana ip

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient barTest;
PubSubClient client(barTest);
long lastMsg = 0;
char msg[50];
int value = 0;

// Timers auxiliary variables
unsigned long Tnow = millis();
unsigned long lastMeasure = 0;

//**********Variables for reading incoming serial data**********
const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

//Variables-not sure what thisis for
int chk;

//**************************************************************
//*******************Setup************************************
void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
    setup_wifi();
//***********Setup for PubSub*********************************
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    delay(1500);  // Allow the hardware to sort itself out
}

void loop() {
//For serial comm
    recvWithStartEndMarkers();

//For PubSub Routine
if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP3_Bar");
    delay(2000);
    Tnow = millis();
    if (Tnow - lastMeasure > 500) {
      lastMeasure = Tnow;
      if (newData == true) {
        Serial.println("publish");
        client.publish("bar/test", receivedChars);
      }
    }
    showNewData();
}
