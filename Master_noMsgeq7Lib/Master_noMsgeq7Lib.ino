#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "MovingAverage.h"
#include <OSCMessage.h>
#include <OSCBundle.h>

//Wifi config
const int8_t ledPin = LED_BUILTIN;
const char* const ssid = "TonyAP";
const char* const pass = "5252wifi";
//const char* const ssid = "ScumbagLoft";
//const char* const pass = "Perfect!Racc00n";
const uint16_t localPort = 54321; // Local port to listen for UDP packets

//const uint32_t stepDuration = 1000 / 50;

IPAddress broadcastAddress;
WiFiUDP udp;

//bool sendPacket(const IPAddress& address, const uint8_t* buf, uint8_t bufSize);
//void receivePacket();

#define STROBE 16
#define RESET 14
#define DC_One A0

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];

//MovingAverage filter(5);
long filteredOutput[7] = {0};
long filteredInts[7] = {0};
int filterLength = 5;
MovingAverage filters[] = {MovingAverage(filterLength),
                           MovingAverage(filterLength),
                           MovingAverage(filterLength),
                           MovingAverage(filterLength),
                           MovingAverage(filterLength),
                           MovingAverage(filterLength),
                           MovingAverage(filterLength)
                          };

double soundVolume = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  //  pinMode(ledPin, OUTPUT);
  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

//
//  while (WiFi.status() != WL_CONNECTED) {
//    digitalWrite(ledPin, ! digitalRead(ledPin));
//    delay(500);
//    Serial.print('.');
//  }


  //  digitalWrite(ledPin, HIGH);
  Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());

  broadcastAddress = (uint32_t)WiFi.localIP() | ~((uint32_t)WiFi.subnetMask());
  Serial.print(F("Broadcast address: "));
  Serial.println(broadcastAddress);

  Serial.println(F("Starting UDP"));
  udp.begin(localPort);
  Serial.print(F("Local port: "));
  Serial.println(udp.localPort());

  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  //pinMode(DC_Two, INPUT);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  digitalWrite(RESET, LOW);
  delay(5);


}

long lastRead;

void loop() {

  Read_Frequencies();
  Graph_Frequencies();

  sendOscVals();
  //sendTest();

  delay(50);
}

void Read_Frequencies() {
  digitalWrite(RESET, HIGH);
  delayMicroseconds(200);
  digitalWrite(RESET, LOW);
  delayMicroseconds(200);

  //Read frequencies for each band
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(STROBE, HIGH);
    delayMicroseconds(50);
    digitalWrite(STROBE, LOW);
    delayMicroseconds(50);

    Frequencies_One[i] = analogRead(DC_One);
    //Frequencies_Two[freq_amp] = analogRead(DC_Two);
    filteredOutput[i] = filters[i].addSample(Frequencies_One[i]);
  }
}

void Graph_Frequencies() {
  for (int i = 0; i < 7; i++) {
    //    Serial.print(Frequencies_One[i]);
    //    Serial.print(" ");
    //    Serial.print(Frequencies_Two[i]);
    //    Serial.print(" ");
    //Serial.print( Frequencies_One[i] );
    Serial.print("    ");
    Serial.print( filteredOutput[i] );
    Serial.print("    ");

  }
  Serial.println();
}

//bool sendPacket(const IPAddress & address, const uint8_t* buf, uint8_t bufSize) {
//
//  Serial.print("bufSize is ");
//  Serial.println(bufSize);
//  udp.beginPacket(address, localPort);
//  udp.write(buf, bufSize);
//  return (udp.endPacket() == 1);
//}

void sendOscVals() {
  OSCBundle bndl;
  bndl.add("/vals/0").add((int32_t) filteredOutput[0]);
  bndl.add("/vals/1").add((int32_t) filteredOutput[1]);
  bndl.add("/vals/2").add((int32_t) filteredOutput[2]);
  bndl.add("/vals/3").add((int32_t) filteredOutput[3]);
  bndl.add("/vals/4").add((int32_t) filteredOutput[4]);
  bndl.add("/vals/5").add((int32_t) filteredOutput[5]);
  bndl.add("/vals/6").add((int32_t) filteredOutput[6]);

  udp.beginPacket(broadcastAddress, localPort);
  bndl.send(udp);
  udp.endPacket();
  bndl.empty();
}

void sendTest() {

  OSCMessage msg("/print");
  //msg.add("hello, osc.");
  msg.add((int32_t)filteredOutput[0]);
  udp.beginPacket(broadcastAddress, localPort);
  msg.send(udp);
  udp.endPacket();
  msg.empty();
  
}

//void receivePacket() {
//  bool led;
//  udp.read((uint8_t*)&led, sizeof(led));
//  udp.flush();
//  if (udp.destinationIP() != broadcastAddress) {
//    Serial.print(F("Client with IP "));
//    Serial.print(udp.remoteIP());
//    Serial.print(F(" turned led "));
//    Serial.println(led ? F("off") : F("on"));
//  } else {
//    Serial.println(F("Skip broadcast packet"));
//  }
//}
