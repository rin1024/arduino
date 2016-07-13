#include "GP20U7.h"

//////////////////////////////////////////////////////////////////////////////////////////
// GPSデータのフォーマット
//
// [Message ID][Latitude][N/S Indicator][Longitude][E/W Indicator][UTC Position][Status][Checksum][<CR>][<LF>]
// $GPGLL,          X, X,           X, X,  140558.00, V, N*47  ... 起動時
// $GPGLL, 3335.77140, N, 13022.10799, E,  125736.00, A, A*6A  ... 安定してくると出てくる
// $GPGLL, 3723.24756, N, 12158.34162, W, 161229.487, A, *2C   ... 理想
//////////////////////////////////////////////////////////////////////////////////////////

/**
 * コンストラクタ
 */
GP20U7::GP20U7() {

}

/**
 * 初期化
 */
void GP20U7::init(Stream *_serial) {
  gpsSerial = _serial;
}

/**
 * アップデート関数
 */
bool GP20U7::update(boolean debugDump) {
  bool updated = false;
  while (gpsSerial->available() > 0) {
    int serialData = gpsSerial->read();

    // begin
    if(serialData == '$') {
      for(int i=0;i<GPS_NUM_POS;i++) {
        for(int j=0;j<GPS_NUM_VAL;j++) {
          gpsVals[i][j] = '\0';
        }
      }
      gpsPosIndex = 0;
      gpsValIndex = 0;
    }
    else if(serialData == ',') {
      // Message IDがvalidか
      if (gpsPosIndex == 0) {
        int correctCount = 0;
        int checkPattern[5] = { 'G', 'P', 'G', 'L', 'L' };
        for(int i=0;i<5;i++) {
          if (checkPattern[i] == gpsVals[0][i]) {
            correctCount++;
          }
        }

        if (correctCount == 5) {
          isLatLon = true;
        }
        else {
          isLatLon = false;
        }
      }

      if (isLatLon == true && gpsPosIndex < GPS_NUM_POS) {
        gpsPosIndex++;
        gpsValIndex = 0;
      }
    }
    else if(serialData == '\r') {
    }
    else if(serialData == '\n') {
      if (isLatLon == true) {
        // strodについて : http://www9.plala.or.jp/sgwr-t/lib/strtod.html
        char*endptr;

        // 緯度・経度のみ取る
        latitude  = strtod(gpsVals[1], &endptr);
        longitude = strtod(gpsVals[3], &endptr);

        if (debugDump == true) {
          for(int i=0;i<GPS_NUM_POS;i++) {
            Serial.print("[");
            Serial.print(i);
            Serial.print("]");
            for(int j=0;j<GPS_NUM_VAL;j++) {
              if (gpsVals[i][j] != '\0') {
                Serial.print((char)gpsVals[i][j]);
              }
            }
            Serial.print(" ");
          }
          Serial.println();
        }

        for(int i=0;i<GPS_NUM_POS;i++) {
          for(int j=0;j<GPS_NUM_VAL;j++) {
            gpsVals[i][j] = '\0';
          }
        }

        updated = true;
      }
    }
    else {
      if ((isLatLon == true || gpsPosIndex == 0) && gpsValIndex < GPS_NUM_VAL) {
        gpsVals[gpsPosIndex][gpsValIndex++] = serialData;
      }
    }
  }

  return updated;
}

/**
 *
 */
float GP20U7::getLatitude() {
  return latitude;
}

/**
 *
 */
float GP20U7::getLongitude() {
  return longitude;
}


