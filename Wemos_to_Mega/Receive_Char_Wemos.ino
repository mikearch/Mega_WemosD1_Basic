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

//RADOMIVA logon credentials
//const char* ssid = "HUAWEI-E5776-89CD";radovica server
//const char* password = "QFYTA2E2";radovica server

//lUBLJANA Logon credentials
const char* ssid = "8D87DA";
const char* password = "EVW327N036930";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
//const char* mqtt_server = "192.168.1.101"  use for radovica ip
const char* mqtt_server = "192.168.0.24"; //use for ljubljana ip

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
// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}
//*********PubSub Callback Function***********************************
// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
/*
//This part of void callback() is for actions involved in receiving topics
  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic home/office/esp1/desk, you check if the message is either 1 or 0. Turns the Desk outlet according to the message
  if(topic=="home/office/esp1/desk"){
      Serial.print("Changing Desk light to ");
      if(messageTemp == "1"){

        Serial.print("On");
      }
      else if(messageTemp == "0"){

        Serial.print("Off");
      }
  }
  if(topic=="home/office/esp1/workbench"){
      Serial.print("Changing Workbench light to ");
      if(messageTemp == "1"){

        Serial.print("On");
      }
      else if(messageTemp == "0"){

        Serial.print("Off");
      }
  }
  Serial.println();
*/
}

//**********PubSub Reconnect Funtion********************************
// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    /*
     YOU MIGHT NEED TO CHANGE THIS LINE, IF YOU'RE HAVING PROBLEMS WITH MQTT MULTIPLE CONNECTIONS
     To change the ESP device ID, you will have to give a new name to the ESP8266.
     Here's how it looks:
       if (client.connect("ESP8266Client")) {
     You can do it like this:
       if (client.connect("ESP1_Office")) {
     Then, for the other ESP:
       if (client.connect("ESP2_Garage")) {
      That should solve your MQTT multiple connections problem
    */
    if (client.connect("ESP3_Bar")) {
      Serial.println("connected");
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("home/office/esp1/desk");
      client.subscribe("home/office/esp1/workbench");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//**************************************************************
//*******************Setup************************************
void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
    setup_wifi();
//***********Setup for PubSub*********************************
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    // Allow the hardware to sort itself out
    delay(1500);
}

void loop() {
//For serial comm
    recvWithStartEndMarkers();
    showNewData();

//For PubSub Routine
if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP3_Bar");
    delay(2000);
    Tnow = millis();
    if (Tnow - lastMeasure > 30000) {
    lastMeasure = Tnow;
    Serial.println("publish");
    client.publish("bar/test", receivedChars);

}
}
//For serial comm
void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

//For serial comm
 // if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//For serial comm
void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        newData = false;
    }
}

//**********************************************************
//**********Code to be Merged with Above*********************
