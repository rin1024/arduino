#ifndef GP20U7_h
#define GP20U7_h

/*******************************************
 * include
 *******************************************/
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*******************************************
 * const
 *******************************************/
#define GPS_NUM_POS  8
#define GPS_NUM_VAL 15

/**************************************************************************************
 * GP20U7 : GPSモジュール
 **************************************************************************************/
class GP20U7 {
  public:
    GP20U7();
    void init(Stream *_serial);
    bool update(boolean debugDump = false);
    float getLatitude();
    float getLongitude();
    static long serialRate(){ return 9600; }

  private:
    Stream *gpsSerial;
    char gpsVals[GPS_NUM_POS][GPS_NUM_VAL];
    uint16_t gpsPosIndex;
    uint16_t gpsValIndex;
    bool isLatLon;
    float latitude;
    float longitude;
};

#endif



