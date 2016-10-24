#include <Morse.h>
#include <SoftwareSerial.h>


// Use pin 13 (built-in LED of Arduino 2009)
Morse morse(13, 12, 1);
SoftwareSerial btSerial(10, 11); // RX, TX

void setup()
{
  Serial.begin(9600);
  btSerial.begin(9600);
  btSerial.println("Hello, world?");
}

void loop()
{
  if (btSerial.available()) {
    char str = btSerial.read();
    Serial.print(str);
    morse.send(str);
  }
}

