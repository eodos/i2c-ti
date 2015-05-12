#include <Wire.h>

#define LED RED_LED
#define SLAVE_ADDRESS 0x08

int number = 0;
int state = 0;

void setup() {                
  pinMode(LED, OUTPUT);     
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop() {}

void receiveData(int byteCount) {
  while(Wire.available()) {
    number = Wire.read();
    if (number == 1) {
      if (state == 0) {
        digitalWrite(LED, HIGH);
        state = 1;
      }
      else {
        digitalWrite(LED, LOW);
        state = 0;
      }
    }
  }
}

void sendData() {
  Wire.write(number);
}
