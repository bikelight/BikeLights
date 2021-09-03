#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <TaskScheduler.h>
#include "FastLED.h"
#include <Vector.h>


//--------------------------------

const char* ssid = "TonyAP";
const char* password = "5252wifi";

//--------------------------------

WiFiUDP Udp;
unsigned int localUdpPort = 54321;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets

//--------------------------------

OSCErrorCode error;
unsigned int ledState;          // LOW means led is *on*

int soundVals[7] = {0};

//--------------------------------

// FastLED

FASTLED_USING_NAMESPACE

#define LED_PINS    2
#define COLOR_ORDER GRB
#define CHIPSET     WS2811 // WS2811 LPD8806
#define NUM_LEDS    75

#define BRIGHTNESS  255  // reduce power consumption
#define LED_DITHER  255  // try 0 to disable flickering
#define CORRECTION  TypicalLEDStrip

#define FRAMES_PER_SECOND  120

const int8_t ledPin = LED_BUILTIN;

//--------------------------------

bool doEffect = false;
int effectCounter = 0;

int effectNumber = 0;
int animationNumber = 0;

uint8_t gHue = 0; // rotating "base color" used by many of the patterns



int baseColorValue = 25;
// baseColorValue = 10.0;

CRGB leds[NUM_LEDS]; // Define the array of leds

int BRIGHTNESS_SCALE[] = {
  0, 1, 2, 3, 4, 5, 7, 9, 12, 15, 18, 22, 27, 32, 38, 44, 51, 58, 67, 76, 86, 96, 108, 120, 134,
  148, 163, 180, 197, 216, 235, 255
};
int MAX_BRIGHTNESS = sizeof(BRIGHTNESS_SCALE);

//--------------------------------

// Callback methods prototypes
Scheduler ts;

void tIncHue();
void tNextPattern();
void tDoLight();
void tDoTop();


//Tasks
Task t1(20 * TASK_MILLISECOND , TASK_FOREVER, &tIncHue, &ts, true);
Task t2(30 * TASK_SECOND, TASK_FOREVER, &tNextPattern, &ts, true);
Task t3((1000 * TASK_MILLISECOND) / FRAMES_PER_SECOND, TASK_FOREVER, &tDoLight, &ts, true);


//--------------------------------
typedef struct  effect;
void star( effect *self);



//--------------------------------


void setup()
{
  Serial.begin(115200);
  Serial.println();
  //pinMode(2, OUTPUT);

  // FastLED setup
  FastLED.addLeds<CHIPSET, 2, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(CORRECTION);
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setDither(LED_DITHER);
  FastLED.show(); // needed to reset leds to zero

  //Wifi setup
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  //  while (WiFi.status() != WL_CONNECTED)
  //  {
  //    digitalWrite(ledPin, ! digitalRead(ledPin));
  //    delay(500);
  //    Serial.print(".");
  //  }
  Serial.println(" connected");

  //Start UPD server
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

void loop()
{
  parseUdp();

  ts.execute();
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  animationNumber = (animationNumber + 1) % ARRAY_SIZE( gPatterns);
}
