#include "DN7C3JA020.h"

/**
 * コンストラクタ
 */
DN7C3JA020::DN7C3JA020() {

}

/**
 * 初期化
 */
void DN7C3JA020::init(uint8_t _sensorPin, uint8_t _ledPin) {
  sensorPin = _sensorPin;
  ledPin = _ledPin;
  samplingIndex = 0;
  ppm = 0.0;
  sensorTimer = micros();

  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

/**
 * アップデート関数
 */
bool DN7C3JA020::update(boolean debugDump) {
  bool updated = false;

  // 一周期(T = 10ms)まわるまでwait
  if (micros() - sensorTimer > DN7C3JA020_PERIODIC_MICROS) {
    // power on the LED
    digitalWrite(ledPin, LOW);
    delayMicroseconds(DN7C3JA020_RISEUP_MICROS);

    // read the dust value
    int dustVal = analogRead(sensorPin);
    ppm += dustVal;

    // wait micros of pulse width
    delayMicroseconds(DN7C3JA020_WAIT_MICROS);

    // turn the LED off
    digitalWrite(ledPin, HIGH);

    if (++samplingIndex >= DN7C3JA020_NUM_SAMPLINGS) {
      voltage = ppm / DN7C3JA020_NUM_SAMPLINGS * 0.0049;
      dustDensity = 0.17 * voltage - 0.1;
      ppmPerCf = (voltage - 0.0256) * 120000;

      if (ppmPerCf < 0) {
        ppmPerCf = 0;
      }
      if (dustDensity < 0) {
        dustDensity = 0;
      }
      if (dustDensity > 0.5) {
        dustDensity = 0.5;
      }

      if (debugDump == true) {
        Serial.print(voltage);
        Serial.print(F("\t"));
        Serial.print(dustDensity);
        Serial.print(F("\t"));
        Serial.print(ppmPerCf);
        Serial.println(F("\t"));
      }

      ppm = 0.0;
      samplingIndex = 0;

      updated = true;
    }

    sensorTimer = micros();
  }

  return updated;
}

/**
 *
 */
float DN7C3JA020::getVoltage() {
  return voltage;
}

/**
 *
 */
float DN7C3JA020::getDustDensity() {
  return dustDensity;
}

/**
 *
 */
float DN7C3JA020::getPpmPerCf() {
  return ppmPerCf;
}

