/***********************************************************
  光センサを用いて周囲の暗さに合わせてLEDを光らせるプログラム

  ・少し暗い場合は赤色
  ・暗い場合は白色

  接続方法
  - A0:  Analog In A0
  - VCC: 5V
  - GND: GND
************************************************************/

/* マクロ(変数) */
#define analogInPin A0 // センサの値を受け取るアナログピン番号
#define digitWhite 6   // 白のLEDのデジタルピン番号
#define digitRed 7     // 赤のLEDのデジタルピン番号

/* 最初に1度だけ実行される関数 */
void setup()
{
  Serial.begin(9600); // 9600はシリアル通信のポート番号
}

/* 繰り返し実行される関数 */
void loop()
{
  unsigned int sensorValue = analogRead(analogInPin); // センサーから入力された値を取得

  displaySensorPercent(sensorValue);
  blinkLedBySensor(sensorValue);

  delay(1000); // 1秒遅らせる
}

/* センサーから受け取った値をパーセンテージに変換して表示 */
void displaySensorPercent(int sensorValue)
{
  int percentValue = 100 - map(sensorValue, 0, 1023, 0, 100);
  Serial.println(percentValue);
}

/*
    センサーからの値によってLEDを光らせる
    明るい   -> 全てのLEDが消灯
    少し暗い -> 赤のLEDのみが点灯
    暗い     -> 白のLEDのみが点灯
*/
void blinkLedBySensor(int sensorValue)
{
  if (sensorValue > 500)
  {
    // 暗い場合
    digitalWrite(digitRed, LOW);
    digitalWrite(digitWhite, HIGH);
  }
  else if (sensorValue > 400)
  {
    // 少し暗い場合
    digitalWrite(digitRed, HIGH);
    digitalWrite(digitWhite, LOW);
  }
  else
  {
    // 明るい場合
    digitalWrite(digitRed, LOW);
    digitalWrite(digitWhite, LOW);
  }
}