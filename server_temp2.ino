#include <Ethernet.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

/*******************************************
  Webサーバで気温・海面気圧・高度・気圧を計測可能
  センサはAdafruit_BMP085を使用
********************************************/

/***************************
 * グローバル変数の定義
 ****************************/
Adafruit_BMP085 bmp;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xED}; // macアドレス
IPAddress ip(169, 254, 240, 158);
EthernetServer server(80); // HTTP通信のポート番号80を指定
EthernetClient client;

void setup()
{
  Serial.begin(9600);
  Serial.println("connect DHCP server");
  // Ethernet通信開始
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Please use your browser to visit http://");
  Serial.println(Ethernet.localIP());
  if (!bmp.begin())
  {
    Serial.println(F("有効な BMP 180 センサが見つかりません、 接続を確認してください!"));

    while (1)
    {
      ; // 何もしない
    }
  }
}

void loop()
{
  client = server.available();
  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        String msg = "HTTP/1.1 200 OK\n\rContent-Type: text/html\n\r\n\r";
        msg += "<HTML><meta http-equiv=\"refresh\" content=\"5\" charset=\"utf-8\"><BODY><H1 style=\"color:green;\">Arduino IoT Lesson 5</H1><br>";
        msg += "<p>気圧：";
        msg += bmp.readPressure();
        msg += "pa<br>気温: ";
        msg += bmp.readTemperature();
        msg += "<br>海面気圧: ";
        msg += bmp.readSealevelPressure();
        msg += "pa<br>高度: ";
        msg += bmp.readAltitude();
        msg += "m</p></BODY></HTML>";
        client.println(msg);
        delay(10);
        // サーバとの通信を終了
        client.stop();
      }
    }
  }
}
