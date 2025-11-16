#pragma once

enum class InputKey {         // Maps numbers to arrow keys
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
    bool rawEnabled = false;  // Tracks if raw mode is enabled in terminal

  protected:
    static const int SCREEN_WIDTH = 80; // Width of terminal screen

  public:
    Screen();
    ~Screen();
    
    void enableRawMode();
    void disableRawMode();

    InputKey processInput();  // Processes user input
    void clear();             // Clears screen/terminal
};