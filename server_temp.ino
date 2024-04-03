/*
  Webサーバで現在の温度と湿度を確認することができるプログラム
*/

#include <SPI.h>
#include <Ethernet.h>
#include <dht.h>

/***********************
 * マクロの定義
************************/
#define DHT11_PIN 2

/***********************
 * グローバル変数の定義
************************/
dht DHT;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(169, 254, 240, 158);
EthernetServer server(80); // server port
EthernetClient client;

/***********************
 * Arduinoの基本関数
************************/
void setup()
{
  Serial.begin(9600);
  Serial.println("connect DHCP server");
  // Ethernet通信開始
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Please use your browser to visit http://");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  // Create a client connection
  client = server.available();
  if (client)
  {
    createResultPage();
  }
}


void createResultPage()
{
  while (client.connected())
  {
    if (client.available())
    {
      int chk = DHT.read11(DHT11_PIN);
      String msg = "HTTP/1.1 200 OK\n\rContent-Type: text/html\n\r\n\r";
      msg += "<!DOCTYPE><HTML lang=\"ja\"><meta http-equiv=\"refresh\" content=\"5\" charset=\"utf-8\"><BODY><H1 style=\"color:green;\">Arduino IoT Lesson 4</H1><br>";
      msg += "<p>現在の温度: ";
      msg += DHT.temperature;
      msg += " C;<br>現在の湿度: ";
      msg += DHT.humidity;
      msg += "%</p></BODY></HTML>";
      client.println(msg);
      delay(10);
      // サーバとの接続を削除
      client.stop();
    }
  }
}