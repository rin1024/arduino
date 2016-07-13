# DN7C3JA020

Arduino Library for PM2.5 Sensor(DN7C3JA020)
http://www.sharp.co.jp/products/device/lineup/selection/rf/pm25/index.html

## Description

ほこり or PM2.5を認識するセンサ

ソースは、GP2Y1010AUをベースに改良を加えた
http://aitendo3.sakura.ne.jp/aitendo_data/product_img/sensor/air/GP2Y1010/GP2Y1010A0F_arduino_demo.txt

センサのデータシートは下記
http://aitendo3.sakura.ne.jp/aitendo_data/product_img/sensor/air/GP2Y1010/gp2y1010au_j.pdf

***DEMO:***

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

## Requirement

- Arduino IDE

## Usage

***Pin Assign:***
- Pin 1(VCC) => 5V
- Pin 2(Vo) => A0
- Pin 3(S-GND) => GND
- Pin 4(LED) => D2
- Pin 5(LED-GND) => GND
- Pin 6(V-LED) => VCC - 150Ohm
                          |
                        Pin 6
                          |
                        220uF - GND

## Author

[@rin1024](https://twitter.com/rin1024)

## License

[MIT](http://b4b4r07.mit-license.org)

