// Take a measurement from the moisture sensor ever 15 minutes
// and save values in EEPROM

#include<EEPROM.h>

int dataPin = 0;
int address = 0;

void setup() {
  //Setup pins
  pinMode(dataPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Five minute delay warning
  for (int i = 5; i > 0; i--){
    for (int j = i; j > 0; j--){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
    delay(60000);
  }

  digitalWrite(LED_BUILTIN, HIGH);

  // Clear the EEPROM
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

void loop() {
  // read voltage from Capacitive Moisture Sensor
  int dataPoint = analogRead(dataPin);

  // Save measurement to EEPROM
  EEPROM.put(address, dataPoint);

  // Blink LED to show data point being recorded
  for (int i = 0; i < 20; i++){
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }

  // move to next address
  address += sizeof(int);

  // check if EEPROM memmory is full
  if (address >= EEPROM.length()){
    digitalWrite(LED_BUILTIN, LOW);
    while(true){
    }
  }

  // Wait 15 minutes (minus the 4 second blinking)
  delay(896000);
}
