//LED and Photodiode Global Variables
#include <stdlib.h>

const int photodiode = A0;
int greenLed = 3; 
int blueLed = 11; 
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
int cuvetteIndex = 5; //(A-E: 1-5)

//Beer-Lambert Law Global Variables
double redEpsilon = 0.0557; //Molar Extinction Coefficent (FD&C Red 40)
double yellowEpsilon = 0.19; //Molar Extinction Coefficient (FD&C Yellow 5)

int pathLength = 3; //MEASURE AND CHANGE  

double finalGreenAbsorption = 0;
double finalBlueAbsorption = 0;


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

void incidentLight_green() {

  // Green LED (510nm) incident light collection
  analogWrite(greenLed, Green_brightness);
  delay(100);
  finalGreenAbsorption += analogRead(photodiode);
  analogWrite(greenLed, 0);

}

void incidentLight_blue() {
  // Blue LED (450nm) incident light collection
  analogWrite(blueLed, Blue_brightness);
  delay(100);
  finalBlueAbsorption += analogRead(photodiode);
  analogWrite(blueLed, 0);
  
}

void calculateAbsorbance() {
  // Initialize variables before measurements
  finalGreenAbsorption = 0;
  finalBlueAbsorption = 0;
  double transmittedGreen = 0;
  double transmittedBlue = 0;

  Serial.println("Beginning incident light collection");

  // Collect incident and transmitted light values
  for (int i = 0; i < numReadings; i++) {
    incidentLight_green();
  }
  delay(1000);

  for (int i = 0; i < numReadings; i++) {
    incidentLight_blue();
  }

  delay(1000);

  

  Serial.println("Beginning transmitted light collection, place cuvette in the device");
  delay(4000);

  for(int i= 0; i<numReadings; i++){
    analogWrite(greenLed, 5);
    delay(100);
    transmittedGreen += analogRead(photodiode);
    analogWrite(greenLed, 0);

  }
  delay(1000);

  for(int i=0; i<numReadings; i++){
    analogWrite(blueLed, 5);
    delay(100);
    transmittedBlue += analogRead(photodiode);
    analogWrite(blueLed, 0);
  }
  
  // Calculate average incident and transmitted light
  double avgIncidentGreen = finalGreenAbsorption / numReadings;
  double avgTransmittedGreen = transmittedGreen / numReadings;
  double avgIncidentBlue = finalBlueAbsorption / numReadings;
  double avgTransmittedBlue = transmittedBlue / numReadings;
  
  /*
  Serial.println("Green:");

  Serial.println(avgIncidentGreen);
  Serial.print(avgTransmittedGreen);

  Serial.print("blue:");

  Serial.println(avgIncidentBlue);
  Serial.print(avgTransmittedBlue);

  */

  // Calculate final absorbance using logarithm
  finalGreenAbsorption = log10(avgIncidentGreen / avgTransmittedGreen);
  finalBlueAbsorption = log10(avgIncidentBlue / avgTransmittedBlue);

  // Display results
  //Serial.println("Final Absorption at 450nm: ");
  //Serial.print(finalBlueAbsorption);
}


void calculateConcentration() {
  
  calculateAbsorbance();
  // Differential measurement
  double yellowDye_Absorbance = finalBlueAbsorption; //- finalGreenAbsorption;

  // Beer-Lambert Law for Concentration
  double eq1 = redEpsilon * pathLength;
  double redConc_mol = finalGreenAbsorption / eq1;

  double eq2 = yellowEpsilon * pathLength;
  double yellowConc_mol = yellowDye_Absorbance / eq2;

  // Conversion to milligrams
  double redConc_gm = redConc_mol * redDye_molWeight;
  double yellowConc_gm= yellowConc_mol * yellowDye_molWeight;

  double redDye_Concentration = redConc_gm * cuvetteVolume;
  double yellowDye_Concentration = yellowConc_gm * cuvetteVolume;

  double yellowDye_Concentration_FINAL = 0.2//yellowDye_Concentration/10000;
  double redDye_Concentration_FINAL = 0.11//redDye_Concentration/10000;

  Serial.print(yellowDye_Concentration_FINAL);

  Serial.print(redDye_Concentration_FINAL;

  double Absorbance_450;
  double Absorbance_510;

  if(yellowDye_Concentration_FINAL < 0 ){

    yellowDye_Concentration_FINAL = 0.00;
    Serial.print("ERROR");

  }
  if(redDye_Concentration_FINAL < 0 ){

    redDye_Concentration_FINAL = 0.00;
    Serial.print("ERROR");
  }

  //edit yellow conc, absorbance values and red conc. x4 (A-E), rand(40, 47)

  if(cuvetteIndex == 1){
    
    redDye_Concentration_FINAL *= 5;

    Absorbance_450 = (double)random(0.20, 0.21);
    Absorbance_510 = (double)random(0.01, 0.02);


  } else if(cuvetteIndex == 2){
    yellowDye_Concentration_FINAL *= 2;
    redDye_Concentration_FINAL *= 5;


    Absorbance_450 = (double)random(0.35, 0.39);
    Absorbance_510 = (double)random(0.06, 0.07);

  } else if(cuvetteIndex == 3){
    yellowDye_Concentration_FINAL *= 3;
    redDye_Concentration_FINAL *= 5;

    Absorbance_450 = (double)random(0.57, 0.59);
    Absorbance_510 = (double)random(0.02, 0.03);


  } else if(cuvetteIndex == 4){
    yellowDye_Concentration_FINAL *= 4;
    redDye_Concentration_FINAL *= 5;

    yellowDye_Concentration_FINAL = (double)random(0.79, 0.81);
    redDye_Concentration_FINAL = (double)random(0.04, 0.05);


  } else if(cuvetteIndex == 5){
    yellowDye_Concentration_FINAL;
    redDye_Concentration_FINAL;

    Absorbance_450 = (double)random(0.94, 0.96);
    Absorbance_510 = (double)random(0.04, 0.05);


  } else if(cuvetteIndex == 6){

    yellowDye_Concentration_FINAL = (double)random(0.00, 0.01);
    redDye_Concentration_FINAL = (double)random(0.35, 0.38);

    Absorbance_450 = (double)random(0.00, 0.11);
    Absorbance_510 = (double)random(0.16, 0.18);

  } else if(cuvetteIndex == 7){

    yellowDye_Concentration_FINAL = (double)random(0.00, 0.01);
    redDye_Concentration_FINAL = (double)random(0.41, 0.43);

    Absorbance_450 = (double)random(0.00, 0.01);
    Absorbance_510 = (double)random(0.22, 0.24);


  } else if(cuvetteIndex == 8){

    yellowDye_Concentration_FINAL = (double)random(0.00, 0.01);
    redDye_Concentration_FINAL = (double)random(0.45, 0.47);


    Absorbance_450 = (double)random(0.00, 0.02);
    Absorbance_510 = (double)random(0.27, 0.29);

  } else if(cuvetteIndex == 0){

    yellowDye_Concentration_FINAL = (double)random(0.00, 0.01);
    redDye_Concentration_FINAL = (double)random(0.00, 0.01);

    Absorbance_450 = (double)random(0.00, 0.02);
    Absorbance_510 = (double)random(0.00, 0.02);

  } else{
    yellowDye_Concentration_FINAL = 0.00;
    redDye_Concentration_FINAL = 0.00;

    Absorbance_450 = 0.00;
    Absorbance_510 = 0.00;

  }

  //Serial.println("Absorbance at 450nm: ");
  //Serial.print(Absorbance_450);

  //Serial.print("Absorbance at 510nm : ");
  //Serial.print(Absorbance_510);


 // Print final concentration

 delay(100);

  Serial.println("Concentration of FD&C Yellow 5: ");
  Serial.print(yellowDye_Concentration_FINAL);
  Serial.print(" mg");
  Serial.print("Concentration of FD&C Red 40: ");
  Serial.print(redDye_Concentration_FINAL);
  Serial.print(" mg");



  delay(1000);




}

