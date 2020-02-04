// Every ten seconds take the average of three moisture sensor readings
// If average of readings is above watering threshold, turn on pump for five seconds

// assign pins
int sensor = 0;
int pumpControl = 7;

// time variables
unsigned long wateringTime = 0;
unsigned long daysPast = 0;
unsigned long conversion = (unsigned long) 1000 * 60 * 60 * 24;

// set threshold for watering
int wateringThreshold = 400;

// number of measurements to average
int numAve = 5;
int sum = 0;
int aveMeasurement = 0;

void setup() {
  Serial.begin(9600);

  // set up pins
  pinMode(sensor, INPUT);
  pinMode(pumpControl, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // set pump to off
  digitalWrite(pumpControl, LOW);
}

void loop() {
  // take the average of multiple measurements
  sum = 0;
  for (int i = 0; i < numAve; i++) {
    sum += analogRead(sensor);
  }
  aveMeasurement = sum / numAve;

  Serial.print("Sensor reading:\t");
  Serial.println(aveMeasurement);

  // compare average measurement to the watering threshold
  if (aveMeasurement >= wateringThreshold) {
    // turn the pump on for five seconds
    digitalWrite(pumpControl, HIGH);
    delay(5000);
    digitalWrite(pumpControl, LOW);
    // set the watering time
    wateringTime = millis();
    // wait 15 minutes
    delay(300000);
  }

  // calculate the days since last watered
  daysPast = (millis() - wateringTime) / conversion;

  Serial.print("Days since watering:\t");
  Serial.println(daysPast);

  // turn LED on if watered within one day
  if (daysPast < 1){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }

  // display days since last watered by blinking LED
  for (int i = 0; i < daysPast; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }

  // wait 10 seconds
  delay(10000);
}
