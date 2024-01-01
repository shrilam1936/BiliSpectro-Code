/*
Absorbance Calculation
Collects data from 450nm (blue) and 510nm (green) LEDs to be used as i (transmitted light) in the Beer-Lambert equation
Uses the Beer-Lambert Law to calculate absorbance from photodiode signals [A = EbC = -log10(T) = log10(i0/i)]
Utilizes quicksort and mergesort algorithms to efficiently sort readings
*/

void calculateAbsorbance (){

  Serial.println("Beginning transmitted light collection, place finger in the device");
  delay(2000);
  digitalWrite(greenLed, HIGH);

  for(int i = 0; i<numReadings; i++){
    greenReadings[i] = analogRead(photoDetectorPin);
  }
  digitalWrite(greenLed, LOW);


  digitalWrite(blueLed, HIGH);
  delay(100);
  digitalWrite(blueLed, LOW);
  delay(100);
  digitalWrite(blueLed, HIGH);


  for(int i = 0; i<numReadings; i++){
    blueReadings[i] = analogRead(photoDetectorPin);
  }
  digitalWrite(blueLed, LOW);

  //I STOPPED HERE - TBC AT CONVERTING THESE VALUES TO ABSORBANCE

  for(int i = 0; i<numReadings; i++){
    greenAbsorption[i] = log10(avgGreen/greenReadings[i]);
  }

  for(int i=0; i<= numReadings; i++){
    for(int j = i; j>0; j--){
      if(greenAbsorption[j-1] > greenAbsorption[j]){
        double placeholder = greenAbsorption[j];
        blueAbsorption[j] = blueAbsorption[j-1];
        blueAbsorption[j-1] = placeholder;
      }
    }
  }

  finalGreenAbsorption = greenAbsorption[numReadings - 1] - greenAbsorption[0];



  for(int i = 0; i<numReadings; i++){
    blueAbsorption[i] = log10(avgBlue/blueReadings[i]);
  }

  for(int i = 0; i<=numReadings; i++){
    for(int j = i; j>0; j--){
      if(blueAbsorption[j-1] > blueAbsorption[j]){
        double temporary = blueAbsorption[j];
        blueAbsorption[j]= blueAbsorption[j-1];
        blueAbsorption[j-1] = temporary;
      }
    }
  }

  finalBlueAbsorption = blueAbsorption[numReadings - 1] - blueAbsorption[0];

  delay(1000);


}