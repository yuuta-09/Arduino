#include <Adafruit_BMP085.h>

/*********************************************
  Adafruit_BMP085を使用したセンサ
  以下のものを計測可能
  - 気圧
  - 温度
  - 海面気圧
  - 高度

  接続方法
  - VCC: 3.3V
  - GND: GND
  - SCL: Analog5
  - SDA: Analog4
***********************************************/

Adafruit_BMP085 bmp;

void setup()
{
  Serial.begin(9600);
  if (!bmp.begin())
  {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1)
    {
    }
  }
}

void loop()
{
  displayTemp();
  displayPres();
  displayAltitude();
  displaySealevelPressure();

  Serial.println("");
  delay(1000);
}

/**************************************
    関数群
**************************************/
/* 気温を表示 */
void displayTemp()
{
  Serial.print("Temprature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
}

/* 気圧 */
void displayPres()
{
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
}

/* 高度を表示 */
void displayAltitude()
{
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");
}

/* 海面気圧を表示 */
void displaySealevelPressure()
{
  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");
}