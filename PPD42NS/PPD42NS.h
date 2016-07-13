/**
 * Arduino Library for Dust Sensor(PPD42NS)
 * http://www.seeedstudio.com/wiki/Grove_-_Dust_Sensor
 **/
#ifndef PPD42NS_h
#define PPD42NS_h

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
#define PPD42NS_SAMPLING_MILLIS 2000

/**************************************************************************************
 * PPD42NS : ほこりセンサ
 **************************************************************************************/
class PPD42NS {
  public:
    PPD42NS();
    void init(uint8_t _sensorPin, uint8_t _ledPin);
    bool update(boolean debugDump = false);
    float getRatio();
    float getConcentration();

  private:
    uint8_t sensorPin;
    uint8_t ledPin;

    uint32_t lowPulseOccupancy;
    uint32_t sensorTimer;
    uint32_t lowMicros;

    boolean highLow = HIGH;
    float ratio;
    float concentration;
};

#endif

