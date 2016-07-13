#include "PPD42NS.h"

/**
 * コンストラクタ
 */
PPD42NS::PPD42NS() {

}

/**
 * 初期化
 */
void PPD42NS::init(uint8_t _sensorPin, uint8_t _ledPin) {
  sensorPin = _sensorPin;
  ledPin = _ledPin;
  sensorTimer = millis();

  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

/**
 * アップデート関数
 */
bool PPD42NS::update(boolean debugDump) {
  bool updated = false;

  // パルスがLowの時間を検出
  int d = digitalRead(sensorPin);
  if (highLow == HIGH && d == LOW) {
    highLow = LOW;
    lowMicros = micros();
  }
  else if (highLow == LOW && d == HIGH) {
    highLow = HIGH;
    lowPulseOccupancy += micros() - lowMicros;
  }

  if ((millis() - sensorTimer) >= PPD42NS_SAMPLING_MILLIS) {
    digitalWrite(ledPin, HIGH);

    // 濃度を計算
    ratio = lowPulseOccupancy / (PPD42NS_SAMPLING_MILLIS * 10.0);
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;

    if (debugDump == true) {
      Serial.print(ratio);
      Serial.print("\t");
      Serial.println(concentration);
    }

    lowPulseOccupancy = 0;
    sensorTimer = millis();
    updated = true;
  }
  else {
    digitalWrite(ledPin, LOW);
  }

  return updated;
}

/**
 *
 */
float PPD42NS::getRatio() {
  return ratio;
}

/**
 *
 */
float PPD42NS::getConcentration() {
  return concentration;
}


