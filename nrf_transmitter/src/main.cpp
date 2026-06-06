#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

byte address[6] = "00001";

struct DataSample {
  int joyX;
  int joyY;
  byte button;
};

DataSample data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(110);
  radio.stopListening();
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  int valX = analogRead(A0);
  int valY = analogRead(A1);
  data.joyX = map(valX, 0, 1023, 0, 180);
  data.joyY = map(valY, 0, 1023, 0, 180);
  data.button = digitalRead(2);
  radio.write(&data, sizeof(data));
}