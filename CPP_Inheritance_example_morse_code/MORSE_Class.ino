#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cctype>

Morse::Morse(int pin, std::string ledname, int state, int ontime, int offtime) 
  :Blink(pin,ledname,state,ontime,offtime)  {
    std::cout << "Morse five arg constructor!" << std::endl;  
}

// Problem : Unable to use morsetable
//
//C:\Users\mikel\AppData\Local\Temp\arduino_build_532563\sketch\blinkled_class_1g_std.ino.cpp.o:(.literal._ZN5Morse21print_int_morse_tableEv+0x0): undefined reference to `Morse::morsetable'
//collect2.exe: error: ld returned 1 exit status
//exit status 1
void Morse::print_int_morse_table() {
    for (int i=0; i<26; i++) {
//        cout << morsetable[i] << " len=" << std::strlen(morsetable[i]) << endl;
    }       
}

void Morse::print_morse_table() {
    for (int i=0; i<26; i++) {
        cout << g_morsetable[i] << " len=" << std::strlen(g_morsetable[i]) << endl;
    }       
}

void Morse::process_letter_code(const char *s, size_t n) {
  cout << "=========================================" << endl;
  cout << "process_letter:";
  cout << s;
  cout << " n=";
  cout << n;
  cout << endl;
  
  for (size_t i=0; i<n; i++) {
    cout << "Index=" << i << endl;
    if (s[i] == '1') {
      cout << "One long dot" << endl;
      Blink::ledon(def_longdot);
      Blink::ledoff(1);
    } else if (s[i] == '0') {
      cout << "One short dot" << endl;
      Blink::ledon(def_shortdot);
      if (i < n-1) Blink::ledoff(1);
    } else {
      cout << "No a valid value" << endl;      
    }
  }
  cout << "=========================================" << endl;
}

void Morse::send_letter(char c) {
  cout << "=========================================" << endl;
  const char *code;
  if (std::isalpha(c)){
    if (std::isupper(c)){
      c = std::tolower(c);
    }
    cout << "send_letter:";
    cout << c;
    cout << endl;
        
    code = g_morsetable[c-'a'];
    cout <<  "code=" << code << endl;        
    Morse::process_letter_code(code,std::strlen(code));          
  } else {
    cout << "Need alpha letter (a to z)" << endl;
  }    
  cout << "=========================================" << endl;
}


void Morse::send_word(char *w, size_t n) {
  cout << "=========================================" << endl;
  cout << "send_word:";
  cout << w;
  cout << " n=";
  cout << n;
  cout << endl;

  for (size_t i=0; i<n; i++) {
    send_letter(w[i]);
    if (i < n-1) 
      Blink::ledoff(def_letter_sep);
    else 
      Blink::ledoff(def_word_sep);
  }
  cout << "=========================================" << endl;
}

void Morse::process_string(char *s, size_t n) {  
  char *word_start_p = s;
  char *word_end_p = nullptr;
  
  cout << "=========================================" << endl;
  cout << "process_string:";
  cout << s;
  cout << " n=";
  cout << n;
  cout << endl;

  // Search for the next word to process
  for (size_t i=0; i<n+1; i++) {
    if (std::isspace(s[i]) || i == n) {      
      cout << "Found space" << endl;
      cout << "index=" << i << endl;
      word_end_p = s + i + 1; // next word
      size_t len = word_end_p - word_start_p - 1;
      Morse::send_word(word_start_p, len);
      word_start_p = word_end_p;
    }
  }
  cout << "=========================================" << endl;    
}

Morse::~Morse () {    
  std::cout << "Morse Destructor!" << std::endl;
}
