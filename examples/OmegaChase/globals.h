#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "Sprites.h"
#include "Sounds.h"

//  Omega Chase
//  Version 1.0, May 22, 2023 
//  Copyright (c) 2023
//  By Karl P. Williams

// array to hold the x and y values for moving objects in 16 direction vectors (0 to 15).
// signed short dir_vec[16][2] = 
// {{0,-1},{1,-3},{+1,-1},{3,-1},{1,0},{3,1},{1,1},{1,3},
// {0,1},{-1,3},{-1,1},{-3,1},{-1,0},{-3,-1},{-1,-1},{-1,-3}};

// array to hold the x and y values for moving objects in 16 direction vectors (0 to 15). 
// Adjusted to make vertical and hoizontal moves faster (positions 0, 4, 8 and 12)
// Also made 45 degree angles moves faster (positions 2, 6, 10 and 14)
signed short dir_vec[16][2] = 
{{0,-3},{1,-3},{+3,-3},{3,-1},{3,0},{3,1},{3,3},{1,3},
{0,3},{-1,3},{-3,3},{-3,1},{-3,0},{-3,-1},{-3,-3},{-1,-3}};

enum GameState {options, in_game, game_over, level_complete, about};
int menu = 0;
uint8_t sound_state = 0;
int score = 0;
int digit = 0;
int dis_score = 0;
int digit_pos = 0;
uint8_t accuracy = 7; // higher number = easier hit
unsigned long clock = 0;
unsigned long current_millis = 0;
unsigned long previous_millis = 0;
unsigned long previous_millis_cmd = 0;
unsigned long previous_millis_accel = 0;
unsigned long previous_millis_death = 0;
unsigned long previous_millis_rl = 0;
unsigned long previous_millis_rr = 0;
uint8_t cycles = 0;
uint8_t lives = 3;
int level = 1;
int pos_x = 10; // players ship x position
int pos_y = 2;  // players ship y position
int thrust_flame = 0;
int drift = 0;
int drift_dir = 8;
int ship_dir = 8;
int shot_num = 0;
uint8_t ship_active = 1;
uint8_t extra_ships_flag = 0;
float accel = 2;
const uint8_t max_shots = 6;
uint8_t mis_vec_x[6] = {0,0,0,0,0,0};
uint8_t mis_vec_y[6] = {0,0,0,0,0,0};
uint8_t mis_pos_x[6] = {0,0,0,0,0,0};
uint8_t mis_pos_y[6] = {0,0,0,0,0,0};
uint8_t mis_avail[6] = {1,1,1,1,1,1};
signed short thrust_x = 0;
signed short thrust_y = 0;
signed short drift_x = 0;
signed short drift_y = 0;
int ani = 0;
uint16_t droid_interval = 500;
uint8_t num_droids = 5;
uint8_t droid_dir[6] = {4,4,4,4,4,4};
uint8_t droid_x[6] = {30,30,30,30,30,30};
uint8_t droid_y[6] = {42,42,42,42,42,42};
uint8_t droid_vec_x[6] = {0,0,0,0,0,0};
uint8_t droid_vec_y[6] = {0,0,0,0,0,0};
uint8_t droid_active[6] = {1,1,1,1,1,1};
uint8_t num_kills = 0;
uint8_t cmd_ship_interval = 75;
uint8_t num_cmd_ships = 0;
uint8_t cmd_ship_dir[2] = {4,4};
uint8_t cmd_ship_x[2] = {30,30};
uint8_t cmd_ship_y[2] = {42,42};
uint8_t cmd_vec_x[2] = {0,0};
uint8_t cmd_vec_y[2] = {0,0};
uint8_t cmd_ship_active[2] = {0,0};
uint8_t num_death_ships = 0;
uint8_t death_ship_interval = 100;
uint8_t death_ship_dir[2] = {6,6};
uint8_t death_ship_x[2] = {64,64};
uint8_t death_ship_y[2] = {45,45};
uint8_t death_vec_x[2] = {0,0};
uint8_t death_vec_y[2] = {0,0};
uint8_t death_ship_active[2] = {0,0};
int enemy_mis_dir = 0;
const uint8_t enemy_max_shots = 6;
uint8_t enemy_mis_vec_x[6] = {0,0,0,0,0,0};
uint8_t enemy_mis_vec_y[6] = {0,0,0,0,0,0};
uint8_t enemy_mis_pos_x[6] = {0,0,0,0,0,0};
uint8_t enemy_mis_pos_y[6] = {0,0,0,0,0,0};
uint8_t enemy_mis_avail[6] = {1,1,1,1,1,1};
int Dx = 0;
int Dy = 0;
double angle = 0;
double angle_degrees = 0;
uint8_t mine_pos_x[6] = {0,0,0,0,0,0};
uint8_t mine_pos_y[6] = {0,0,0,0,0,0};
uint8_t mine_active[6] = {0,0,0,0,0,0};
uint8_t mine_type[6] = {0,0,0,0,0,0};
uint8_t num_mines = 6;
uint8_t mine_count = 0;
int object_x = 0;
int object_y = 0;
int object_dir = 0;

#endif