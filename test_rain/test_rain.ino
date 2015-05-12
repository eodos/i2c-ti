#define RAIN_SENSOR A9

void setup() {
  Serial.begin(9600);
  pinMode(RAIN_SENSOR, INPUT);
}

void loop() {
  int rain;
  rain = digitalRead(RAIN_SENSOR);
  Serial.println(rain);
  delay(500);
}

