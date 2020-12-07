#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

#define Trig 8
#define Echo 9
#define ledPin 13

void setup()
{
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//  display.clearDisplay();
}
unsigned int impulseTime = 0;
unsigned int distance_sm = 0;
bool start = false;
float timer = 0;
float time1 = micros();

void loop()
{
  if (start)
  {
    timer += (micros() - time1) * 0.1;
  } 
    time1 = micros();
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    impulseTime = pulseIn(Echo, HIGH);
    distance_sm = impulseTime / 58;
    Serial.println(timer / 100000);
  if (distance_sm < 20)
  {
      if (start && timer / 100000 > 3)
      {
          Serial.println(-1);
          delay(5000);
      }
      if(start && timer / 100000 < 3)
      {
          goto x;
      }
      start = !start;
      timer = 0;
      PORTB |= _BV(PB5);
    }
    else
    {
      PORTB &= ~_BV(PB5);
    } 
x:
    delay(100);
}
