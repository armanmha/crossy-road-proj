#pragma once

#include <vector>

using std::vector;

class Screen {
 protected: 
   vector<int> cursorPosition;
   static const int SCREEN_WIDTH = 80;

 public: 
   void processInput(char input);

};