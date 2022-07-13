#ifndef __INPUT_MANAGER_H
#define __INPUT_MANAGER_H

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

  bool QuitRequested();

  static InputManager &GetInstance();

private:
  InputManager();
  ~InputManager();
};

#endif // __INPUT_MANAGER_H
