#include <Ethernet.h>

/**********************************
 * マクロの定義
 ***********************************/
#define HTTP_PORT_NUM 80     // HTTPのポート番号
#define SERIAL_PORT_NUM 9600 // Serial通信のポート番号

/***********************************
 * グローバル変数の定義
 ************************************/

// 製品に指定されたmacアドレスを設定
// 今回の値は製品にmacアドレスの指定がない場合にも使用可
byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// IPアドレスを固定する場合に使用
// ローカルネットワークのipアドレスの「.」区切りで上3つは同じ値を設定し、最後の部分だけ使用していない値を設定
IPAddress ip(192, 168, 0, 7);

EthernetServer server(HTTP_PORT_NUM); // HTTPのポート番号を指定

/***********************************
 * Arduinoの基本関数
 ************************************/
void setup()
{
  Serial.begin(SERIAL_PORT_NUM);
  Serial.println("waiting for DHCP IP...");

  Ethernet.begin(mac, ip);
  server.begin();

  checkEthernetHardWare();

  // 設定されたIPアドレスを表示する
  Serial.print("Please use your browser to visit http://");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  EthernetClient client = server.available(); // サーバに接続されて、読み取り可能なデータを持つクライアントを取得し、出来なかった場合はif分の中でfalseと評価される
  if (client)
  {
    Serial.println("new client");

    readServerInfo(&client);

    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}

/*******************************
 * 自作関数
 ********************************/

/*
  Ethernetが正しく使用できるかを確認するメソッド

  ・ハードウェアが正しく認識されているか
  ・使用可能なケーブルが接続されているか
*/
void checkEthernetHardWare()
{
  // ハードウェアの確認
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    while (true)
    {
      Serial.println("Ethernet機器の存在が確認できません。");
      Serial.println("正しく接続されているかを確認してください。");
    }
  }

  // ケーブルの確認
  if (Ethernet.linkStatus() == LinkOFF)
  {
    Serial.println("Ethernetケーブルが正しく接続されていません。");
  }
}

/*
  サーバの情報を作成する

  ・httpリクエストの際に必要な情報を作成
  ・ページ内の表示するデータを作成
*/
void createServerInfo(const EthernetClient *client)
{
  client->println("HTTP/1.1 200 OK");
  client->println("Content-Type: text/html");
  client->println("Connection: close");
  client->println("Refresh: 5");
  client->println();
  client->println("<!DOCTYPE HTML>");
  client->println(
      "<html><body><h4>Osoyoo Ethernet IoT Lesson 1 </h4><font color=red size=5>Hello World!</font></html>");
}

/*
  クライアントと接続が確立されていて、
  利用可能な場合はクライアントが接続しているサーバから受信したデータを1文字読み込む
*/
void readServerInfo(const EthernetClient *client)
{
  boolean currentLineIsBlank = true; // 読み込んだデータの行が空かどうかを示す

  while (client->connected())
  {
    if (client->available())
    {
      char c = client->read(); // クライアントが接続しているサーバーから受信したデータを1文字読み込み
      if (c == '\n' && currentLineIsBlank)
      {
        createServerInfo(client);
        break;
      }
      if (c == '\n')
      {
        currentLineIsBlank = true;
      }
      else if (c != '\r')
      {
        currentLineIsBlank = false;
      }
    }
  }
}