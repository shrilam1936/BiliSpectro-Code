//LED and Photodiode Global Variables
#include <stdlib.h>

const int photodiode = A0;
int greenLed = 3; 
int blueLed = 6; 
int Green_brightness = 255; // can be value between 0 and 255
int Blue_brightness = 255;


const int numReadings = 15;

double blueReadings[numReadings];
double blueAbsorption[numReadings];
double avgBlue = 0;

double greenReadings[numReadings];
double greenAbsorption[numReadings];
double avgGreen = 0;


double cuvetteVolume  = 7.00;


//Beer-Lambert Law Global Variables
double redEpsilon = 0.0557; //Molar Extinction Coefficent (FD&C Red 40)
double yellowEpsilon = 0.19; //Molar Extinction Coefficient (FD&C Yellow 5)

int pathLength = 3; //MEASURE AND CHANGE  

double finalGreenAbsorption = 0.00;
double finalBlueAbsorption = 0.00;


double yellowDye_molWeight = 534.36;
double redDye_molWeight = 496.43;



void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(photodiode, INPUT);

  Serial.begin(9600);

  
  calculateConcentration();
  
}

void loop(){

}


void calculateAbsorbance() {
  // Initialize variables before measurements
  finalGreenAbsorption = 0.00;
  finalBlueAbsorption = 0.00;
  double incidentGreen = 0.00;
  double incidentBlue = 0.00;
  double transmittedGreen = 0.00;
  double transmittedBlue = 0.00;

  // Collect incident and transmitted light values

  Serial.println("Beginning incident light collection");

  // Green LED (5100nm) incident light collection
  for (int i = 0; i < numReadings; i++) {
    analogWrite(greenLed, Green_brightness);
    delay(100);
    incidentGreen += analogRead(photodiode);
    analogWrite(greenLed, 0);
  }
  delay(1000);

  // Blue LED (450nm) incident light collection

  for (int i = 0; i < numReadings; i++) {
    analogWrite(blueLed, Blue_brightness);
    delay(100);
    incidentBlue += analogRead(photodiode);
    analogWrite(blueLed, 0);
  }

  delay(1000);

  

  Serial.println("Beginning transmitted light collection, place cuvette in the device");
  delay(4000);


  for(int i= 0; i<numReadings; i++){
    analogWrite(greenLed, 150);
    delay(100);
    transmittedGreen += analogRead(photodiode);
    analogWrite(greenLed, 0);

  }
  delay(1000);

  for(int i=0; i<numReadings; i++){
    analogWrite(blueLed, 150);
    delay(100);
    transmittedBlue += analogRead(photodiode);
    analogWrite(blueLed, 0);
  }

  delay(100);
  
  // Calculate average incident and transmitted light
  double avgIncidentGreen = incidentGreen / numReadings;
  double avgTransmittedGreen = transmittedGreen / numReadings;
  double avgIncidentBlue = incidentBlue / numReadings;
  double avgTransmittedBlue = transmittedBlue / numReadings;
  
  
  Serial.println("Green:");

  Serial.println(avgIncidentGreen);
  Serial.print(avgTransmittedGreen);

  Serial.print("blue:");

  Serial.println(avgIncidentBlue);
  Serial.print(avgTransmittedBlue);

  

  // Calculate final absorbance using logarithm
  finalGreenAbsorption = log10(avgIncidentGreen / avgTransmittedGreen);
  //finalGreenAbsorption = log10(avgTransmittedGreen / avgIncidentGreen);
  finalBlueAbsorption = log10(avgIncidentBlue / avgTransmittedBlue);

  // Display results
  //Serial.println("Final Absorption at 450nm: ");
  //Serial.print(finalBlueAbsorption);
}


void calculateConcentration() {
  
  calculateAbsorbance();

  double yellowDye_Absorbance = 0.00;

  double eq1 = 0.00;
  double redConc_mol = 0.00;

  double eq2 = 0.00;
  double yellowConc_mol =0.00;

  double redConc_gm = 0.00;
  double yellowConc_gm= 0.00;

  double redDye_Concentration = 0.00;
  double yellowDye_Concentration = 0.00;

  double yellowDye_Concentration_FINAL = 0.00;
  double redDye_Concentration_FINAL = 0.00;

  // Differential measurement
  yellowDye_Absorbance = finalBlueAbsorption; //- finalGreenAbsorption;

  // Beer-Lambert Law for Concentration
  eq1 = redEpsilon * pathLength;
  redConc_mol = finalGreenAbsorption / eq1;

  eq2 = yellowEpsilon * pathLength;
  yellowConc_mol = yellowDye_Absorbance / eq2;

  // Conversion to milligrams
  redConc_gm = redConc_mol * redDye_molWeight;
  yellowConc_gm= yellowConc_mol * yellowDye_molWeight;

  redDye_Concentration = redConc_gm * cuvetteVolume;
  yellowDye_Concentration = yellowConc_gm * cuvetteVolume;

  yellowDye_Concentration_FINAL = yellowDye_Concentration;
  redDye_Concentration_FINAL = redDye_Concentration;


if(yellowDye_Concentration_FINAL < 0 ){

    yellowDye_Concentration_FINAL = 0.00;
    Serial.print("ERROR");

  }
  if(redDye_Concentration_FINAL < 0 ){

    redDye_Concentration_FINAL = 0.00;
    Serial.print("ERROR");
  }

  delay(100);

  Serial.println("Concentration of FD&C Yellow 5: ");
  Serial.print(yellowDye_Concentration_FINAL);
  Serial.print(" mg");
  Serial.print("Concentration of FD&C Red 40: ");
  Serial.print(redDye_Concentration_FINAL);
  Serial.print(" mg");



  delay(1000);





}


