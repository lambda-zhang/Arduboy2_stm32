#pragma once

#include "../utils/Arduboy2Ext.h"
#ifndef STM32F103xB
#include "../Utils/Enums.h"
#else
#include "../utils/Enums.h"
#endif /* STM32F103xB */

class Base {

  public:

    Base();
 

    // Properties ..

    uint8_t getCounter();
    void setCounter(uint8_t counter);


  protected:

    uint8_t counter = 0;

};

