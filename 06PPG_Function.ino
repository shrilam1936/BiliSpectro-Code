/*
PPG Function
Insertion Sort algorithm to eliminate peripheral tissue and bone absorption and isolate arterial absorption

*/

void PPG_Function(){
  
  // Perform insertion sort
  for (int i = 1; i < RATE_SIZE; ++i) {
    int key = rates[i];
    int j = i - 1;

    // Move elements of samples[0..i-1] that are greater than key to one position ahead of their current position
    while (j >= 0 && rates[j] > key) {
      rates[j + 1] = rates[j];
      j = j - 1;
    }

    rates[j + 1] = key;
  }

  // The middle value after sorting is considered arterial absorption
  int arterialValue = samples[numSamples / 2];


}