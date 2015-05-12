#include <math.h>

int temperatureSensor = A11;

void setup() {
  Serial.begin(9600);
}

void loop() {
  double temperature;
  //temperature = Thermister(analogRead(temperatureSensor));
  temperature = AdcValToC(analogRead(temperatureSensor));
  Serial.print(temperature);
  Serial.println(" C");
  /*int value;
  value = analogRead(temperatureSensor);
  Serial.println(value);*/
  delay(500);
}

// A partir de la salida del termistor calculamos la temperatura
double AdcValToC(int RawADC) {
  double res;
  double Vo;
  
  Vo = (RawADC)*(3.3/4095.0);
  res = log(10000*(3.3/Vo-1));
  res = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * res * res ))* res );
  //res = 1 / (0.001126068758413 + ( 0.000234572594529 + (0.000000086312248 * res * res ))* res );
  res = res - 273.15;// Convert Kelvin to Celcius
  return res;
}
