#include <Arduino.h>
#include <SPI.h>

#define MAX6675_CS 5 

void setup() {
  Serial.begin(9600);
  SPI.begin();              
  pinMode(MAX6675_CS, OUTPUT);
  digitalWrite(MAX6675_CS, HIGH);

  Serial.println("MAX6675 test...");
}

double readMAX6675() {
  uint16_t value = 0;
  digitalWrite(MAX6675_CS, LOW);
  delayMicroseconds(10);
  value = SPI.transfer16(0x0000);
  digitalWrite(MAX6675_CS, HIGH);
  if (value & 0x0004) {
    return NAN;  
  }
  value >>= 3;
  double tempC = value * 0.25;
  return tempC;
}

void loop() {
  double temp = readMAX6675();
  if (isnan(temp)) {
    Serial.println("Loi: Khong doc duoc cam bien Type-K!");
  } else {
    Serial.print("Nhiet do: ");
    Serial.print(temp);
    Serial.println(" *C");
  }
  delay(1000);
}
