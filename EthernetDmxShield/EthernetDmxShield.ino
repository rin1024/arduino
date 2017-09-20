/**
 * ENC28J60 + DMX ShieldでledSimulatorを動かすサンプル
 * だけど遅延が起きたり不安定でした
 */
#include <Conceptinetics.h>
#include <EtherCard.h>
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
/*#define STATIC 0  // set to 1 to disable DHCP (adjust myip/gwip values below)
#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,10,200 };
// gateway ip address
static byte gwip[] = { 192,168,10,1 };
#endif*/
#define NUM_PACKET_BUFFER 568

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[NUM_PACKET_BUFFER]; // tcp/ip send and receive buffer

// ================================================
void setup(){
  //Serial.begin(9600);
  //Serial.println(F("\n[backSoon]"));

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
    //Serial.println(F("Failed to access Ethernet controller"));
  }
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup()) {
    //Serial.println(F("DHCP failed"));
  }
#endif

  //ether.printIp("IP:  ", ether.myip);
  //ether.printIp("GW:  ", ether.gwip);
  //ether.printIp("DNS: ", ether.dnsip);

  //register udpSerialPrint() to port 1337
  ether.udpServerListenOnPort(&udpSerialPrint, 1337);

  //register udpSerialPrint() to port 42.
  ether.udpServerListenOnPort(&udpSerialPrint, 42);

  // Enable DMX master interface and start transmitting
  dmx_master.enable();  
  
  // Set channel
  dmx_master.setChannelRange(START_CHANNEL, NUM_CHANNELS, 256);
  for (int i=START_CHANNEL;i<NUM_CHANNELS;i++) {
    dmx_master.setChannelValue(i, 0);
  }
}

void loop(){
  //this must be called for ethercard functions to work.
  ether.packetLoop(ether.packetReceive());
}

// ================================================
// Ethernet function
// callback that prints received packets to the serial port
// ================================================
void udpSerialPrint(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t dataLen){
  IPAddress src(src_ip[0],src_ip[1],src_ip[2],src_ip[3]);
  
  /*Serial.print(F("src_ip: "));
  ether.printIp(src_ip);
  Serial.print(F("\tsrc_port: "));
  Serial.print(src_port);
  Serial.print(F("\tdest_port: "));
  Serial.println(dest_port);
  
  Serial.print(F("dataLen: "));
  Serial.println(dataLen);
  Serial.println(F("data: "));
  Serial.println(data);*/

  int OFFSET = 16;
  if (dataLen > OFFSET) {
    for (int i=OFFSET;i<dataLen;i++) {
      if (i - OFFSET + START_CHANNEL < NUM_CHANNELS && (data[i] > 0 && data[i] < 256)) {
        dmx_master.setChannelValue(i - OFFSET + START_CHANNEL, data[i]);
      }
    }
  }
}

