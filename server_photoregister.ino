/*
  Webサーバを使用して光の値を監視するプログラム
*/
#include <Ethernet.h>

/**************************
 * マクロの定義
 ***************************/
#define SERVER_PORT_NUM 80   // http通信に使用するポート番号
#define SERIAL_PORT_NUM 9600 // シリアル通信に使用するポート番号
#define ANALOG_PIN_NUM A0    // フォトレジスタと接続するアナログピン番号

/**************************
 * グローバル変数の定義
 ***************************/
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // macアドレス
IPAddress ip(169, 254, 240, 158);
EthernetServer server(SERVER_PORT_NUM); // server port
EthernetClient client;

void setup()
{
  Serial.begin(SERIAL_PORT_NUM);
  Serial.println("connect DHCP server");
  // Etheret通信の開始
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Please use your browser to visit http://");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  // サーバに接続されていて読み取り可能なデータを持つクライアントを作成。失敗したらfalseと評価される
  client = server.available();
  if (client)
  {
    // フォトレジスタの値を読み込む
    int sensorValue = analogRead(ANALOG_PIN_NUM);
    // 読み込んだ値をパーセンテージへ変換
    int percentValue = 100 - map(sensorValue, 0, 1023, 0, 100);
    createResultPage(sensorValue, percentValue);
  }
}

/*******************************
 * 自作関数
 ********************************/
void createResultPage(const int sensorValue, const int percentValue)
{
  while (client.connected())
  {
    if (client.available())
    {
      char c = client.read();

      String msg = "HTTP/1.1 200 OK\n\rContent-Type: text/html\n\r\n\r";
      // metaデータの http-equiv=refreshはcontentに指定した秒数毎にページをリロードする
      // metaデータのcharsetは文字コードを指定する
      msg += "<HTML><head><meta http-equiv=\"refresh\" content=\"5\" charset=\"utf-8\"></head><BODY><H1 style=\"color:green;\">Arduino IoT Lesson 3</H1><br>";
      msg += "<p>現在のフォトレジスタの値: ";
      msg += sensorValue;
      msg += ", <br>パーセンテージ：";
      msg += percentValue;
      msg += "%</p></BODY></HTML>";
      client.println(msg);
      delay(10);
      // サーバとの通信を終了
      client.stop();
    }
  }
}
