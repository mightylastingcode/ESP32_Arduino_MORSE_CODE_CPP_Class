/*
 *  Author: Michael C. Li
 *  Date: 3/24/2021
 *  email: ----
 *  
 *  Project: An exmaple of using CPP Inheritnace Class Feature
 *  
 *  Use three classes (Led, Blink, and Morse) to generate the morse code for any sentence and 
 *  blink the LED accordingly.
 *   
 *  Device : ESP32 Dev Kit Rev C, Red LED, Green LED, two 333 ohm resistors.
 *  LED pin : Green GPIO 17, Red GPIO 17
 *  
 *  
 */

/*
 MIT License

Copyright (c) 2021 Michael Li

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define DEFAULTLEDPIN 16

#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cctype>

class Led {
  friend std::ostream &operator<<(std::ostream &os, const Led &obj);
protected:
    static constexpr int def_ledpin = 16;  
    static constexpr const char *def_ledname = "Unnamed Led";  
    static constexpr int def_ledstate = LOW;  
protected: // allowed the derived class to access data members
  // Order needs to be consistent with the 3 arg constructor
  int pin;  // GPIO pin
  std::string ledname;  
  int state;  // LOW or HIGH
public:
//  Led();
//  Led(int pin, std::string ledname);
  Led(int pin=def_ledpin, std::string ledname=def_ledname, int state=def_ledstate);  // Need to be in the same order as the declaration part
                                                                                     //pin, ledname, state
  void set_state(int state);
  void toggle_state();
  int get_state() const;
  std::string getstrinfo() const;
  ~Led ();
};

class Blink : public Led {
protected:
    static constexpr int def_basetime = 1000;  // 1 sec  
    static constexpr int def_ontime = 1;
    static constexpr int def_offtime = 1;    
protected:
  int ontime; // in 1 second
  int offtime; // in 1 second
public:  
  Blink(int pin=def_ledpin, std::string ledname=def_ledname, int state=def_ledstate, int ontime=def_ontime, int offtime=def_offtime);
  void blink_led(int count);
  void ledon(int count);
  void ledoff(int count);
  ~Blink ();
};


const char g_morsetable[26][100] = {
        "01", "1000", "1010", "100", "0", // A,B,C,D,E
        "0011", "110", "0000", "00", "0111", // F,G,H,I,J
        "101", "0100", "11", "10", "111", // K,L,M,N,O
        "0110", "1101", "010", "000", "1", // P,Q,R,S,T
        "001", "0001", "011", "1001", "1011", // U,V,W,X,Y
        "1100"  //Z
};

class Morse : public Blink {
private:
  static constexpr const char morsetable[26][100] = {
        "01", "1000", "1010", "100", "0", // A,B,C,D,E
        "0011", "110", "0000", "00", "0111", // F,G,H,I,J
        "101", "0100", "11", "10", "111", // K,L,M,N,O
        "0110", "1101", "010", "000", "1", // P,Q,R,S,T
        "001", "0001", "011", "1001", "1011", // U,V,W,X,Y
        "1100"  //Z  1 = a long dot 0 = a short dot
    };  // not allowed to be referenced by the class method.
  static constexpr int def_shortdot = 1;  // 1 time unit (led on)
  static constexpr int def_longdot = 3;   // 3 time unit (led on)
  static constexpr int def_letter_sep = 3; // 3 time unit (led off)
  static constexpr int def_word_sep = 7;   // 7 time unit (led off)
private:  
  void process_letter_code(const char *s, size_t n);
public:
  Morse(int pin=def_ledpin, std::string ledname=def_ledname, int state=def_ledstate, int ontime=def_ontime, int offtime=def_offtime);
  void send_letter(char c);    
  void send_word(char *w, size_t n);
  void process_string(char *s, size_t n);
  void print_morse_table();  
  void print_int_morse_table();
  ~Morse ();
  
};

using namespace std;

void setup() {
  // Serial port for debugging purposes  
  Serial.begin(115200); 
  cout << __cplusplus << endl;
 
}

void loop() {

//#define TESTLEDCLASS
#ifdef TESTLEDCLASS
  
  cout << "=================================== Root Class: Led  ==========================================" << endl;

  Led greenled0;   // 16 UNKNOWN LOW
  Led greenled1 {27}; //27 UNKNOWN LOW
  Led greenled2 {27,"greenled2"}; // 27 greenled2 LOW
  Led greenled3 {27,"greenled3",HIGH}; // 16 greenled3 HIGH

  cout << "greenled0 obj: " << greenled0;
  cout << "greenled1 obj: " << greenled1;
  cout << "greenled2 obj: " << greenled2;
  cout << "greenled3 obj: " << greenled3;

  Led greenled {16,"greenled",HIGH}; // 16 greenled3 HIGH
  Led redled {17,"redled",HIGH};

  cout << greenled;
  cout << redled;

  delay(1000);
  greenled.set_state(LOW);
  redled.set_state(LOW);
  
  cout << greenled;
  cout << redled;

  cout << "===========dummyled is the shallow copy of greenled==================" << endl;
  Led dummyled {greenled};    
  cout << dummyled;
  cout << "Loop" << endl;

  {
    Led yellowled {18,"yellowled",LOW};
    cout << yellowled;
  }
  // yellowled obj is destroyed.

  cout << "===========toggle Green and Red LED==================" << endl;
  for (size_t i=0; i< 10; i++) {
    if (greenled.get_state() == HIGH) {
      greenled.set_state(LOW);
    }else {
      greenled.set_state(HIGH);
    }
    redled.toggle_state();
    cout << greenled;
    cout << redled;
    delay(1000);    
  }    
  cout << "*** End of Test ***" << endl;
  
#endif // TESTLEDCLASS


//#define TESTBLINKCLASS
#ifdef TESTBLINKCLASS
  cout << "=================================== Derived Class: Blink  ==========================================" << endl;

  Blink greenled;   // 16 UNKNOWN LOW
  Blink greenled1 {27}; //27 UNKNOWN LOW
  Blink greenled2 {27,"greenled2"}; // 27 greenled2 LOW
  Blink greenled3 {27,"greenled3",HIGH}; // 16 greenled3 HIGH

  cout << "greenled obj: " << greenled;
  cout << "greenled1 obj: " << greenled1;
  cout << "greenled2 obj: " << greenled2;
  cout << "greenled3 obj: " << greenled3;

  Blink redled {17,"redled",HIGH};
  
  cout << greenled;
  cout << redled;
  delay(1000);
  greenled.set_state(HIGH);
  redled.set_state(HIGH);
  
  cout << greenled;
  cout << redled;

  greenled.set_state(LOW);
  redled.set_state(LOW);

  delay(1000);

  cout << "===========Blink Green LED one, twice, three times ==================" << endl;
  for (int i=1; i<4; i++) {
    greenled.blink_led(i);
    delay(3000);
  }

  cout << "*** End of Test ***" << endl;

#endif // TESTBLINKCLASS

#define TESTMORSECLASS
#ifdef TESTMORSECLASS
  cout << "=================================== Derived Class: Morse  ==========================================" << endl;

//  Morse m;
  Morse m {17,"redled",HIGH,2,2};
  cout << m;
//  m.print_morse_table();
  m.print_int_morse_table();
//  m.send_letter('a');
//  m.send_word("This", std::strlen("This"));
  m.process_string("This is a test", std::strlen("This is a test"));

 cout << "*** End of Test ***" << endl;
 
#endif // TESTMORSECLASS
  
  while (1) {
      delay(3000);
 }
 
}
