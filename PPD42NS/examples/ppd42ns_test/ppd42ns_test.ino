#include <PPD42NS.h>

#define SENSOR_PIN A0
#define LED_PIN 13

PPD42NS sensor;

void setup() {
  Serial.begin(115200);

  sensor.init(SENSOR_PIN, LED_PIN);
}

void loop() {
  if (sensor.update() == true) {
    float ratio = sensor.getRatio();
    float concentration = sensor.getConcentration();

    Serial.print(ratio);
    Serial.print("\t");
    Serial.println(concentration);
  }
}

