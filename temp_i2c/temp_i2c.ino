#include <Wire.h>
#include <math.h>
 
#define SLAVE_ADDRESS 0x08
#define TAG_TEMP "TEMP"
#define TAG_RAIN "RAIN"
#define TAG_HUM "HUMIDITY"
#define TEMPERATURE_SENSOR A11
#define RAIN_SENSOR A9
#define HUMIDITY_SENSOR A8

String var;
char c;

double temperature;
int int_temperature;
int rain;
int humidity;

String value;
char char_array[] = "";
 
// configuracion inicial
void setup() {
  // configuracion de los pines digitales
  pinMode(RAIN_SENSOR, INPUT);
  
  // inicializamos comunicacion serial
  //Serial.begin(9600);
  
  // inicializamos i2c como esclavo
  Wire.begin(SLAVE_ADDRESS);
  
  // llamadas para la comunicacion
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}
 
// bucle principal
void loop() {}

// llamada para recibir datos
void receiveData(int byteCount) {
  
  var = "";
  
  while (Wire.available() > 0) {
    c = Wire.read();
    var.concat(c);
  }
  
  //Serial.print("Received: ");
  //Serial.println(var);
 
  if (var == TAG_TEMP) {
    //Serial.println("TEMP request received");
    temperature = Thermister(analogRead(TEMPERATURE_SENSOR)) *100;
    int_temperature = (int) temperature; 
    value = (String) int_temperature;
  }
  
  else if (var == TAG_RAIN) {
    rain = digitalRead(RAIN_SENSOR);
    if (rain == 1)
      rain = 0;
    else if (rain == 0)
      rain = 1;
    value = (String) rain;   
  }
  
  else if (var == TAG_HUM) {
    humidity = 100-0.0245*analogRead(HUMIDITY_SENSOR);
    value = (String) humidity;
    if (humidity < 10)
      value = String("00" + value);
    else if (humidity <100)
      value = String("0" + value);
  }
  
  // Convert String to char*
  unsigned int value_length = value.length()+1;
  ((String)value).toCharArray(char_array, value_length);
  
}

// llamada para enviar datos
void sendData() {
  Wire.write(char_array);
  //Serial.print("sent: ");
  //Serial.println(char_array);
}
 
// A partir de la salida del termistor calculamos la temperatura
double Thermister(int RawADC) {
  double res;
  double Vo;
  
  Vo = (RawADC)*(3.3/4095.0);
  res = log(10000*(3.3/Vo-1));
  res = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * res * res ))* res );
  //res = 1 / (0.001126068758413 + ( 0.000234572594529 + (0.000000086312248 * res * res ))* res );
  res = res - 273.15;// Convert Kelvin to Celcius
  return res;
}
