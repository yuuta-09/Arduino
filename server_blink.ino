/*
  webサーバでLEDの点灯・消灯を制御するプログラム
*/
#include <Ethernet.h>

/*************************
 * マクロの定義
**************************/
#define SERVER_PORT_NUM 80   // http通信に使うポート番号
#define SERIAL_PORT_NUM 9600 // シリアル通信に使用するポート番号
#define LED_PIN_NUM 4        // LEDを接続するデジタルポート番号

/***************************
 * グローバル変数の定義
****************************/
// macアドレス
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 109);
EthernetServer server(SERVER_PORT_NUM); // server port
EthernetClient client;
String readString;

/***************************
 * Arduinoの基本関数
****************************/
void setup()
{
  Serial.begin(SERIAL_PORT_NUM);

  pinMode(LED_PIN_NUM, OUTPUT); // 制御するピン番号の選択

  // start Ethernet
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Please use your browser to visit http://");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  // サーバに接続されて、読み取り可能なデータのあるクライアントを作成。失敗した場合はfalseと評価される
  client = server.available();
  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        readHttpRequest();

        Serial.println(readString);

        createControlLedPage();


        delay(10);
        client.stop(); // サーバとの接続を終了する

        controlLed();
      }
    }
  }
}

/************************
 * 自作関数
*************************/

/*
  HTTPリクエストから情報を読み取る
*/
void readHttpRequest()
{
  char c = client.read();

  while(readString.length() < 100 && c != 0x0D)
  {
    // 文字を文字列型の変数に保存する
    readString += c;
    c = client.read();
  }
}

/*
  LEDを制御するWebページを作成する
*/
void createControlLedPage()
{
  String msg = "HTTP/1.1 200 OK\n\rContent-Type: text/html\n\r\n\r";
  msg += "<HTML><BODY><H1 style=\"color:green;\">Test W5100 ETHERNET SHIELD</H1><br>";
  msg += "<H2><a href=\"/?LEDON\"\">Turn On LED</a><br></H2>";

  msg += "<H2><a href=\"/?LEDOFF\"\">Turn Off LED</a><br></H2></BODY></HTML>";

  client.println(msg);
}

/*
  選択されたボタンによってLEDを制御するプログラム
*/
void controlLed()
{
  if (readString.indexOf("?LEDON") > -1) // LEDONという文字があるかを確認する。
  {
    digitalWrite(LED_PIN_NUM, HIGH); // 光らせる
  }
  else
  {
    if (readString.indexOf("?LEDOFF") > -1) // LEDOFFという文字があるかを確認する
    {
      digitalWrite(LED_PIN_NUM, LOW); // 光を消す
    }
  }

  readString = ""; // 次回のために読み込んだデータをリセットする
}
