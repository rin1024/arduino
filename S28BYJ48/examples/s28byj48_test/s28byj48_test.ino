#include <S28BYJ48.h>

#define LED_PIN 13

S28BYJ48 motor(8,9,10,11);

void setup(){
  Serial.begin(115200);
  Serial.println("start");

  motor.setStepDuration(1);

  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  while (Serial.available() > 0) {
    int serialData = Serial.read();

    digitalWrite(LED_PIN, HIGH);
    Serial.println("rotate");
    motor.step(2352);
//  motor.step(-4352);
    digitalWrite(LED_PIN, LOW);
  }
}

