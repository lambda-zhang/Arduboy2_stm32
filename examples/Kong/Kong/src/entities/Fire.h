#pragma once

#include "../utils/Arduboy2Ext.h"
#ifndef STM32F103xB
#include "../Utils/Enums.h"
#else
#include "../utils/Enums.h"
#endif /* STM32F103xB */
#include "Base.h"

class Fire : public Base {

  public:

    Fire();
 
    // Methods

    void update();


  protected:

};

