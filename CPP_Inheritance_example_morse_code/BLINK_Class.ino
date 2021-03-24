#include <string>
#include <iostream>
#include <sstream>

Blink::Blink(int pin, std::string ledname, int state, int ontime, int offtime):
  Led(pin,ledname,state), ontime{ontime}, offtime{offtime}  {
    std::cout << "Blink five arg constructor!" << std::endl;
  }

void Blink::blink_led(int count) {
  for (int i=0; i<count; i++) {
    Blink::ledon(1);
    Blink::ledoff(1);
  }
}

void Blink::ledon(int count) {
    Led::set_state(HIGH);
    for (int i=0; i<count; i++) {
      delay(ontime * def_basetime);
    }
}
void Blink::ledoff(int count) {  
    Led::set_state(LOW);
    for (int i=0; i<count; i++) {
      delay(offtime * def_basetime);
    }
}


Blink::~Blink () {    
  std::cout << "Blink Destructor!" << std::endl;
}
