#ifndef LEVELS_H
#define LEVELS_H

#include "globals.h"

#define LEVEL_WIDTH 16
#define LEVEL_HEIGHT 7
#define LEVEL_SIZE 112

char level_current = 0;

const unsigned char PROGMEM level_data[] = {
//level 0
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,2,3,5,1,0,0,0,0,0,0,0,0,0,0,0,
0,2,4,3,1,0,0,0,2,3,4,3,1,0,0,0,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
};

unsigned char level_get_block(char level_x, char level_y)
{
   return pgm_read_byte_near (level_data + (level_current * LEVEL_SIZE) + level_x + (level_y * LEVEL_WIDTH));
}

void level_draw()
{  
   for (char x=0; x < LEVEL_WIDTH; x++)
   {
      for (char y=0; y < LEVEL_HEIGHT; y++)
      {
          char current_block = level_get_block(x, y);
          if (current_block > 0) sprites.drawSelfMasked(x * 8, y * 8, level_img, current_block-1);
      }
   }
}

//compare the given x,y coordinate against the level data
char level_check_move(char x, char y)
{
   char level_x = x / 8;
   char level_y = y / 8;
   if ((level_x > 15) || (level_y > 7)) return 0;
   return level_get_block(level_x, level_y);
}


char level_check_move_h(char x, char y, char &tile_y)
{
   char tile_x_pixels = (x - (x % 8));   //calculate the x position in pixels we are checking against
   char testend = x + 8; //calculate the end of testing
   tile_y = y >> 3; //calculate the y position (map coordinates) of the tiles we want to test   
   char tile_x = tile_x_pixels >> 3; //calculate map x coordinate for first tile
 
    //loop while the start point of the test tile is inside the bounding box
    while(tile_x_pixels <= testend){
       if(level_get_block(tile_x, tile_y) > 0)  //is a solid tile is found at tile_x, tile_y?
      return 1; 
      
       tile_x++;    //increase tile x map coordinate
       tile_x_pixels +=8; //increase tile x pixel coordinate
  }

  return 0;
}

char level_check_move_v(char x, char y, char &tile_x)
{
   char tile_y_pixels = (y - (y % 8));  //calculate the x position in pixels we are checking against
   char testend = y + 8; //calculate the end of testing
   tile_x = x >> 3; //calculate the y position (map coordinates) of the tiles we want to test   
   char tile_y = tile_y_pixels >> 3; //calculate map x coordinate for first tile
 
    //loop while the start point of the test tile is inside the bounding box
    while(tile_y_pixels <= testend){
       if(level_get_block(tile_x, tile_y) > 0)  //is a solid tile is found at tile_x, tile_y?
      return 1; 
      
       tile_y++;    //increase tile x map coordinate
       tile_y_pixels +=8; //increase tile x pixel coordinate
  }

  return 0;
}

#endif
