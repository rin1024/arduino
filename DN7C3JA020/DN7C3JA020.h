/**
 * Arduino Library for PM2.5 Sensor(DN7C3JA020)
 * http://www.sharp.co.jp/products/device/lineup/selection/rf/pm25/index.html
 *
 * Sample Source of GP2Y1010AU :
 * http://aitendo3.sakura.ne.jp/aitendo_data/product_img/sensor/air/GP2Y1010/GP2Y1010A0F_arduino_demo.txt
 **/
#ifndef DN7C3JA020_h
#define DN7C3JA020_h

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
#define DN7C3JA020_NUM_SAMPLINGS      50 // default: 100

#define DN7C3JA020_RISEUP_MICROS     280
#define DN7C3JA020_WAIT_MICROS        40
#define DN7C3JA020_PERIODIC_MICROS  9680

/**************************************************************************************
 * DN7C3JA020 : PM2.5センサ
 **************************************************************************************/
class DN7C3JA020 {
  public:
    DN7C3JA020();
    void init(uint8_t _sensorPin, uint8_t _ledPin);
    bool update(boolean debugDump = false);
    float getVoltage();
    float getDustDensity();
    float getPpmPerCf();

  private:
    uint8_t sensorPin;
    uint8_t ledPin;

    uint16_t samplingIndex;
    uint32_t sensorTimer;
    float ppm;

    float voltage;
    float dustDensity;
    float ppmPerCf;
};

#endif
