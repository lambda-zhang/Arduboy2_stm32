/*
  DUNGEONS: http://www.team-arg.org/dun-manual.html

  Arduboy version 0.1:  http://www.team-arg.org/dun-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2013 - Original for Gamby Shield : Trodoss - JO3RI

  2017 - Arduboy version : JO3RI - PIQUESEL

  License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 10

#include "globals.h"

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.clear();
  sprites.drawSelfMasked(34, 4, TeamArgLogo, 0);
  arduboy.display();
}
