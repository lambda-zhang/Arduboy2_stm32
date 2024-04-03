#pragma once
#include "Dice.hpp"
#include "Board.hpp"

#include "cursor.h"
#include "menuitems.h"
#include "limits.h"

#include <Sprites.h>

/* Enum for tracking the result of menu operations that can result from
 * in-game selection. */
enum MenuAction
{
    NO_ACTION,
    RESTART_BOARD,
    NEW_BOARD,
    RETURN_TO_MENU
};


class Hand
{
protected:
    int x = 0, y = 0;
    int grab_x = 0, grab_y = 0;
    bool empty = true;
    Dice holding[NUMCOL] = {EMPTY};
    
public:
    Hand() {}

    void reset_pos()
    {
        // This is expected to happen when selecting a menu option, so
        // the hand should already be empty at that point
        x = 0;
        y = 0;
    }
    
    void draw()
    {
        if (empty)
        {
            // "Empty" cursor is also allowed to move to the menu options.
            // In that case, the normal cursor is not drawn
            if (y < NUMROW)
            {
                Sprites::drawPlusMask(x * 12, y * 12, cursor, 0);
            }
        }
        else
        {
            Dice value;
            for (int pos = 0; pos < NUMCOL; pos++)
            {
                value = holding[pos];
                if (value >= WHITE_1 && value <= WHITE_6)
                    Sprites::drawOverwrite((x + pos) * 12 + 4, y * 12, 
                            whitedice, value - WHITE_1);
                else if (value >= BLACK_1 && value <= BLACK_6)
                    Sprites::drawOverwrite((x + pos) * 12 + 4, y * 12, 
                            blackdice, value - BLACK_1);
            }
            Sprites::drawPlusMask(x * 12 + 4, y * 12, cursor, 0);
        }

        // The hand routine also draws the menu at the bottom, since it tracks
        // that selection too
        for (int item = 0; item < NUMMENU; item++)
        {
            if (y == NUMROW && x == item)
            {
                // Selected items are drawn higher up (overlapping the board)
                Sprites::drawPlusMask(item * 40, 56, menuitems, item);
            }
            else
            {
                Sprites::drawPlusMask(item * 40, 60, menuitems, item);
            }

        }
    }
    
    void up()
    {
        y--;
        if (y < MINROW) y = MINROW;
    }
    
    void down()
    {
        y++;
        if (empty)
        {
            // Empty cursor can move to the menu row
            if (y > NUMROW) y = NUMROW;
        }
        else
        {
            if (y > NUMROW - 1) y = NUMROW - 1;
        }
    }
    
    void left()
    {
        x--;
        if (x < MINCOL) x = MINCOL;
    }
    
    void right()
    {
        x++;
        if (x > NUMCOL - 1) x = NUMCOL - 1;
    }
    
    MenuAction grab(Board & board)
    {
        MenuAction result = NO_ACTION;
        if (empty)
        {
            // "Empty Grab" also can trigger when selecting a bottom menu
            // option
            if (y == NUMROW)
            {
                switch (x)
                {
                    case 0:
                        result = RESTART_BOARD;
                        break;
                    case 1:
                        result = NEW_BOARD;
                        break;
                    case 2:
                        result = RETURN_TO_MENU;
                        break;
                }
            }
            else
            {
                board.grab(x, y, holding);
                if (holding[0] != EMPTY)
                {
                    grab_x = x;
                    grab_y = y;
                    empty = false;
                }
            }
        }
        else
        {
            if (board.place(x, y, holding))
            {
                empty = true;
                grab_x = 0;
                grab_y = 0;
            }
        }
        return result;
    }
    
    void put_back(Board & board)
    {
        /* We can only put back if we are holding anything */
        if (!empty)
        {
            board.put_back(grab_x, grab_y, holding);
            empty = true;
            grab_x = 0;
            grab_y = 0;
        }
    }
    
    /** Restricts the cursor position based on board conents so we don't
     * need to cursor in and out of blank spaces */
#ifndef STM32F103xB
    void gravity(const Board & board)
#else
    void gravity(Board & board)
#endif /* STM32F103xB */
    {
        if (empty)
        {
            if (y < NUMROW)
            {
                x = board.gravity_grab(x, y);
            }
            else
            {
                // Limit menu options explicitly, since they don't change
                if (x > NUMMENU - 1) x = NUMMENU - 1;
            }
        }
        else
        {
            x = board.gravity_place(x, y);
        }
    }
};
