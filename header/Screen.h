#pragma once

enum class InputKey {
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
    bool rawEnabled = false;

  protected:
    static const int SCREEN_WIDTH = 80;

  public:
    Screen();
    ~Screen();
    
    void enableRawMode();
    void disableRawMode();

    InputKey processInput();
    void clear();
};