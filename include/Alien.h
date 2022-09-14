#ifndef __ALIEN_H
#define __ALIEN_H

#include <memory>
#include <queue>
#include <vector>

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

class Alien : public Component {
public:
  Alien(GameObject &associated, int nMinions);
  ~Alien();
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void NotifyCollision(GameObject &other) override;

  static int alienCount;
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

  enum AlienState {
    MOVING,
    ATTACKING,
  };

  AlienState state;
  Timer stateTimer;
  Timer shootCooldown;

  float fireRate;
  float fireAngle;
  int attackType;

  Vec2 speed;
  int hp;

  void Move();

  std::queue<Action> taskQueue;
  std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif // __ALIEN_H

