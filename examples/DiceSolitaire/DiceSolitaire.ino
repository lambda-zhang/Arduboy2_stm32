/*
This file is part of DiceSolitaire.

DiceSolitaire is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DiceSolitaire is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with DiceSolitaire.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "Hand.hpp"
#include "Board.hpp"

#include <Arduboy2.h>
#include <Sprites.h>
#include <string.h>
#include "title.h"
#include "youwin.h"

Arduboy2 arduboy;
Hand hand;
Board board;

/* Maybe list
 * - Options to choose the number of dice sets?
 * - Fixed puzzles that have known solutions?
 * - Consider allowing placement on top of collapsed sets. It seems a
 *   good challenge without this, though.
 * - Don't allow anything but 6 to be placed on blank space. Or is this too hard?
 */

bool menu = true;

void setup() {
  arduboy.begin();

  //~ arduboy.setFrameRate(15);
}

void do_menu()
{
    Sprites::drawOverwrite(0, 0, title, 0);
    arduboy.pollButtons();

    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
    {
        menu = false;
        board.shuffle(arduboy.generateRandomSeed());
    }
}

void user_action()
{
    arduboy.pollButtons();
    
    if (arduboy.justPressed(UP_BUTTON)) hand.up();
    if (arduboy.justPressed(DOWN_BUTTON)) hand.down();
    if (arduboy.justPressed(LEFT_BUTTON)) hand.left();
    if (arduboy.justPressed(RIGHT_BUTTON)) hand.right();

    if (arduboy.justPressed(A_BUTTON))
    {
        // Grab can also result in a menu option getting triggered
        switch (hand.grab(board))
        {
            case RESTART_BOARD:
                board.restart();
                hand.reset_pos();
                break;
            case NEW_BOARD:
                board.shuffle(arduboy.generateRandomSeed());
                hand.reset_pos();
                break;
            case RETURN_TO_MENU:
                menu = true;
                hand.reset_pos();
                break;
        }
    }
    if (arduboy.justPressed(B_BUTTON)) hand.put_back(board);
}


void draw_display()
{
    arduboy.clear();
    board.draw();
    hand.draw();

    // Won indicator will be drawn last when present
    if (board.is_won())
    {
        Sprites::drawPlusMask(16, 16, youwin, 0);
    }
}

/* Also reminder: F() macro is to convert string constant from flash */
void loop() {
    if (!(arduboy.nextFrame()))
        return;

    if (menu)
    {
        do_menu();
    }
    else
    {
        user_action();
        // User action can result in going to menu
        if (!menu)
        {
            hand.gravity(board);
            board.check_matches();
            draw_display();
        }
    }
    arduboy.display();
}
