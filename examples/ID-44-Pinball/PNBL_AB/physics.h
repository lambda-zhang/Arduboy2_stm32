#ifndef _PHYSICS_
#define _PHYSICS_

class Physics {
public:
  Physics(byte framerate, byte ticksperframe) {
    tickRate = framerate * ticksperframe;
    eachTickMillis = 1000 / tickRate;
    nextTickStart = 0;
  }

  Physics() : Physics(60, 10) {}

  bool nextTick() {
    long now = millis();
    byte remaining;

    if (now < nextTickStart) {
      return false;
    }

    nextTickStart = now + eachTickMillis;
    return true;
  }

protected:
  byte eachTickMillis;
  byte tickRate;
  long nextTickStart;
};

#endif
