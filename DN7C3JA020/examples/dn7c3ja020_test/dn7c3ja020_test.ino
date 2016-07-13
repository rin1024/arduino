#include <DN7C3JA020.h>

#define SENSOR_PIN A0
#define LED_PIN 2

DN7C3JA020 sensor;

void setup() {
  Serial.begin(115200);

  sensor.init(SENSOR_PIN, LED_PIN);
}

void loop() {
  if (sensor.update() == true) {
    float voltage = sensor.getVoltage();
    float dustDensity = sensor.getDustDensity();
    float ppmPerCf = sensor.getPpmPerCf();

    Serial.print(voltage);
    Serial.print("\t");
    Serial.print(dustDensity);
    Serial.print("\t");
    Serial.println(ppmPerCf);
  }
}

