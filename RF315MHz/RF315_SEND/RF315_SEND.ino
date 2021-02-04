/**
 * 315MHzのモジュール簡易送信プログラム
 * VDDに3.3V常時接続ではなく、SEND_EN_PINとVDDつないで通常時はlowにして省電力にするバージョン
 */
#include <VirtualWire.h>

#define MY_ID 12
#define SEND_PIN 12 // DATA <-> D12
#define SEND_EN_PIN 3 // VDD <-> D3

#define PACKET_ID 0
#define PACKET_TYPE 1
#define PACKET_DATA 2

#define SEND_INTERVAL 2500

unsigned long sendTimer;

void setup() {
  //Serial.begin(9600);
  //Serial.println("RF315_SEND init");
  
  pinMode(SEND_EN_PIN, OUTPUT);
  digitalWrite(SEND_EN_PIN, LOW);

  vw_set_tx_pin(SEND_PIN);
  //vw_set_rx_pin(receive_pin);
  //vw_set_ptt_pin(transmit_en_pin);
  //vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000); // Bits per sec
}
 
void loop() {
  if (millis() - sendTimer > SEND_INTERVAL) {
    //Serial.println("send");
    
    digitalWrite(SEND_EN_PIN, HIGH);
    delay(50); // wait for wakeup

    for (int j=0;j<2;j++) {
      int numCount = 25; // 25くらいがmax、30とかにすると落ちる
      char counts[numCount];
      counts[PACKET_ID] = MY_ID;
      counts[PACKET_TYPE] = j * 10;
      for (int i=PACKET_DATA;i<numCount;i++) {
        counts[i] = i;
      }
      vw_send((uint8_t *)counts, numCount);
      vw_wait_tx(); // Wait until the whole message is gone
    }
  
    digitalWrite(SEND_EN_PIN, LOW);

    sendTimer = millis();
  }
}

