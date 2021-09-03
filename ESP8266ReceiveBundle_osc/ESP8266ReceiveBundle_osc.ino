/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for receiving open sound control (OSC) bundles on the ESP8266/ESP32
  Send integers '0' or '1' to the address "/led" to turn on/off the built-in LED of the esp8266.

  This example code is in the public domain.

  --------------------------------------------------------------------------------------------- */
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

const char* const ssid = "TonyAP";
const char* const pass = "5252wifi";

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
const IPAddress outIp(10, 40, 10, 105);     // remote IP (not needed for receive)
const unsigned int outPort = 54321;          // remote port (not needed for receive)
const unsigned int localPort = 54321;        // local port to listen for UDP packets (here's where we send the packets)


OSCErrorCode error;
unsigned int ledState = LOW;              // LOW means led is *on*

#ifndef BUILTIN_LED
#ifdef LED_BUILTIN
#define BUILTIN_LED LED_BUILTIN
#else
#define BUILTIN_LED 13
#endif
#endif

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, ledState);    // turn *on* led

  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif

}


void led0(OSCMessage &msg) {
  ledState = msg.getInt(0);
  digitalWrite(BUILTIN_LED, ledState);
  Serial.print("/led0: ");
  Serial.println(ledState);
}

void led1(OSCMessage &msg) {
  ledState = msg.getInt(0);
  digitalWrite(BUILTIN_LED, ledState);
  Serial.print("/led1: ");
  Serial.println(ledState);
}

void led2(OSCMessage &msg) {
  ledState = msg.getInt(0);
  digitalWrite(BUILTIN_LED, ledState);
  Serial.print("/led2: ");
  Serial.println(ledState);
}

void led3(OSCMessage &msg) {
  ledState = msg.getInt(0);
  digitalWrite(BUILTIN_LED, ledState);
  Serial.print("/led3: ");
  Serial.println(ledState);
}
void led4(OSCMessage &msg) {
  ledState = msg.getInt(0);
  digitalWrite(BUILTIN_LED, ledState);
  Serial.print("/led4: ");
  Serial.println(ledState);
}

void led5(OSCMessage &msg) {
  ledState = msg.getInt(0);
  digitalWrite(BUILTIN_LED, ledState);
  Serial.print("/led5: ");
  Serial.println(ledState);
}
void led6(OSCMessage &msg) {
  ledState = msg.getInt(0);
  digitalWrite(BUILTIN_LED, ledState);
  Serial.print("/led6: ");
  Serial.println(ledState);
}


void loop() {
  parseUdp();
}


void parseUdp() {
  OSCBundle bundle;
  int size = Udp.parsePacket();

  if (size > 0) {
//    Serial.print("Size is");
//    Serial.println(size);
    while (size--) {
      bundle.fill(Udp.read());
    }
    if (!bundle.hasError()) {
      bundle.dispatch("/vals/0", led0);
      bundle.dispatch("/vals/1", led1);
      bundle.dispatch("/vals/2", led2);
      bundle.dispatch("/vals/3", led3);
      bundle.dispatch("/vals/4", led4);
      bundle.dispatch("/vals/5", led5);
      bundle.dispatch("/vals/6", led6);
    }
  } else {
    error = bundle.getError();
//    Serial.print("error: ");
//    Serial.println(error);
  }
}
