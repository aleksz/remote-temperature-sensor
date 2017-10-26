#include <RH_ASK.h>
#include <SPI.h>
//#include "LowPower.h"

RH_ASK driver = RH_ASK(2000, 11, 9, 10, false);

int ThermistorPin = 0;
int ledPin = 13;      // select the pin for the LED

int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int intTemperature;
char address = 'A';

void setup() {
//  pinMode(ledPin, OUTPUT);     
  Serial.begin(9600); // Debugging only
  if (!driver.init())
     Serial.println("init failed");
} 

void loop() {
  
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); 
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
//  T = (byte) (T* 10);
  intTemperature = (int) (T * 100);

//    const char *msg = "Hello World!";
//    driver.send((uint8_t *)msg, strlen(msg));

  uint8_t data[] = {(uint8_t) address, (uint8_t) highByte(intTemperature), (uint8_t) lowByte(intTemperature)};
  driver.send(data, (uint8_t) 3);
  driver.waitPacketSent();

 // Serial.print(intTemperature);

//  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  delay(1000);
}


