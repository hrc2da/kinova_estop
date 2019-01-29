/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */
#include <ros.h>
#include <std_msgs/String.h>
#include <kinova_msgs/Stop.h>
// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

ros::NodeHandle nh;
ros::ServiceClient<kinova_msgs::Stop::Request, kinova_msgs::Stop::Response> client("/j2s7s300_driver/in/stop");

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  nh.initNode();
  nh.serviceClient(client);
  nh.advertise(chatter);
  while(!nh.connected()) nh.spinOnce();
  nh.loginfo("Startup Complete");
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // Serial.println("E-STOP");
    kinova_msgs::Stop::Request req;
    kinova_msgs::Stop::Response res;
    client.call(req,res);
    str_msg.data = "estop";
    chatter.publish(&str_msg);
    
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    // Serial.println(LOW);
  }
  nh.spinOnce();
  // delay(1);
}
