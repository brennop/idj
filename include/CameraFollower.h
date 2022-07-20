#ifndef __CAMERA_FOLLOWER_H
#define __CAMERA_FOLLOWER_H

#include "GameObject.h"

class CameraFollower : public Component {
public:
  CameraFollower(GameObject &go);
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
};

#endif // __CAMERA_FOLLOWER_H
