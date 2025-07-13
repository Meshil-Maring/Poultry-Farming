#include <HX711.h>

#define DOUT 5
#define CLK 18

HX711 scale;

void setupWeightSensor() {
  scale.begin(DOUT, CLK);
  scale.tare();
  scale.set_scale(23200);
}

void readWeight() {
  float weight = scale.get_units(10) - 18;
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" kg");
}
