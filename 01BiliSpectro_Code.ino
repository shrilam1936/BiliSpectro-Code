/*

BiliSpectro Code
January 01, 2024

The software includes:

Data collection functions to accept blue (450nm) and green (510nm) led initial and transmitted light intensity
Functions and algorithms to calculate absorbance and concentration of FD&C Yellow 5 and Red 40 utilizing the Beer-Lambert Law
Penepheral Beat Amplidude algorithms for optical heart rate detection
Insertion sort algorithms to eliminate peripheral tissue light absorption

Note: Requires the MAX3010x Pulse and Proximity Sensor Library to be installed

*/


//PPG Sensor Global Variables

#include <Wire.h>
#include "MAX30105.h"

#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;


//LED and Photodiode Global Variables
#include <stdlib.h>

const int photodiode = A0;
const int greenLed = 11;
const int blueLed = 3;

const int numReadings = 15;

double blueReadings[numReadings];
double blueAbsorption[numReadings];
float avgBlue;

double greenReadings[numReadings];
double greenAbsorption[numReadings];
float avgGreen;


//Beer-Lambert Law Global Variables
double redEpsilon = 0.0557; //Molar Extinction Coefficent (FD&C Red 40)
double yellowEpsilon = 0.19; //Molar Extinction Coefficient (FD&C Yellow 5)

int pathLength = 3; //MEASURE AND CHANGE  

double finalGreenAbsorption; //Absorption at 510nm
double finalBlueAbsorption; //Absorption at 450nm

double yellowDye_Absorbance; //Absorption of yellow dye at 450nm (after differential measurement)

double redConc_mol; //Concentration (molarity)
double yellowConc_mol; 

float yellowDye_molWeight = 534.36;
float redDye_molWeight = 496.43;

double redDye_Concentration_FINAL; //Concentration after conversion to grams/liter or miligrams/mililiter 
double yellowDye_Concentration_FINAL; 


void setup() {

  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(photodiode, INPUT);

  Serial.begin(9600);

  incidentLight();
  calculateAbsorbance();
  calculateConcentration();

  //If performing data collection on a human: 

  //PPG_Setup();
  //PPG_Function();


}

void loop() {

}
