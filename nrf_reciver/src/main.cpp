#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

struct SampleData {
  int joyX;
  int joyY;
  byte button;
};

Servo firstServo;
Servo secondServo;
SampleData data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(110);
  radio.startListening();
  pinMode(2, OUTPUT);
  firstServo.attach(3);
  secondServo.attach(4);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    firstServo.write(data.joyX);
    Serial.println(data.joyX);
    secondServo.write(data.joyY);
    if(data.button == LOW) {
      digitalWrite(2, HIGH);
    } else {
      digitalWrite(2, LOW);
    }
  }
  
}
