/***************************************************************************
  環境温度を計測するプログラム

  環境温度とは？
  - https://kotobank.jp/word/%E7%92%B0%E5%A2%83%E6%B8%A9%E5%BA%A6-1294978

  接続方法
  - -:      GND
  - Middle: 5V
  - S:      D2
******************************************************************************/

#include <OneWire.h>
#include <DallasTemperature.h>

/* マクロ(変数) */
#define OneWireBus 2 // デジタルピン番号

OneWire oneWire(OneWireBus);
DallasTemperature sensors(&oneWire);

/* 最初に1度だけ実行される関数 */
void setup()
{
  Serial.begin(9600);
  sensors.begin();
}

/* setup実行後に繰り返し実行される関数 */
void loop()
{
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("Done");

  displayTemperature(0);

  Serial.println(); // 1回のループをわかりやすくするために空の行を表示

  delay(1000); // 1秒遅らせる
}

/********************************
  関数群
********************************/

/* 読み取りが成功した場合温度を表示する */
void displayTemperature(int index)
{
  float tempC = sensors.getTempCByIndex(index);

  // 読み取りに成功しているかをチェック
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the devise 1 (index 0) is: ");
    Serial.println(tempC);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
}
