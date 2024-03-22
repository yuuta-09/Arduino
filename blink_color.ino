/*
    ledを制御するプログラム
    ユーザが入力した値に応じた色のLEDを光らせる
*/

#define DIG_R 4 // 赤色のLEDに接続するデジタルピン番号
#define DIG_G 5 // 緑色のLEDに接続するデジタルピン番号
#define DIG_Y 6 // 黄色のLEDに接続するデジタルピン番号
#define DIG_W 7 // 白色のLEDに接続するデジタルピン番号

#define RED_CHAR 'R'    // 赤色を光らせるときに使う文字
#define GREEN_CHAR 'G'  // 緑色を光らせるときに使う文字
#define YELLOW_CHAR 'Y' // 黄色を光らせるときに使う文字
#define WHITE_CHAR 'W'  // 白色を光らせるときに使う文字
#define CLEAR_CHAR 'C'  // 全てのLEDを消灯させるときに使う文字

/* 最初に一度だけ実行される関数 */
void setup()
{
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(DIG_R, OUTPUT);
  pinMode(DIG_G, OUTPUT);
  pinMode(DIG_Y, OUTPUT);
  pinMode(DIG_W, OUTPUT);
}

/* setup関数が実行された後に無限にループする関数 */
void loop()
{
  char user_input = Serial.read(); // シリアル通信でユーザからの入力を取得する

  led_control(user_input); // ユーザから入力された文字によってledを光らせたり消したりする

  delay(1000); // wait for a second
}

/***************************
  LEDを制御するメソッド群
****************************/

/* LEDのすべてを消灯させる関数 */
void reset_led()
{
  digitalWrite(DIG_R, LOW);
  digitalWrite(DIG_G, LOW);
  digitalWrite(DIG_Y, LOW);
  digitalWrite(DIG_W, LOW);
}

/* ユーザの入力値によってledを光らせたり消したりする関数 */
void led_control(char user_input)
{
  switch (user_input)
  {
  case RED_CHAR:
    // 赤のLEDを反転する
    digitalWrite(DIG_R, !(digitalRead(DIG_R)));
    break;

  case GREEN_CHAR:
    // 緑のLEDの光を反転する
    digitalWrite(DIG_G, !(digitalRead(DIG_G)));
    break;

  case YELLOW_CHAR:
    // 黄色のLEDの光を反転する
    digitalWrite(DIG_Y, !(digitalRead(DIG_Y)));
    break;

  case WHITE_CHAR:
    // 白のLEDの光を反転する
    digitalWrite(DIG_W, !(digitalRead(DIG_W)));
    break;

  case CLEAR_CHAR:
    // 全てのLEDの光を消す
    reset_led();
    break;
  }
}