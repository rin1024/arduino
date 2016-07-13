# PPD42NS

Arduino Library for Dust Sensor(PPD42NS)
https://www.seeedstudio.com/item_detail.html?p_id=1050

## Description

ほこり検知センサのArduino用ライブラリ。
(一部の通販サイトの型番では、SEN12291Pと表記されている。)

公式のソースがpulseInを使用しており( http://www.seeedstudio.com/wiki/Grove_-_Dust_Sensor )、
使い勝手が悪かったので書き直した。

ちなみに、このセンサ実は出力ピンが2個あって二種類の粒度のホコリを取れるかもしれない(未着手)。

***DEMO:***

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

## Usage

***Pin Assign:***
- Pin 1 (Black)  => GND
- Pin 2 (Red)    => 5V
- Pin 3 (Yellow) => A0

## Requirement

- Arduino IDE

## Author

[@rin1024](https://twitter.com/rin1024)

## License

[MIT](http://b4b4r07.mit-license.org)

