/*
Heart Rate Detection
Optical heart rate detection using the Penpheral Beat Amplitude (PBA) algorithm

*/

void detectHR (){ 


  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true){ //If a beat is sensed--
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  if (irValue < 50000)
  Serial.print(" No finger?");

  Serial.println();



  Serial.print(", Avg BPM=");
  Serial.println(beatAvg);


  delay(1000);



}

