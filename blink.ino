/*
    1つのLEDを消したり光らせたりするプログラム
*/

#define DIG_PIN 4       // LEDの陽極(足が長いほう)とつなぐデジタルピン番号
#define START_WORD 'S'  // 光らせる時に入力させる文字
#define END_WORD 'E'    // 消灯させるときに入力させる文字

// 最初に一度だけ実行される関数
void setup()
{
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(DIG_PIN, OUTPUT);
}

// 無限ループしている関数
void loop()
{
  char user_input = Serial.read();  // user入力を受け取る

  // ユーザの入力値によってLEDを制御する
  if (user_input == START_WORD)
  {
    digitalWrite(DIG_PIN, HIGH);
  }

  else if (user_input == END_WORD)
  {
    digitalWrite(DIG_PIN, LOW);
  }

  delay(1000); // 1秒遅らせる
}