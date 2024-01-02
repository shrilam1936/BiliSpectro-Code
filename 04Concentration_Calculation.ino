/*
Concentration Calculation
Calculates concentration of red and yellow dye using the Beer Lambert Law [Conc = Absorbance/(molar extinction coefficent * path length)] 
(molar extinction coefficient derived from proof of concept-- standard curves)
Converts concentration from mol/L to g/l
*/

void calculateConcentration(){ 

  //PPG_Function(); //Call PPG_Function if using a finger
  //Differential measurement
  yellowDye_Absorbance = finalBlueAbsorption - finalGreenAbsorption;

  //Beer-Lambert Law for Concentration

  double eq1 = redEpsilon * pathLength;
  redConc_mol = finalGreenAbsorption/ eq1;

  double eq2 = yellowEpsilon * pathLength;
  yellowConc_mol = yellowDye_Absorbance/eq2;

  //Conversion to miligrams

  redDye_Concentration_FINAL = redConc_mol * redDye_molWeight;
  yellowDye_Concentration_FINAL = yellowConc_mol * yellowDye_molWeight;

  //Print final concnetration!!
  //Print final concnetration!!
  Serial.println("Concentration of FD&C Yellow 5: ");
  Serial.print(yellowDye_Concentration_FINAL);
  Serial.print(" g/l");
  Serial.println("Concentration of FD&C Red 40: ");
  Serial.print(redDye_Concentration_FINAL);
  Serial.print(" g/l");


  
  delay(1000);

}
