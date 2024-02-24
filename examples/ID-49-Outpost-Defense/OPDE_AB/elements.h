#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "globals.h"

#define STATE_HIDDEN       0
#define STATE_VISIBLE      1
#define STATE_MOVE_LEFT    2
#define STATE_MOVE_RIGHT   4
#define STATE_CLIMB_LEFT   5
#define STATE_CLIMB_RIGHT  6
#define STATE_ATTACK_LEFT  7
#define STATE_ATTACK_RIGHT 8
#define STATE_EXPLODING    9

#define EGG_STATE_FALL    7
#define EGG_STATE_STOP    8
#define EGG_STATE_HATCH   9

#define TYPE_TROOPER      0   //4x4 element
#define TYPE_AILEN        1   //4x4 element
#define TYPE_BARRACADE    2   //4x4 element

#define TYPE_EGG          10   //8x8 element
#define TYPE_WALKER       11   //8x8 element
#define TYPE_AILEN_WALKER 12   //8x8 element

#define TYPE_FLAG         20   //8x8 element

#define TEST_NO_COLLISION  0
#define TEST_ELEMENT_LEFT  1
#define TEST_ELEMENT_RIGHT 2
#define TEST_COLLISION     3

#define STEP_LENGTH  2
#define COUNTER_START    25


#define MAX_ELEMENT_RECORDS 16

struct LevelElement
{
  unsigned char id;          //elment identifier
  unsigned char type;        //element type
  unsigned char x;           // y position
  unsigned char y;           // x position
  unsigned char state;       //determines the state of the the element
  unsigned char speed;       //deternimes how fast the object moves
  unsigned char step;        //used to maintain animation step
  unsigned char counter;     //used for timed events
  unsigned char speed_counter;
  unsigned char life;        //used to determine how much damage the element can take
};

LevelElement levelElements[MAX_ELEMENT_RECORDS];
char element_count = 0;

void level_element_add(char type, char x, char y, char state, char speed, char life)
{
      levelElements[element_count].id = element_count;
      levelElements[element_count].type = type;
      levelElements[element_count].x = x;
      levelElements[element_count].y = y;
      levelElements[element_count].step = 0;
      levelElements[element_count].state = state;
      levelElements[element_count].counter = COUNTER_START;
      levelElements[element_count].speed = speed;
      levelElements[element_count].speed_counter = 0;
      levelElements[element_count].life = life;
      element_count++;  
}

//sort all of the used elements by x,y axis (help with collision detection)
void level_elements_sort_xy () {
  //
  for (char i=0; i < (element_count-1); i++) {
    for (char o=0; o < (element_count-(i+1)); o++) {

      //convert x,y to a single number for comparison
      //so a single pass sort can be used (save processing time)
      short curr_xy = (levelElements[o].y * 128) + levelElements[o].x;
      short next_xy = (levelElements[o+1].y * 128) + levelElements[o+1].x;
      
      if (curr_xy > next_xy) {
        LevelElement e = levelElements[o];
        
        levelElements[o] = levelElements[o+1];
        levelElements[o+1] = e;
      }
    }
  }
}

//test for collision in level elements
char level_test_element (LevelElement element, char testX, char testY)
{
   if ((element.y + 8) < testY) return TEST_NO_COLLISION;  //no collision
   if (element.y > (testY + 8)) return TEST_NO_COLLISION;  //no collision
   if ((element.x + 8) < testX) return TEST_ELEMENT_LEFT;  //on same y, element x
   if (element.x > (testX + 8)) return TEST_ELEMENT_RIGHT;  //on same y, element x 
   return TEST_COLLISION;
}

//Egg behavior
LevelElement egg_move(LevelElement element)
{
  char adjust;
  
  //draw new monster bitmap
  if (element.state > STATE_HIDDEN)
  {
  
    if (element.speed_counter == element.speed)
    {
        element.speed_counter = 0;
       
        switch (element.state)
        {
       
        case EGG_STATE_FALL:
               element.state = EGG_STATE_FALL;
               //check above; if it is possible to move down, then do so
               if (level_check_move_h(element.x, element.y +8 +STEP_LENGTH, adjust) == 0)
               {            
                 if ((element.y + 8 + STEP_LENGTH) < 60)
                 {
                   element.y += STEP_LENGTH;
                 } else {
                   //fallen past the normal ledge, so we will place
                   //the egg on the platform
                   element.x = 40;
                   element.y = 47;
                   element.state = EGG_STATE_STOP;
                 }
               } else {
                 element.y = (adjust * 8) - 9;
                 element.state = EGG_STATE_STOP;
               }
               break;    
         
        case EGG_STATE_STOP:
               element.state = EGG_STATE_STOP;
         if (element.counter > 0)
         {
            element.counter--;
         } else {
            element.state = EGG_STATE_HATCH;
         }
         break;
         
        case EGG_STATE_HATCH:
               element.state = EGG_STATE_HATCH;
               element.step++;
               if (element.step > 2)
         { 
            element.state = STATE_HIDDEN;
            level_element_add(TYPE_AILEN, element.x, element.y+4, STATE_MOVE_LEFT, 4,1);
            level_element_add(TYPE_AILEN_WALKER, element.x, element.y, STATE_MOVE_LEFT,6,1);
         }
         break;         
        }
       }
       else
       {
         element.speed_counter++;
       }
       sprites.drawSelfMasked(element.x, element.y, egg_img, element.step);
       
  }
  return element;
}


//Alien behavior
LevelElement ailen_move(LevelElement element)
{
  char adjust;

  //draw new monster bitmap
  if (element.state > STATE_HIDDEN)
  {
    if (element.speed_counter == element.speed)
    {
        element.speed_counter = 0;
        element.step++;
        if (element.step > 1) {
          element.step = 0;
          
          switch (element.state) {
            case STATE_EXPLODING:
              //if the element was exploding, it is now hidden
              element.state = STATE_HIDDEN;
              break;

            case STATE_ATTACK_LEFT:
              element.state = STATE_MOVE_LEFT;
              break;

            case STATE_ATTACK_RIGHT:
              element.state = STATE_MOVE_RIGHT;
              break;
          }
          
        }
       
        switch (element.state)
        { 
          case STATE_MOVE_LEFT:
            if (element.x > STEP_LENGTH) {
             if (level_check_move_v(element.x - STEP_LENGTH, element.y+4, adjust)== 1 ) {
                    element.x -= STEP_LENGTH;
                    element.state = STATE_MOVE_LEFT;
             } else {
               element.state = STATE_MOVE_RIGHT;
             }
             if (level_check_move(element.x, element.y+4) == 4) {
                element.y -= STEP_LENGTH;
             }             
            } else {
              element.state = STATE_MOVE_RIGHT;
            }
            break;

          case STATE_MOVE_RIGHT:
            if (element.x < (128- STEP_LENGTH)) {
             if (level_check_move_v(element.x + STEP_LENGTH, element.y+4, adjust) == 1 ) {
                    element.x += STEP_LENGTH;
                    element.state = STATE_MOVE_RIGHT;
             } else {
                element.state = STATE_MOVE_LEFT;
             }
             if (level_check_move(element.x+4, element.y+4) == 5) {
                element.y -= STEP_LENGTH;
             }             
            } else {
              element.state = STATE_MOVE_LEFT; 
            }
            break;
        }
         
    }

    switch (element.state) {
      case STATE_EXPLODING:
      sprites.drawSelfMasked(element.x, element.y, explosion_img, element.step);
      break;
      
      case STATE_ATTACK_LEFT:
      sprites.drawSelfMasked(element.x, element.y, ailen_img, element.step + 2);
      break;

      case STATE_ATTACK_RIGHT:
      sprites.drawSelfMasked(element.x, element.y, ailen_img, element.step + 4);
      break;

      default:
      sprites.drawSelfMasked(element.x, element.y, ailen_img, element.step);
      break;
    }
    element.speed_counter++;
    
  }
  return element;
}

//trooper behavior
LevelElement trooper_move(LevelElement element)
{
  char adjust;

  //draw new monster bitmap
  if (element.state > STATE_HIDDEN)
  {
    if (element.speed_counter == element.speed)
    {
        element.speed_counter = 0;
        element.step++;
        if (element.step > 1) {
          element.step = 0;

          switch (element.state) {
            case STATE_EXPLODING:
              //if the element was exploding, it is now hidden
              element.state = STATE_HIDDEN;
              break;

            case STATE_ATTACK_LEFT:
              element.state = STATE_MOVE_LEFT;
              break;

            case STATE_ATTACK_RIGHT:
              element.state = STATE_MOVE_RIGHT;
              break;
          }
        }
       
        switch (element.state)
        { 
          case STATE_MOVE_LEFT:
            if (element.x > STEP_LENGTH) {
             if (level_check_move_v(element.x - STEP_LENGTH, element.y+4, adjust)== 1 ) {
                    element.x -= STEP_LENGTH;
                    element.state = STATE_MOVE_LEFT;
             } else {
               element.state = STATE_MOVE_RIGHT;
             }
             if (level_check_move(element.x, element.y+4) == 4) {
                element.y -= STEP_LENGTH;
             }             
            } else {
              element.state = STATE_MOVE_RIGHT;
            }
            break;


          case STATE_MOVE_RIGHT:
            if (element.x < (128- STEP_LENGTH)) {
             if (level_check_move_v(element.x + STEP_LENGTH, element.y+4, adjust) == 1 ) {
                    element.x += STEP_LENGTH;
                    element.state = STATE_MOVE_RIGHT;
             } else {
                element.state = STATE_MOVE_LEFT;
             }
             if (level_check_move(element.x+4, element.y+4) == 5) {
                element.y -= STEP_LENGTH;
             }             
            } else {
              element.state = STATE_MOVE_LEFT; 
            }
            break;
        }
         
    }


    switch (element.state) {
      case STATE_EXPLODING:
      sprites.drawSelfMasked(element.x, element.y, explosion_img, element.step);
      break;
      
      case STATE_MOVE_LEFT:
      sprites.drawSelfMasked(element.x, element.y, trooper_img, element.step+2);
      break;

      case STATE_MOVE_RIGHT:
      sprites.drawSelfMasked(element.x, element.y, trooper_img, element.step);
      break;

      case STATE_ATTACK_LEFT:
      sprites.drawSelfMasked(element.x, element.y, trooper_img, element.step+4);
      break;

      case STATE_ATTACK_RIGHT:
      sprites.drawSelfMasked(element.x, element.y, trooper_img, element.step+6);
      break;    
    }

    element.speed_counter++;
    
  }
  return element;
}

//Alien walker behavior
LevelElement ailen_walker_move(LevelElement element)
{
  char adjust;

  //draw new monster bitmap
  if (element.state > STATE_HIDDEN)
  {
    if (element.speed_counter == element.speed)
    {
        element.speed_counter = 0;
        element.step++;
        if (element.step > 2) {
          element.step = 0;

          switch (element.state) {
            case STATE_EXPLODING:
              //if the element was exploding, it is now hidden
              element.state = STATE_HIDDEN;
              break;

            case STATE_ATTACK_LEFT:
              element.state = STATE_MOVE_LEFT;
              break;

            case STATE_ATTACK_RIGHT:
              element.state = STATE_MOVE_RIGHT;
              break;
          }
        }
       
        switch (element.state)
        {         
          case STATE_MOVE_LEFT:
            if (element.x > STEP_LENGTH) {

             //check underneath to see if there is a platform
             if (level_check_move_v(element.x - STEP_LENGTH, element.y+4, adjust)== 1 ) {
                    element.x -= STEP_LENGTH;
                    element.state = STATE_MOVE_LEFT;
             } else {
               element.state = STATE_MOVE_RIGHT;
             }
             if (level_check_move(element.x, element.y+8) == 4) {
                element.y -= STEP_LENGTH;
             }
             
            } else {
              element.state = STATE_MOVE_RIGHT; 
            }
            break;


          case STATE_MOVE_RIGHT:
            if (element.x < (128- STEP_LENGTH)) {
             if (level_check_move_v(element.x + STEP_LENGTH, element.y+4, adjust) == 1 ) {
                    element.x += STEP_LENGTH;
                    element.state = STATE_MOVE_RIGHT;
             } else {
                element.state = STATE_MOVE_LEFT;
             }

             if (level_check_move(element.x+8, element.y+8) == 5) {
                element.y -= STEP_LENGTH;
             }
            } else {
              element.state = STATE_MOVE_LEFT; 
            }
            break;
        }
         
    }

    switch (element.state) {
      case STATE_EXPLODING:
      sprites.drawSelfMasked(element.x, element.y, explosion_img, element.step);
      break;
      
      case STATE_ATTACK_LEFT:
      sprites.drawSelfMasked(element.x, element.y, ailen_walker_img, element.step + 3);
      break;

      case STATE_ATTACK_RIGHT:
      sprites.drawSelfMasked(element.x, element.y, ailen_walker_img, element.step + 6);
      break;

      default:
      sprites.drawSelfMasked(element.x, element.y, ailen_walker_img, element.step);
      break;
    }

    element.speed_counter++;
    
  }
  return element;
}

//walker behavior
LevelElement walker_move(LevelElement element)
{
  char adjust;

  //draw new monster bitmap
  if (element.state > STATE_HIDDEN)
  {
    if (element.speed_counter == element.speed)
    {
        element.speed_counter = 0;
        element.step++;
        if (element.step > 3) {
          element.step = 0;

          switch (element.state) {
            case STATE_EXPLODING:
              //if the element was exploding, it is now hidden
              element.state = STATE_HIDDEN;
              break;

            case STATE_ATTACK_LEFT:
              element.state = STATE_MOVE_LEFT;
              break;

            case STATE_ATTACK_RIGHT:
              element.state = STATE_MOVE_RIGHT;
              break;
          }
        }
       
        switch (element.state)
        { 
          case STATE_MOVE_LEFT:
            if (element.x > STEP_LENGTH) {
             if (level_check_move_v(element.x - STEP_LENGTH, element.y+4, adjust)== 1 ) {
                    element.x -= STEP_LENGTH;
                    element.state = STATE_MOVE_LEFT;
             } else {
               element.state = STATE_MOVE_RIGHT;
             }
             if (level_check_move(element.x, element.y+8) == 4) {
                element.y -= STEP_LENGTH;
             }             
            } else {
              element.state = STATE_MOVE_RIGHT;
            }
            break;


          case STATE_MOVE_RIGHT:
            if (element.x < (128- STEP_LENGTH)) {
             if (level_check_move_v(element.x + STEP_LENGTH, element.y+4, adjust) == 1 ) {
                    element.x += STEP_LENGTH;
                    element.state = STATE_MOVE_RIGHT;
             } else {
                element.state = STATE_MOVE_LEFT;
             }
             if (level_check_move(element.x+8, element.y+8) == 5) {
                element.y -= STEP_LENGTH;
             }             
            } else {
              element.state = STATE_MOVE_LEFT; 
            }
            break;
        }
         
    }
    
    switch (element.state) {
      case STATE_EXPLODING:
      sprites.drawSelfMasked(element.x, element.y, explosion_img, element.step);
      break;
      
      case STATE_MOVE_LEFT:
      sprites.drawSelfMasked(element.x, element.y, walker_img, element.step+4);
      break;

      case STATE_MOVE_RIGHT:
      sprites.drawSelfMasked(element.x, element.y, walker_img, element.step);
      break;

      case STATE_ATTACK_LEFT:
      sprites.drawSelfMasked(element.x, element.y, walker_img, element.step+12);
      break;

      case STATE_ATTACK_RIGHT:
      sprites.drawSelfMasked(element.x, element.y, walker_img, element.step+8);
      break;    
    }

    element.speed_counter++;
    
  }
  return element;
}


bool element_ignore(LevelElement element, LevelElement hittingElement)
{
  if ((element.state == STATE_EXPLODING)||(element.state == STATE_HIDDEN)) return true;
  if ((hittingElement.state == STATE_HIDDEN)||(hittingElement.state == STATE_EXPLODING)) return true;

  //Ignore "friendly" (or neutral) units
  switch (element.type) {
    case TYPE_TROOPER:
    case TYPE_WALKER:
      if ((hittingElement.type == TYPE_TROOPER) || (hittingElement.type == TYPE_WALKER)|| (hittingElement.type == TYPE_EGG)) return true;
      break;

    case TYPE_AILEN:
    case TYPE_AILEN_WALKER:
      if ((hittingElement.type == TYPE_AILEN) || (hittingElement.type == TYPE_AILEN_WALKER) || (hittingElement.type == TYPE_EGG)) return true;
      break; 
  }
  return false;
}

LevelElement element_hit(LevelElement element, LevelElement hittingElement)
{
  //see if we need to ignore the element
  if (element_ignore(element, hittingElement)) return element;

  //check enemy action.  If they are attacking, register hit
  if ((hittingElement.state == STATE_ATTACK_LEFT) || (hittingElement.state == STATE_ATTACK_RIGHT)) {
    element.state = STATE_EXPLODING;
  } else {

    //Otherwise start attacking enemy
    if (element.x > hittingElement.x) {
      element.state = STATE_ATTACK_LEFT;
    } else {
      element.state = STATE_ATTACK_RIGHT;
    }
  }
  return element;
}

LevelElement element_spotted(LevelElement element, LevelElement hittingElement, char newState)
{
  //see if we need to ignore the element
  if (element_ignore(element, hittingElement)) return element;
  
  //if the elements are not on the same element, ignore
  if (element.y != hittingElement.y) return element;
  
  element.state = newState;
  return element;
}

void level_element_handle()
{
  level_elements_sort_xy();

  for (char i=0; i < element_count; i++)
  {
    //if the element is hidden, skip past it
    if (levelElements[i].state > STATE_HIDDEN)
    {   
      //if the element was not the first element in the list,
      //compare the current element to the previous element
      //to see if there was a collision or if it is to the left/right
      //of the previous element
      if (i > 0) {
        switch (level_test_element(levelElements[i-1], levelElements[i].x, levelElements[i].y)) {
          case TEST_NO_COLLISION:
             break;

          case TEST_ELEMENT_LEFT:
             levelElements[i-1] = element_spotted(levelElements[i-1], levelElements[i], STATE_MOVE_LEFT);
             break;
            
          case TEST_ELEMENT_RIGHT:
             levelElements[i-1] = element_spotted(levelElements[i-1], levelElements[i], STATE_MOVE_RIGHT);
             break;

          case TEST_COLLISION:
             levelElements[i-1] = element_hit(levelElements[i-1], levelElements[i]);
             break;
        }

      }
      
       switch(levelElements[i].type) {
         case TYPE_EGG:
            levelElements[i] = egg_move(levelElements[i]);
            break;

         case TYPE_TROOPER:
            levelElements[i] = trooper_move(levelElements[i]);
            break;
            
         case TYPE_AILEN:
            levelElements[i] = ailen_move(levelElements[i]);
            break;

         case TYPE_AILEN_WALKER:
            levelElements[i] = ailen_walker_move(levelElements[i]);
            break;

         case TYPE_WALKER:
            levelElements[i] = walker_move(levelElements[i]);
            break;            
            
         default:
            break;
       }
    }
  }
}


#endif
