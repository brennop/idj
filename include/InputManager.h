#ifndef __INPUT_MANAGER_H
#define __INPUT_MANAGER_H

#include "Vec2.h"

#define INCLUDE_SDL
#include "SDL_include.h"

#define RIGHT_ARROW_KEY   0xCF
#define LEFT_ARROW_KEY    0xD0
#define DOWN_ARROW_KEY    0xD1
#define UP_ARROW_KEY      0xD2
#define ESCAPE_KEY        SDLK_ESCAPE
#define MOUSE1 SDL_BUTTON_LEFT
#define MOUSE2 SDL_BUTTON_RIGHT

class InputManager {
public:
  void Update();
  bool KeyPress(int key);
  bool KeyRelease(int key);
  bool IsKeyDown(int key);

  bool MousePress(int button);
  bool MouseRelease(int button);
  bool IsMouseDown(int button);

  int GetMouseX();
  int GetMouseY();
  Vec2 GetMousePos();

  bool QuitRequested();

  static InputManager &GetInstance();

private:
  InputManager();
  ~InputManager();

  bool mouseState[6];
  int mouseUpdate[6];

  bool keyState[416];
  int keyUpdate[416];

  bool quitRequested;
  int updateCounter;
  int mouseX;
  int mouseY;
};

#endif // __INPUT_MANAGER_H
