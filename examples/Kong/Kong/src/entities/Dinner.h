#pragma once

#include "../utils/Arduboy2Ext.h"
#ifndef STM32F103xB
#include "../Utils/Enums.h"
#else
#include "../utils/Enums.h"
#endif /* STM32F103xB */
#include "Base.h"

class Dinner : public Base {

  public:

    Dinner();
 

    // Properties ..

    bool isVisible();
    uint8_t getFood();
    
    void setVisible(bool visible);
    void setFood(uint8_t visfoodible);


    // Methods

    void update();
    void incFood();


  protected:

    uint8_t food = 0;
    bool visible = true;

};

