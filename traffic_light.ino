/* マクロ(変数) */
#define digitGreen  5 // 緑色のLEDと接続するデジタルピン番号
#define digitYellow 6 // 黄色のLEDと接続するデジタルピン番号
#define digitRed    7 // 赤色のLEDと接続するデジタルピン番号

/* マクロ(関数) */
#define LEN(arr) (sizeof(arr) / sizeof(arr[0])) // 配列の要素数を計算する

const unsigned int digitColors[] = {digitGreen, digitYellow, digitRed}; // 全てのLEDのデジタルピン番号を格納する配列
unsigned int loopCnt; // ループ関数を実行した回数を格納する変数

/* 最初に実行される初期設定用の関数 */
void setup()
{
    Serial.begin(9600);
    loopCnt = 0;
}

/* 何度も繰り返し実行される関数 */
void loop()
{
    lightControl();

    loopCnt++;
    delay(1000);
}

/* loop回数に合わせてLEDを光らせる */
void lightControl()
{
    unsigned int blinkNum = digitColors[loopCnt % 3];

    lightReset();
    digitalWrite(blinkNum, HIGH);

    if (blinkNum != digitYellow)
    {
        delay(3000);
    }
}

/* 全てのLEDを消灯する */
void lightReset()
{

    for (int i = 0; i < LEN(digitColors); i++)
    {
        digitalWrite(digitColors[i], LOW);
    }
}