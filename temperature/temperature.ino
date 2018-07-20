
#define MY_DEBUG
#define MY_BAUD_RATE 38400
#define MY_RADIO_NRF24

#define CHILD_ID_TEMP_1 0
#define CHILD_ID_TEMP_2 1

//#include <MySensors.h> 

//MyMessage msgTemp1(CHILD_ID_TEMP_1, V_TEMP);
//MyMessage msgTemp2(CHILD_ID_TEMP_2, V_TEMP);

#define THERMISTOR_PIN_1 A6
#define THERMISTOR_PIN_2 A1

float R1 = 10000;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float lastTemperature1 = 0.0;
float lastTemperature2 = 0.0;

void presentation()  
{ 
//  // Send the sketch version information to the gateway
//  sendSketchInfo("temperature", "1.0");
//
//  // Register all sensors to gw (they will be created as child devices)
//  present(CHILD_ID_TEMP_1, S_TEMP);
//  present(CHILD_ID_TEMP_2, S_TEMP);
}
 
void setup() {
  pinMode(THERMISTOR_PIN_1, INPUT);
  pinMode(THERMISTOR_PIN_2, INPUT);
  Serial.begin(38400); // Debugging only
} 

void loop() {
  
  float T = readTemperature(THERMISTOR_PIN_1);

  #ifdef MY_DEBUG
//    Serial.println(T);
  #endif

  if (lastTemperature1 != T) {
//    send(msgTemp1.set(T, 1));
    lastTemperature1 = T;
  }

//  T = readTemperature(THERMISTOR_PIN_2);
//
//  #ifdef MY_DEBUG
//    Serial.println(T);
//  #endif
//
//  if (lastTemperature2 != T) {
//    send(msgTemp2.set(T, 1));
//    lastTemperature2 = T;
//  }

    delay(1000);
//  sleep(1000);
}


float readTemperature(int pin) {
  int Vo = analogRead(pin);
  #ifdef MY_DEBUG
    Serial.println(Vo);
  #endif
  float R2 = R1 * (1023.0 / (float)Vo - 1.0); 
  float logR2 = log(R2);
  float t = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  return round((t - 273.15) * 2) / 2;
}

