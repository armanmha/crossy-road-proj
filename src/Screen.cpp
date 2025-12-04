#include "../header/Screen.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <unistd.h>
#include <sys/select.h>

namespace ScreenVars {
    termios origTermios;    // Stores original terminal settings
    bool hasOrig = false;   // Checks if the original terminal settings were preserved
} 

// CONSTRUCTOR
Screen::Screen() {
    if (!ScreenVars::hasOrig) {                             // If original terminal settings were not preserved
        tcgetattr(STDIN_FILENO, &ScreenVars::origTermios);  // Gets default terminal settings and stores in origTermios
        ScreenVars::hasOrig = true;                         // Original terminal settings ON
    }
}

// DESTRUCTOR
Screen::~Screen() {
    disableRawMode();
}

void Screen::enableMenuMode() {
    if (!ScreenVars::hasOrig) {                             // If original terminal settings were not preserved
        tcgetattr(STDIN_FILENO, &ScreenVars::origTermios);  // Gets default terminal settings and stores in origTermios
        ScreenVars::hasOrig = true;                         // Original terminal settings ON
    }

    termios raw = ScreenVars::origTermios;                  // Creates modifiable copy of terminal settings
    raw.c_lflag &= ~(ICANON | ECHO);                        // ICANON - disables waiting for enter and reads key instantly
                                                            // ECHO - disables printing key presses on screen

    raw.c_cc[VMIN] = 1;                                     // read() waits until at least 1 byte available
    raw.c_cc[VTIME] = 0;                                    // read() blocks until a byte arrives
    
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);                 // Applies new settings instantly and sets terminal in RAW MODE
    rawEnabled = true;
}

void Screen::enableGameMode() {
    if (!ScreenVars::hasOrig) {                             // If original terminal settings were not preserved
        tcgetattr(STDIN_FILENO, &ScreenVars::origTermios);  // Gets default terminal settings and stores in origTermios
        ScreenVars::hasOrig = true;                         // Original terminal settings ON
    }

    termios raw = ScreenVars::origTermios;                  // Creates modifiable copy of terminal settings
    raw.c_lflag &= ~(ICANON | ECHO);                        // ICANON - disables waiting for enter and reads key instantly
                                                            // ECHO - disables printing key presses on screen

    raw.c_cc[VMIN] = 0;                                     // read() waits until at least 0 byte available
    raw.c_cc[VTIME] = 0;                                    // read() blocks until a byte arrives
    
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);                 // Applies new settings instantly and sets terminal in RAW MODE
    rawEnabled = true;
}

void Screen::disableRawMode() {
    if (rawEnabled && ScreenVars::hasOrig) {                        // If raw is enabled and original settings preserved
        tcsetattr(STDIN_FILENO, TCSANOW, &ScreenVars::origTermios); // Reset terminal settings to default
        rawEnabled = false;                                         // Set RAW variable to false
    }
}

void Screen::clear() {
    // std::cout << "\x1b[3J\x1b[2J\x1b[H" << std::flush;              // Clear screen
    // changed to below line as screen was not fully clearing when going through menus
    std::cout << "\x1b[H\x1b[2J\x1b[3J" << std::flush;
}

// InputKey enumerated in Screen.h"
InputKey Screen::processInput() {
    char c;

    // check if first byte typed by user is valid
    if (read(STDIN_FILENO, &c, 1) != 1) {              
        return InputKey::Unknown; 
    }
    
    // check if enter was pressed
    if (c == '\n') {                            
        return InputKey::Enter;                         // Output ENTER
    }

    // check if variation of Q was pressed
    if (c == 'q' || c == 'Q') {
        return InputKey::Quit;    // Output QUIT
    }

    // easter egg: if user presses y or Y, toggle character mode
    if (c == 'y' || c == 'Y') {
        return InputKey::ToggleChar;
    }

    // WASD support
    if (c == 'w' || c == 'W') {
        return InputKey::Up;
    }

    if (c == 's' || c == 'S') {
        return InputKey::Down;
    }

    if (c == 'a' || c == 'A') {
        return InputKey::Left;
    }

    if (c == 'd' || c == 'D') {
        return InputKey::Right;
    }

    // Arrows begin with ESC character
    if (c == '\x1b') {                                  
        char seq[2];                                    // Read next 2 characters

        // if 3rd byte is not valid return keystroke as unknown
        if (read(STDIN_FILENO, &seq[0], 1) != 1) {
            return InputKey::Unknown; 
        } 
        if (read(STDIN_FILENO, &seq[1], 1) != 1) {
            return InputKey::Unknown;
        }

        // if valid arrow key is pressed
        if (seq[0] == '[') {                            
            switch (seq[1]) {
                case 'A': return InputKey::Up;
                case 'B': return InputKey::Down;
                case 'C': return InputKey::Right;
                case 'D': return InputKey::Left;
            }
        }
    }

    return InputKey::Unknown;
}

// InputKey enumerated in Screen.h"
InputKey Screen::processInputNonBlocking() {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0; // zero timeout

    int result = select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv);

    if (result > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
         char c;

        // check if first byte typed by user is valid
        if (read(STDIN_FILENO, &c, 1) != 1) {              
            return InputKey::Unknown; 
        }

        // check if enter was pressed
        if (c == '\n') {                            
            return InputKey::Enter;   // Output ENTER
        }

        // check if variation of Q was pressed
        if (c == 'q' || c == 'Q') {
            return InputKey::Quit;    // Output QUIT
        }

        // easter egg: if user presses y or Y, toggle character mode
        if (c == 'y' || c == 'Y') {
        return InputKey::ToggleChar;
        }

        // WASD support
        if (c == 'w' || c == 'W') {
            return InputKey::Up;
        }

        if (c == 's' || c == 'S') {
            return InputKey::Down;
        }

        if (c == 'a' || c == 'A') {
            return InputKey::Left;
        }

        if (c == 'd' || c == 'D') {
            return InputKey::Right;
        }

        // Arrows begin with ESC character
        if (c == '\x1b') {                                  
            char seq[2];                                    // Read next 2 characters
            ssize_t n = read(STDIN_FILENO, &seq[0], 1);

            if (n != 1) {
                // ESC alone -> pause
                return InputKey::Pause;
            }

            // if valid arrow key is pressed
            if (seq[0] == '[') {  
                if (read(STDIN_FILENO, &seq[1], 1) != 1) {
                    return InputKey::Unknown;
                }     

                switch (seq[1]) {
                    case 'A': return InputKey::Up;
                    case 'B': return InputKey::Down;
                    case 'C': return InputKey::Right;
                    case 'D': return InputKey::Left;
                }
            }

            return InputKey::Unknown;
        }
    }

    return InputKey::Unknown;
} 