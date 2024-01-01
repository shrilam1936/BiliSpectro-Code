/*
Incident Light Collection
Collects data from 450nm (blue) and 510nm (green) LEDs to be used as i0 (incident light) in the Beer-Lambert equation
*/


void incidentLight(){ //setup function
  
  Serial.println("Beginning incident light collection");
  //Green LED (510nm): Turn on, collect values, find average, turn off (INCIDENT LIGHT)
  digitalWrite(greenLed, HIGH);

  for(int i=0; i<numReadings; i++){
    delay(1000);
    avgGreen += analogRead(photodiode);
  }
  avgGreen/=15;
  digitalWrite(greenLed, LOW);

  //Blue LED (450nm): Turn on, collect values, find average, turn off (INCIDENT LIGHT)
  digitalWrite(blueLed, HIGH);

  for(int i=0; i<numReadings; i++){
    delay(1000);
    avgBlue += analogRead(photodiode);
  }
  avgBlue/=15;

  digitalWrite(blueLED, LOW);


}
