/**
 * イーサネットシールド + DMXシールド / ledSimulatorの連携テスト
 * 
 * ただ動きが鈍いというか、信号はいってるんだけど欠落が多い
 */
#include <Conceptinetics.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <IPAddress.h>

// ================================================
// DMX settings
// ================================================
#define RXEN_PIN                 2
#define START_CHANNEL            1
#define NUM_CHANNELS           512

static DMX_Master dmx_master(NUM_CHANNELS, RXEN_PIN);

// ================================================
// Ethernet settings
// ================================================
static byte myip[] = { 169,254,52,101 };
static int myport = 2430;

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };

EthernetUDP Udp;

// ================================================
void setup(){
  Ethernet.begin(mymac, myip);
  Serial.print("Arduino IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println("");

  Udp.begin(myport);

  dmx_master.enable();  
  dmx_master.setChannelRange(START_CHANNEL, NUM_CHANNELS, 256);
  for (int i=START_CHANNEL;i<NUM_CHANNELS;i++) {
    dmx_master.setChannelValue(i, 10);
  }
  delay(1000);
  for (int i=START_CHANNEL;i<NUM_CHANNELS;i++) {
    dmx_master.setChannelValue(i, 0);
  }
}

void loop(){
  int size;
  if ((size = Udp.parsePacket()) > 0) {
    int OFFSET = 16;
    int cnt = 0;
    int data[size];
    while(size--) {
      data[cnt++] = Udp.read();
      if (cnt >= size) {
        break;
      }
    }

    if (size > OFFSET) {
      for (int i=OFFSET;i<size;i++) {
        if (i - OFFSET + START_CHANNEL < NUM_CHANNELS && (data[i] > 0 && data[i] < 256)) {
          dmx_master.setChannelValue(i - OFFSET + START_CHANNEL, data[i]);
        }
      }
    }
  }
}


