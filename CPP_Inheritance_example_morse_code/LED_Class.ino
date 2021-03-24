#include <string>
#include <iostream>
#include <sstream>

//Led::Led():Led(DEFAULTLEDPIN,LOW,"unknown") {
//  std::cout << "Led No arg constructor!" << std::endl;
//}

//Led::Led(int pin, std::string ledname):Led(pin,LOW,ledname) {    
//  std::cout << "Led One arg constructor!" << std::endl;
//}

Led::Led(int pin, std::string ledname, int state): pin{pin}, ledname {ledname}, state{state} {    
  std::cout << "Led Three arg constructor!" << std::endl;

  if (state == HIGH || state == LOW) {
    this->state = state;  
  } else {    
    this->state = LOW; //default
  }

  pinMode(this->pin, OUTPUT);
  digitalWrite(this->pin, this->state);
}

void Led::set_state(int state) { 
  this->state = state;
  digitalWrite(this->pin, this->state);
}

void Led::toggle_state() { 
  if (state == HIGH) {
    state = LOW;
  } else {
    state = HIGH;
  }
  digitalWrite(this->pin, this->state);
}

int Led::get_state() const { 
  return (this->state);    
}

std::string Led::getstrinfo() const {
  std::string tempstr = ""; 
  std::string pinstr = ""; 
  std::stringstream ss;
  ss << pin;       
  ss >> pinstr;

  tempstr = tempstr + "Name:" + ledname + ", pin:" + pinstr + ", state:" + ((state == LOW) ? "LOW" : "HIGH");
  return tempstr; 
}  

std::ostream &operator<<(std::ostream &os, const Led &obj) {
  os << obj.getstrinfo() << endl;
  return os;
}

Led::~Led () {    
  std::cout << "Led Destructor!" << std::endl;
}
