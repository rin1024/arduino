# PPD42NS

Arduino library for 28BYJ48 Stepper motor and ULN2003 driver
28BYJ48 : http://robocraft.ru/files/datasheet/28BYJ-48.pdf
ULN2003 : http://www.ti.com/lit/ds/symlink/uln2003a.pdf

## Description

ステッピングモーター(28BYJ48)とドライバ(ULN2003)を使う際のライブラリ。

ソースはほぼほぼ、下記のものを流用。
http://engyfun.blogspot.jp/2015/02/here-is-source-code-for-our-28byj48.html

***DEMO:***

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

## Usage

***Pin Assign:***

Reference:
http://3.bp.blogspot.com/-yzEWT6VnYBI/VNboFHx0X2I/AAAAAAAAAAg/BpW3LvCVUR4/s1600/Wiring.png

## Requirement

- Arduino IDE

## Author

[@rin1024](https://twitter.com/rin1024)

## License

[MIT](http://b4b4r07.mit-license.org)

