/**
 * 複数バイトの文字列受信用
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
#define PACKET_SIZE 144
#define PACKET_HEADER 0xFF
#define PACKET_FOOTER 0xFE

#define BUF_SIZE 512
#define BUF_HEAD 0
#define BUF_ID 1
#define BUF_PSIZE 2
#define BUF_RESERVED 3
#define BUF_OFFSET_PACKET 4

byte buf[BUF_SIZE];
int bufIndex;

void setup() {
  Serial.begin(9600);
  Serial.println("a_serial_14bit_receiver init");

  restoreBuf();
}

void loop () {
  if (Serial.available() > 0) {
    byte data = Serial.read();
    
    // footer(254)
    if (data == PACKET_FOOTER) {
      Serial.println("[recv]");
      
      // ヘッダが正しい場合処理開始
      if (buf[BUF_HEAD] == PACKET_HEADER) {
        int id = buf[BUF_ID];
        int packetSize = buf[BUF_PSIZE];

        Serial.print("id:");
        Serial.print(id);
        Serial.print(", packetSize:");
        Serial.println(packetSize);

        if (packetSize <= PACKET_SIZE) {
          for (int i = BUF_OFFSET_PACKET; i < BUF_OFFSET_PACKET + packetSize * 2; i += 2) {
            if (i + 1 >= bufIndex) {
              Serial.println("overflow");
              break;
            }

            // 2byte(というか14bit)のデータを復号化する
            int num = (buf[i] << 7) | buf[i + 1];
            Serial.print(num);
            Serial.print(",");
          }
        }

        Serial.println("");
      }
      
      restoreBuf();
    }
    else {
      // ヘッダは0xFF(255)固定
      if (data == PACKET_HEADER) {
        restoreBuf();
      }

      // データ層は7bitでマスクしているので、0x00 ~ 0x7Fの範囲内でくる
      if (bufIndex < BUF_SIZE) {
        buf[bufIndex++] = data;
      }
    }
  }
}

void restoreBuf() {
  for (int i = 0; i < bufIndex; i++) {
    buf[i] = '\0';
  }
  bufIndex = 0;
}


