#pragma once

#include "../utils/Arduboy2Ext.h"
#ifndef STM32F103xB
#include "../Utils/Enums.h"
#else
#include "../utils/Enums.h"
#endif /* STM32F103xB */
#include "../map/Coordinates.h"
#include "Base.h"

class Crane : public Base {

  public:

    Crane();
 
    // Properties ..

    CranePosition getPosition();
    bool getLiftPlayer();

    void setPosition(CranePosition position);
    void setLiftPlayer(bool liftPlayer);


    // Methods

    void turnOn();
    void turnOff();
    void update();

  private:

    void swingHook();

  protected:

    CranePosition position = CranePosition::Declined;
    CraneState state = CraneState::Dormant;
    Movements hookDirection = Movements::Right;
    uint8_t hook = 2;
    bool liftPlayer;

};

