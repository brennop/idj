#ifndef __TIMER_H
#define __TIMER_H

class Timer
{
public:
  Timer();

  void Update(float dt);
  void Restart();
  float Get();
private:
  float time;
};

#endif
