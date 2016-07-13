# GP20U7

Arduino Library for GPS Module(GP-20U7)
https://www.sparkfun.com/products/13740

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
      if (gp.update() == true) {
        Serial.print("Latitude : ");
        Serial.print(gp.getLatitude());
        Serial.print("\tLongitude : ");
        Serial.println(gp.getLongitude());
      }
    }


## Requirement

- Arduino IDE
- SofwareSerial.h

## Author

[@rin1024](https://twitter.com/rin1024)

## License

[MIT](http://b4b4r07.mit-license.org)

