/******************************************************************************
  SparkFun Spectrum Shield Demo
  Wes Furuya @ SparkFun Electronics
  January 2020
  https://github.com/sparkfun/Spectrum_Shield

  This sketch shows the basic functionality of the Spectrum Shield, using the Serial Monitor/Plotter.

  The Spectrum Shield code is based off of the original demo sketch by Toni Klopfenstein @SparkFun Electronics.
  This sketch is available in the Spectrum Shield repository.

  Development environment specifics:
  Developed in Arduino 1.8.5
*********************************************************************************/
#include "MovingAverage.h"
//Declare Spectrum Shield pin connections
#define STROBE 16
#define RESET 14
#define DC_One A0
//#define DC_Two A1

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];
int i;

//MovingAverage filter(5);
double filteredOutput[7] = {0};

MovingAverage filters[] = {MovingAverage(5), 
                           MovingAverage(5),
                           MovingAverage(5),
                           MovingAverage(5),
                           MovingAverage(5),
                           MovingAverage(5),
                           MovingAverage(5)};

/********************Setup Loop*************************/
void setup() {
  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  //pinMode(DC_Two, INPUT);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  digitalWrite(RESET, LOW);
  delay(5);

  Serial.begin(115200);
}


/**************************Main Function Loop*****************************/
void loop() {


  Read_Frequencies();
  Graph_Frequencies();

  delay(10);

}


/*******************Pull frquencies from Spectrum Shield********************/
void Read_Frequencies() {
  digitalWrite(RESET, HIGH);
  delayMicroseconds(200);
  digitalWrite(RESET, LOW);
  delayMicroseconds(200);

  //Read frequencies for each band
  for (i = 0; i < 7; i++)
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

/*****************Print Out Band Values for Serial Plotter*****************/
void Graph_Frequencies() {
  for (i = 0; i < 1; i++)
  {
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
