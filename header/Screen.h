#pragma once

enum class InputKey {         // maps numbers to arrow keys
  Up,
  Down,
  Left,
  Right,
  Enter,
  Quit,
  Unknown
};

class Screen {
  private:
    bool rawEnabled = false;  // tracks if raw mode is enabled in terminal

  protected:
    static const int SCREEN_WIDTH = 80; // constant screen size in terminal

  public:
    Screen();                 // constructor 
    ~Screen();                // destructor
    
    void enableRawMode();     // enables raw mode
    void disableRawMode();    // disables raw mode

    InputKey processInput();  // processes key input
    void clear();             // clear screen
};