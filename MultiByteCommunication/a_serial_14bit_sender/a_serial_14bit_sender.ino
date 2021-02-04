/**
 * 複数バイトの文字列送信用
 *
 * 識別用にヘッダとフッタは8bitのデータにしておき、
 * データ層は2byteのデータを7bit x 2回に分割しておくってる。
 *
 * 通常2byteのデータは16bit(0 ~ 65535)つかえるけど、
 * 今回は上位2bitをすてて14bitにまるめてるので、データの値の範囲は0 ~ 16383になる。
 *
 * パケットのフォーマット
 * [0] 0xFF ヘッダ(255)
 * [1] 0x** 送信元のID(0 ~ 253)
 * [2] 0x** パケットサイズ(0 ~ 253)
 * [3] 0x** ダミー
 * [4 ~ PACKET_SIZE * 2] データ層(0 ~ 16383) x PACKET_SIZE * 2
 * [*] 0xFE フッタ(254)
 */
#define PACKET_HEADER 0xFF
#define PACKET_FOOTER 0xFE

#define MY_ID 9
#define PACKET_SIZE 144
#define SEND_INTERVAL 2000

unsigned long sendTimer;

void setup() {
  Serial.begin(9600);
  Serial.println("a_serial_14bit_sender init");
}

void loop() {
  if (millis() - sendTimer > SEND_INTERVAL) {
    int id = MY_ID;
    int packetSize = PACKET_SIZE;
    int packet[packetSize];
    for (int i = 0; i < packetSize; i++) {
      packet[i] = i * 10;//(int)random(0, 16383);
    }
    sendSignal(id, packetSize, packet);
    sendTimer = millis();
  }
}

void sendSignal(int id, int packetSize, int packet[]) {
  Serial.write(PACKET_HEADER);
  Serial.write(id);
  Serial.write(packetSize);
  Serial.write(0x00);
  for (int i = 0; i < packetSize; i++) {
    int v = packet[i];
    Serial.write(v >> 7);  // hight
    Serial.write(v & 127); // low
  }
  Serial.write(PACKET_FOOTER);
}

