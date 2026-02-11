#include <KPMIS.h>
KPMIS wall_e;
void setup() {
  wall_e.ledValue(0, 1);
  while (wall_e.readButton(0) == 0){}
  Serial.begin(9600);
}

void loop() {
  Serial.println(wall_e.readPot(0));
  delay(100);
  for (int i = 0; i < 6; i++) wall_e.ledValue(i, wall_e.readButton(i));
}
