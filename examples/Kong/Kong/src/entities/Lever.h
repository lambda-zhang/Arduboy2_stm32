#pragma once

#include "../arduboyTones/ArduboyTonesPitches.h"
#include "../arduboyTones/ArduboyTonesExt.h"
#include "../utils/Arduboy2Ext.h"
#ifndef STM32F103xB
#include "../Utils/Enums.h"
#else
#include "../utils/Enums.h"
#endif /* STM32F103xB */
#include "../map/Coordinates.h"
#include "Crane.h"
#include "Base.h"

class Lever : public Base {

  public:

    Lever();

 
    // Properties ..

    LeverPosition getPosition();

    void setPosition(LeverPosition position);
    void setCrane(Crane *crane);


    // Methods

    void update();
    void setSound(ArduboyTonesExt *sound);


  protected:

    ArduboyTonesExt *sound;
    LeverPosition position = LeverPosition::Off;
    Crane *crane;

};

