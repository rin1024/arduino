#include <S28BYJ48.h>

#define LED_PIN 13

S28BYJ48 motor(8,9,10,11);

void setup(){
  Serial.begin(115200);
  Serial.println("start");

  motor.setStepDuration(1200);

  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  while (Serial.available() > 0) {
    int serialData = Serial.read();

    digitalWrite(LED_PIN, HIGH);
    Serial.println("rotate");
    // clockwise
    // via https://arduino-info.wikispaces.com/SmallSteppers
    // 64 * 64 = 4096[steps]
    motor.step(4096);
    // anti-clockwise
    motor.step(-4096);
    digitalWrite(LED_PIN, LOW);
  }
}

