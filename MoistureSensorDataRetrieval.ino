// Print all data stored in EEPROM

#include<EEPROM.h>

void setup() {
  Serial.begin(9600);

  int dataPoint;
  for (int i = 0; i < EEPROM.length(); i += sizeof(int))
  {
    EEPROM.get(i, dataPoint);

    Serial.print(dataPoint);
    Serial.print('\n');
  }
}

void loop() {

}
