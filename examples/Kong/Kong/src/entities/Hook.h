#pragma once

#include "../arduboyTones/ArduboyTonesPitches.h"
#include "../arduboyTones/ArduboyTonesExt.h"
#include "../utils/Arduboy2Ext.h"
#ifndef STM32F103xB
#include "../Utils/Enums.h"
#else
#include "../utils/Enums.h"
#endif /* STM32F103xB */
#include "Base.h"

class Hook : public Base {

  public:

    Hook();


    // Methods ..

    void decCounter();
    void setSound(ArduboyTonesExt *sound);

  protected:

    ArduboyTonesExt *sound;

};

