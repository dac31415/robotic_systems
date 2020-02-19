#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

const int numReadings = 40;
unsigned int readings[3][numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
unsigned int total[] = {0, 0, 0};               // the running total
float average[] = {0, 0, 0};              // the average
unsigned int sensorValue[] = {0, 0, 0};
int inputPin[] = {A2, A3, A4};
int sensorMin[] = {1023, 1023, 1023};
int sensorMax[] = {0, 0, 0};



// Variables to remember our
// motor power for Left and Right.
// Byte stores 0 to 255
byte l_power;
byte r_power;

unsigned int linea = 0;
unsigned int pos = 0;
unsigned int centre = 0, error = 0, error_anterior = 0;

// Calibración sensores
void cal() {
  for (int i = 0; i < 3; i++) {
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
    delay(10);        // delay in between reads for stability

  }
  //Serial.println();
  //analogWrite(6,10);
  //delay(1);
  //analogWrite(6,0);
  //delay(1);
}




void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(6, OUTPUT);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    for (int i = 0; i < 3; i++) {
      readings[i][thisReading] = 0;
    }
  }
  while (millis() < 5000) {
    cal();
  }
  // Motors def
  pinMode( L_PWM_PIN, OUTPUT );
  pinMode( L_DIR_PIN, OUTPUT );
  pinMode( R_PWM_PIN, OUTPUT );
  pinMode( R_DIR_PIN, OUTPUT );

  // Set initial direction for l and r
  // Which of these is foward, or backward?
  // LOW FORWARD , HIGH BACKWARDS
  digitalWrite( L_DIR_PIN, LOW  );
  digitalWrite( R_DIR_PIN, LOW );

  // Set initial l_power and r_power values.
  l_power = 0;
  r_power = 0;

}

void loop()
{

  for (int i = 0; i < 3; i++) {
    sensorValue[i] = analogRead(inputPin[i]);

    sensorValue[i] = abs(sensorValue[i] - average[i]);
    if (sensorValue[i] < 100) {
      sensorValue[i] = 0;
    }
    else if (sensorValue[i] > 200) {
      sensorValue[i] = 500;
    }
    
    //sensorValue[i] = map(sensorValue[i], sensorMin[i], sensorMax[i], 1000, 0);
    sensorValue[i] = constrain(sensorValue[i], 0, 500);
    Serial.print(sensorValue[i]);
    Serial.print("\t");
    delay(10);
  }

  //Serial.println();

  linea = (sensorValue[1]) + (sensorValue[2]) + (sensorValue[3]);
  pos = sensorValue[1] * 0 + sensorValue[2] * 1 + sensorValue[3] * 2;
  //int set_point = 200 / 2;
  //centre = pos / line;
  Serial.print("line ");
  Serial.println(linea);
  //delay(100);
  /*
    if(line==0){
    error=error_anterior;
    }
    else{
    error = centre - set_point;
    error_anterior = error;
    }

  */



}





/*


  const int numReadings = 40;
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
    sensorValue[i]=abs(sensorValue[i]-average[i]);
    Serial.print(sensorValue[i]);
    Serial.print("\t");
    delay(10);
    }

    Serial.println();

  }

*/
