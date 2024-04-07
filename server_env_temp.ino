/*
  DS18B20 環境気温センサのデータをWebサーバで表示するプログラム

  接続方法
  - -:      GND
  - Middle: 5V
  - S:      D2
*/

#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/**************
  マクロの定義
***************/
#define DEBUG_MODE 0         // 0: デバッグを行わない  0以外: デバッグを行う

#define ONE_WIRE_BUS 2       // センサのS部分に接続するデジタルピン番号
#define SERVER_PORT_NUM 80   // HTTP通信をするときのポート番号
#define SERIAL_PORT_NUM 9600 // シリアル通信を行うときのポート番号

/**************
  変数等の定義
***************/
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xFE, 0xED }; // macアドレス
IPAddress ip(169, 254, 240, 158);              // 静的なIPアドレスを指定
EthernetServer server(SERVER_PORT_NUM); // サーバのポート番号を指定

EthernetClient client;

/*********************
  Arduinoの基本関数
**********************/
void setup()
{
  Serial.begin(SERIAL_PORT_NUM);
  sensor.begin();
  Serial.println("connect DHCP server");

  // Ethernet通信の開始
  Ethernet.begin(mac, ip); // macアドレスとIPアドレスを指定
  server.begin();
  Serial.print("Please use your browser to visit http://");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  // 通信を行うクライアントの作成(失敗したらfalseとして評価される)
  client = server.available();
// 使用可能なクライアントが存在するなら
  if (client)
  {
    // クライアントが接続をしている間
    while (client.connected())
    {
      // DEBUGモードになっている場合は送信されたデータをSerial通信で表示する
      if (DEBUG_MODE)
      {
        debug();
      }

      createResultPage();

      client.stop();
    }
  }
}

/***********************
  自作関数
************************/
void createResultPage()
{
  sensor.requestTemperatures(); // 気温を取得する

  String msg = "";
  msg += "HTTP/1.1 200 OK\n\rContent-Type: text/html\n\r\n";
  msg += "<!DOCTYPE><HTML><meta http-equiv=\"refresh\" content=\"5\"><BODY><H1 style=\"color: green;\">Arduino IoT Lesson 6</H1><br>";
  msg += "Temperature: ";
  msg += sensor.getTempCByIndex(0); // 1つめのdevise(index 0)に関する気温を指定

  client.println(msg);
  delay(10);
}

void debug()
{
  String readString;

  
  // 読み込み可能なデータがあるならクライアントが接続されたサーバから送信されたデータを読み込み
  if (client.available())
  {
    char c = client.read();

    while (readString.length() < 100 && c != 0x0D )
    {
      readString += c;
      c = client.read();
    }
  }

  Serial.println(readString);
}