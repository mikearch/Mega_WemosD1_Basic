//For Wifi functions
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
