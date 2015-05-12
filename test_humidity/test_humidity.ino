#define HUMIDITY_SENSOR A8

void setup() {
  Serial.begin(9600);
}

void loop() {
  int humidity;
  int value;
  String temp;
  char char_array[] = "";
  
  humidity = 100-0.0245*analogRead(HUMIDITY_SENSOR);
  value = humidity;
  temp = (String) value;
  if (value < 10)
    temp = String("00"+temp);
  else if (value <100)
    temp = String("0"+temp);
  
  unsigned int temp_length = temp.length()+1;
  ((String)temp).toCharArray(char_array, temp_length);
  
  Serial.println(char_array);
  delay(500);
}

