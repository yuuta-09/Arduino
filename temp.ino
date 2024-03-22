/*********************************************
  DHT11を用いて温度・湿度を計測し、シリアル通信で表示するプログラム

  接続方法
  - VCC: 5V
  - GND: GND
  - S:   D2
**********************************************/

#include <dht.h>

#define DHT11_PIN 2 // DHT11を接続するデジタルピン番号

dht DHT;

// 最初に1度だけ実行される関数
void setup()
{
  Serial.begin(9600);
}

/* setup実行後に繰り返し実行される関数 */
void loop()
{
  DHT.read11(DHT11_PIN);

  // 温度の表示
  Serial.print("temperature: ");
  Serial.println(DHT.temperature);

  // 湿度の表示
  Serial.print("Humidity: ");
  Serial.println(DHT.humidity);

  // 一回のループがどこまでかわかりやすくするために空の行を入れる
  Serial.println("");

  delay(1000); // 1秒遅らせる
}