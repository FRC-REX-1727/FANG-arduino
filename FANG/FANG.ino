#include <Rotary.h>

#include <Wire.h>
 
#define RADIUS      3.0
#define RESOLUTION  360

Rotary rotary = Rotary(2, 3);
int counter = 0;
float vel = 0;
const float DISTANCE_PER_PULSE = 2*RADIUS*PI/RESOLUTION;
unsigned long last_pulse = 0;
float dummy = 10;

void setup() {
  Serial.begin(9600);
  last_pulse = millis();
  attachInterrupt(0, rotate, CHANGE);
  attachInterrupt(1, rotate, CHANGE);
}

void loop() {
  Serial.print(counter);Serial.print("\t");Serial.println(vel);
}

// rotate is called anytime the rotary inputs change state.
void rotate() {
  unsigned char result = rotary.process();
  unsigned long curr_pulse = millis();  
  if (result == DIR_CW) {
    counter++;
    vel = DISTANCE_PER_PULSE/(curr_pulse-last_pulse);
    last_pulse = curr_pulse;
  } else if (result == DIR_CCW) {
    counter--;
    vel = DISTANCE_PER_PULSE/(curr_pulse-last_pulse);
    last_pulse = curr_pulse;
  }
}

