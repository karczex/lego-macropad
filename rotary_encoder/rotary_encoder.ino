#include "rotary_encoder.h"

constexpr int CLK = 3; // Connected to CLK on KY-040
constexpr int DT = 4; // Connected to DT on KY-040

int previous_clk = 0;

void volume_up(){
  Serial.println("VOLUME_UP");
}

void volume_down(){
   Serial.println("VOLUME_DOWN");
}

bool is_rotating(int previous_pin_state, int pin_state){
  return previous_pin_state != pin_state;
}

direction get_direction(int clk_pin_state, int dt_pin_state){
  if(clk_pin_state == dt_pin_state){
    return direction::clockwise;
  }
  return direction::counter_clockwise;
}


void setup() {
  pinMode (CLK,INPUT);
  pinMode (DT,INPUT);
  /* Read Pin A 
    Whatever state it's in will reflect the last position 
  */
  previous_clk = digitalRead(CLK);
  Serial.begin (9600);
   while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
}


void loop() {
  int clk = digitalRead(CLK);
  int dt = digitalRead(DT);
  if(is_rotating(previous_clk, clk)){
    auto dir = get_direction(dt,clk);
    switch(dir) {
      case direction::clockwise:
        volume_up();
        break;
      case direction::counter_clockwise:
        volume_down();
        break;
      default:
        break;
    }
 
  }
  previous_clk = clk;
 
}
