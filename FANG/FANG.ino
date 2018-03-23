#include <Rotary.h>

#include <Wire.h>
 
#define RADIUS        3.0
#define RESOLUTION    360
#define ROTARY_PIN_A  2
#define ROTARY_PIN_B  3

Rotary rotary = Rotary(ROTARY_PIN_A, ROTARY_PIN_B);
int counter = 0;
float vel = 0;
const float DISTANCE_PER_PULSE = 2*RADIUS*PI/RESOLUTION;
unsigned long last_pulse = 0;
float dummy = 10;

void setup() {
  Serial.begin(9600);

  // Start timer setup
  
  cli();                    // disable global interrupts
  TCCR1A = 0;               // clear timer 1 A register
  TCCR1B = 0;               // clear timer 1 B register
  OCR1A = 15624;            // set compare match register to desired timer count
  TCCR1B |= (1 << WGM12);   // turn on CTC mode
  TCCR1B |= (1 << CS10);    // Set CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12);    // Set CS12 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  sei();                    // enable global interrupts

  // End Timer setup
  
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

