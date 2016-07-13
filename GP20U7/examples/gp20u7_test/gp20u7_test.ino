// GPS Module (GP-20U7) - Arduino Example Source Code
//
// References:
// https://cdn.sparkfun.com/datasheets/GPS/GP-20U7.pdf
// https://www.arduino.cc/en/Reference/SoftwareSerial
// http://forum.arduino.cc/index.php?topic=288234.0
//
#include <SoftwareSerial.h>
#include "GP20U7.h"

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

