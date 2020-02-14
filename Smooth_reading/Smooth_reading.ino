// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 40;
// sensor 1
int readings[3][numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total[] ={0,0,0};                  // the running total
float average[] = {0,0,0};                // the average
int sensorValue[]={0,0,0};
int inputPin[] = {A2,A3,A4};

void cal(){
  for (int i=0;i<3;i++){
    // subtract the last reading:
    total[i] = total[i] - readings[i][readIndex];
    // read from the sensor:
    readings[i][readIndex] = analogRead(inputPin[i]);
    // add the reading to the total:
    total[i] = total[i] + readings[i][readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
  }

  // calculate the average:
  average[i] = abs(total[i] / numReadings);
  // send it to the computer as ASCII digits
  //Serial.print(average[i]);
  //Serial.print("\t");
  //delay(10);        // delay in between reads for stability
}
//Serial.println();
analogWrite(6,10);
delay(1);
analogWrite(6,0);
delay(1);
}
void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    for (int i=0; i<3; i++){
      readings[i][thisReading] = 0;
    }
  }
  while(millis()<5000){
    cal();
  }
}

void loop() {
  //analogWrite(6,0);
  for (int i=0; i<3; i++){
    sensorValue[i]=analogRead(inputPin[i]);
    sensorValue[i]=sensorValue[i]-average[i];
    Serial.print(sensorValue[i]);
    Serial.print("\t");
    delay(10); 
  }
    Serial.println();
  
}
