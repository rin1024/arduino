# GP20U7

Arduino Library for GPS-Module(GP20U7)

## Description

***DEMO:***

    #include <SoftwareSerial.h>
    #include <GP20U7.h>

    GP20U7 gp;
    SoftwareSerial gpsSerial(8, 9); // RX, TX

    void setup() {
      Serial.begin(115200);

      gpsSerial.begin(GP20U7::serialRate());
      gp.init(&gpsSerial);
    }

    void loop() {
      gp.update(true);
    }


## Requirement

- Arduino IDE
- SofwareSerial.h

## Author

[@rin1024](https://twitter.com/rin1024)

## License

[MIT](http://b4b4r07.mit-license.org)

