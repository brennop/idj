#ifndef __ALIEN_H
#define __ALIEN_H

#include <memory>
#include <queue>
#include <vector>

#include "Component.h"
#include "Vec2.h"

class Alien : public Component {
public:
  Alien(GameObject &associated, int nMinions);
  ~Alien();
  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
private:
  class Action {
  public:
    enum ActionType {
      MOVE,
      SHOOT,
    };

    Action(ActionType type, float x, float y);

    ActionType type;
    Vec2 pos;
  };

  void AddAction(Action::ActionType type, float x, float y);

  Vec2 speed;
  int hp;

  void Move();

  std::queue<Action> taskQueue;
  std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif // __ALIEN_H

