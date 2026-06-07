#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

struct SampleData {
  int joyX;
  int joyY;
  byte button;
};

SampleData data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(54);
  radio.startListening();

  // L298N pwm pins
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

  // L298N digital pins
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    int valFront = map(data.joyX, 530, 1022, 0, 255);
    int valBack = map(data.joyX, 0, 528, 255, 0);

    int valLeft = map(data.joyY, 0, 515, 255, 0);
    int valRight = map(data.joyY, 515, 1022, 0, 255);
    if(valFront > 0) {
      analogWrite(3, valFront);
      analogWrite(5, valFront);
      digitalWrite(2, HIGH);
      digitalWrite(6, HIGH);

    } else if(valBack > 0) {
      analogWrite(3, valBack);
      analogWrite(5, valBack);
      digitalWrite(4, HIGH);
      digitalWrite(7, HIGH);

    } else if(valLeft > 0) {
      analogWrite(3, valLeft);
      analogWrite(5, valLeft);
      digitalWrite(4, HIGH);
      digitalWrite(6, HIGH);

    } else if(valRight > 0) {
      analogWrite(3, valRight);
      analogWrite(5, valRight);
      digitalWrite(2, HIGH);
      digitalWrite(7, HIGH);
    }
    else {
      analogWrite(3, 0);
      analogWrite(5, 0);
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
    }
  }
  
}
