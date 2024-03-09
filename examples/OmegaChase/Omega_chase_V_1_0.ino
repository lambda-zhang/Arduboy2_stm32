//  Omega Chase
//  Version 1.0, May 22, 2023 
//  Copyright (c) 2023
//  By Karl P. Williams
//  Website: http://www.thinkbotics.com
//  Email: karlw@thinkbotics.com
//
// MIT License
//
// Copyright (c) 2023 Karl P. Williams
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation 
// files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, 
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software 
// is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
// IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE

#include "globals.h"
#include <math.h>

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
GameState gameState = options;

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(60);

  arduboy.audio.on();
 
  // Random start positions of enemy droids
  for (int i = 0; i < num_droids; i++){
    arduboy.initRandomSeed();
    droid_x[i] = 30 + random(70);
    droid_y[i] = 42 + random(15);
  }

  num_cmd_ships = 0;
  num_death_ships = 0;
  mine_count = 0;
}

void loop() {
  if (!(arduboy.nextFrame()))
		return;
  arduboy.clear();

  if (gameState == options){
    arduboy.drawSlowXYBitmap(0,11,title_screen1,128,42,1);
    arduboy.display();
    delay(2000);
    arduboy.clear();
    for (int i = 11; i > 0; i--){
      arduboy.clear();
      arduboy.drawSlowXYBitmap(0,i,title_screen1,128,42,1);
      arduboy.display();
    }
    menu = 0;
    while (menu < 3){
      arduboy.pollButtons();
      if (arduboy.anyPressed(DOWN_BUTTON)){
        menu = menu + 1;
        if (menu == 3){menu = 0;}
      }
      if (arduboy.anyPressed(UP_BUTTON)){
        menu = menu - 1;
        if (menu < 0){menu = 2;}
      }
      if (menu == 0){
        arduboy.setTextColor(BLACK);
        arduboy.setTextBackground(WHITE);
        printText("Start Game",48,36,1);
        arduboy.setTextColor(WHITE);
        arduboy.setTextBackground(BLACK);
        if (sound_state == 1){
          printText("Sound Off",48,46,1); 
        }
        else{
          printText("Sound On ",48,46,1); 
        }
        arduboy.setTextColor(WHITE);
        arduboy.setTextBackground(BLACK);
        printText("About",48,56,1);
        arduboy.display();
        arduboy.pollButtons();
        if (arduboy.anyPressed(A_BUTTON) || arduboy.anyPressed(B_BUTTON)){
          gameState = in_game;
          menu = 4;  //escape the menu loop
        }
      }
      if (menu == 1){
        arduboy.setTextColor(WHITE);
        arduboy.setTextBackground(BLACK);
        printText("Start Game",48,36,1);
        arduboy.setTextColor(BLACK);
        arduboy.setTextBackground(WHITE);
        if (sound_state == 1){
          printText("Sound Off",48,46,1); 
        }
        else{
          printText("Sound On ",48,46,1); 
        }
        arduboy.setTextColor(WHITE);
        arduboy.setTextBackground(BLACK);
        printText("About",48,56,1);
        arduboy.display();
        arduboy.pollButtons();
        if (arduboy.anyPressed(A_BUTTON) || arduboy.anyPressed(B_BUTTON)){
          sound_state++;
          if (sound_state > 1){sound_state = 0;}
          if (sound_state == 0){arduboy.audio.on();}
          else {arduboy.audio.off();}
            delay(120);
        }
      }
      if (menu == 2){
        arduboy.setTextColor(WHITE);
        arduboy.setTextBackground(BLACK);
        printText("Start Game",48,36,1);
        arduboy.setTextColor(WHITE);
        arduboy.setTextBackground(BLACK);
        if (sound_state == 1){
          printText("Sound Off",48,46,1); 
        }
        else{
          printText("Sound On ",48,46,1); 
        }
        arduboy.setTextColor(BLACK);
        arduboy.setTextBackground(WHITE);
        printText("About",48,56,1);
        arduboy.display();
        arduboy.pollButtons();
        if (arduboy.anyPressed(A_BUTTON) || arduboy.anyPressed(B_BUTTON)){
          gameState = about;
          menu = 4; //escape the menu loop
        }
      }
    delay(120);
    }
  }
	if (gameState == game_over){
    sound.tones(song_2);
    score_area();
    arduboy.drawSlowXYBitmap(5,4,game_over_img,120,15,1);
    arduboy.display();
    delay(8500);
    lives = 3;
    extra_ships_flag = 0;
    score = 0;
    level = 1;
    level_reset();
    gameState = options;
  }

  if (gameState == about){
    arduboy.clear();
    arduboy.drawSlowXYBitmap(0,0,points_screen,128,64,1);
    arduboy.display();
    delay(400);
    while (!arduboy.anyPressed(A_BUTTON) && !arduboy.anyPressed(B_BUTTON)){
      arduboy.pollButtons();
    }
    arduboy.clear();
    arduboy.drawSlowXYBitmap(0,0,controls_screen,128,64,1);
    arduboy.display();
    delay(400);
    while (!arduboy.anyPressed(A_BUTTON) && !arduboy.anyPressed(B_BUTTON)){
      arduboy.pollButtons();
    }
    arduboy.clear();
    arduboy.drawSlowXYBitmap(0,0,title_screen1,128,42,1);
    for (int i = 13; i > -9; i--){
      arduboy.clear();
      arduboy.drawSlowXYBitmap(0,i,title_screen1,128,42,1);
      arduboy.display();
    }
    arduboy.setTextColor(WHITE);
    arduboy.setTextBackground(BLACK);
    printText("Copyright (c) 2023",7,34,1);
    printText(" Karl P. Williams",7,44,1);
    printText("www.thinkbotics.com",7,54,1);
    arduboy.display();
    delay(400);
    while (!arduboy.anyPressed(A_BUTTON) && !arduboy.anyPressed(B_BUTTON)){
      arduboy.pollButtons();
    }
      gameState = options;
  }

  if (gameState == level_complete){
    sound.tones(song_1);
    delay(8500);
    level_reset();
    level = level + 1;
    clock = 0;
    gameState = in_game;
  }

  if (gameState == in_game){

    cycles++;
    clock++;
    ani++;
    current_millis = millis();

    if (accel > 0){
      accel = accel - 0.4;
    }
    if (accel < 0){
      accel = 0;
    }

    // Postion command ships so they are always at the opposite screen positon to the space ship.
    if (clock == 250 && level < 4){
        num_cmd_ships = 1;
        cmd_ship_active[0] = 1;
        cmd_ship_active[1] = 0;
        cmd_ship_x[0] = 120 - pos_x;
        cmd_ship_y[0] = 56 - pos_y;
        cmd_ship_dir[0] = cmd_ship_direction(cmd_ship_x[0], cmd_ship_y[0], cmd_ship_dir[0]);
    }
    if (clock == 260 && level >= 4){
        num_cmd_ships = 1;
        cmd_ship_active[0] = 1;
        cmd_ship_active[1] = 0;
        cmd_ship_x[0] = 120 - pos_x;
        cmd_ship_y[0] = 56 - pos_y;
        cmd_ship_dir[0] = cmd_ship_direction(cmd_ship_x[0], cmd_ship_y[0], cmd_ship_dir[0]);
      }
     if (clock == 300 && level >= 4){
        num_cmd_ships = 2;
        cmd_ship_active[0] = 1;
        cmd_ship_active[1] = 1;
        cmd_ship_x[1] = 120 - pos_x;
        cmd_ship_y[1] = 56 - pos_y;
        cmd_ship_dir[1] = cmd_ship_direction(cmd_ship_x[1], cmd_ship_y[1], cmd_ship_dir[1]);
      }

    // Launch the mine laying death ships
    // Make start position on the opposite y-axis side of arena to the active space ship
    if (clock == 350){
      for (int i = 0; i < 2; i++){
      arduboy.initRandomSeed();
      death_ship_x[i] = 64;
      if (pos_y <= 32){
        death_ship_y[i] = 45;
      }
      else{
        death_ship_y[i] = 2;
      }
      death_ship_dir[i] = random(3) + 5;
    }
      if (level < 3){
        num_death_ships = 1;
        death_ship_active[0] = 1;
        death_ship_active[1] = 0;
      }
      else{
        num_death_ships = 2;
        death_ship_active[0] = 1;
        death_ship_active[1] = 1;
      }
    }
    
    // Play heartbeat sounds
    if (cycles == 15){ 
      sound.tone(392,30); // G4
    }
    if (cycles == 30){ 
      sound.tone(415.30,30); // G#4
    }
    if (cycles == 45){ 
      sound.tone(392,30); // G4
    }
    if (cycles == 60){ 
      sound.tone(329.63,30); // E4
      cycles = 0;
    }

    arduboy.pollButtons();

    score_area();

    // Rotate ship left. The ship has 16 possible directions.
    // Slowed down rotation to make it controllable
    if (current_millis - previous_millis_rl >= 50){
      previous_millis_rl = current_millis;
      if (arduboy.anyPressed(LEFT_BUTTON)) {
        ship_dir = ship_dir - 1;
        if (ship_dir < 0) {
          ship_dir = 15;
        }
      }
    }

    // Rotate ship right
    if (current_millis - previous_millis_rr >= 50){
      previous_millis_rr = current_millis;
      if (arduboy.anyPressed(RIGHT_BUTTON)) {
        ship_dir = ship_dir + 1;
        if (ship_dir > 15) {
          ship_dir = 0;
        }
      }
    }

    // Thrust button
    if (arduboy.anyPressed(UP_BUTTON)) {
      thrust_x = dir_vec[ship_dir][0];
      thrust_y = dir_vec[ship_dir][1];
      accel = accel + 7;
      if (accel > 150){
        accel = 150;
      }
      drift = 650;        
      drift_dir = ship_dir;     // bounce in direction of drift. Ship orientation can change while drifting.
      thrust_flame = 16;
      sound.tones(thrustNoise);
    }

    // Reverse thrust button
    if (arduboy.anyPressed(DOWN_BUTTON) and drift > 0) {
      accel = accel - 7;
      if (accel < 0 ){accel = 0;}        
      drift = drift - 5;
      if (drift < 0 ){drift = 0;}
      sound.tones(thrustNoise);
    }
  
    drift = drift - 1;
    if (drift < 0 ){drift = 0;}
    if (accel < 0 ){accel = 0;} 

    // Fire buttons: button A is single shot, button B is full auto. 0 = missile in play, 1 = missile available.
    if (arduboy.justPressed(A_BUTTON) or arduboy.anyPressed(B_BUTTON)){ 
      delay(40);
      for (int i = 0; i < max_shots; i++){
        if(mis_avail[i] == 1){
          mis_pos_x[i] = pos_x + 4;
          mis_pos_y[i] = pos_y + 4;
          mis_vec_x[i] = dir_vec[ship_dir][0];
          mis_vec_y[i] = dir_vec[ship_dir][1];
          mis_avail[i] = 0;
          sound.tones(fire);
          break;  
        }
      }
    }

    // Command ships fire missiles at the players ship
    // Figure out direction vector for missile, pointing from command ships to the players ship
    for (int k = 0; k < 2; k++){
      if (cmd_ship_active[k] == 1){
        Dx = cmd_ship_x[k] - pos_x;
        Dy = cmd_ship_y[k] - pos_y;
        angle = atan2(Dx, Dy);
        angle_degrees = fmod(angle * -180 / M_PI + 360, 360);
        enemy_mis_dir = round(angle_degrees / 22.5);          // Map the angle to the range of 0 to 15 for direction vector array
        arduboy.initRandomSeed();
        if (random(35 - level) == 1){                         // Fire randomly to give the player a chance
          for (int i = 0; i < enemy_max_shots; i++){
            if(enemy_mis_avail[i] == 1){
              enemy_mis_pos_x[i] = cmd_ship_x[k] + 4;
              enemy_mis_pos_y[i] = cmd_ship_y[k] + 4;
              enemy_mis_vec_x[i] = dir_vec[enemy_mis_dir][0];
              enemy_mis_vec_y[i] = dir_vec[enemy_mis_dir][1];
              enemy_mis_avail[i] = 0;
              sound.tones(fire);
              break;  
            }
          }
        }
      }
    }

    // Check for spaceship wall hits and determine bounce angle
    drift_dir = boundaries(pos_x, pos_y, drift_dir);

    // Move spaceship after thrust
    if (current_millis - previous_millis_accel >= (150 - accel)){
      previous_millis_accel = current_millis;
      thrust_x = dir_vec[drift_dir][0];
      thrust_y = dir_vec[drift_dir][1]; 
      if (drift > 0) {
        pos_x = pos_x + thrust_x;
        pos_y = pos_y + thrust_y;
        drift = drift - 1;
        accel = accel - 1;
      }
    }

    // Check spaceship collision with a droid
    for (int k = 0; k < num_droids; k++){
      if ((pos_x >= (droid_x[k] - accuracy) && pos_x <= (droid_x[k] + accuracy)) 
        && (pos_y >= (droid_y[k] - accuracy) && pos_y <= (droid_y[k] + accuracy))
        && droid_active[k] == 1){ 
        droid_active[k] = 2; // 0 = not active, 1 = active, 2 = display explosion then set to 0
        ship_active = 0;
        num_kills = num_kills + 1;
      } 
    }

    // Check spaceship collision with a command ship
    for (int k = 0; k < num_cmd_ships; k++){
      if ((pos_x >= (cmd_ship_x[k] - accuracy) && pos_x <= (cmd_ship_x[k] + accuracy)) 
        && (pos_y >= (cmd_ship_y[k] - accuracy) && pos_y <= (cmd_ship_y[k] + accuracy))
        && cmd_ship_active[k] == 1){ 
        cmd_ship_active[k] = 2; // 0 = not active, 1 = active, 2 = display explosion then set to 0
        ship_active = 0;
        num_kills = num_kills + 1;
      } 
    }

    // Check spaceship collision with a death ship
    for (int k = 0; k < num_death_ships; k++){
      if ((pos_x >= (death_ship_x[k] - accuracy) && pos_x <= (death_ship_x[k] + accuracy)) 
        && (pos_y >= (death_ship_y[k] - accuracy) && pos_y <= (death_ship_y[k] + accuracy))
        && death_ship_active[k] == 1){ 
        death_ship_active[k] = 2; // 0 = not active, 1 = active, 2 = display explosion then set to 0
        ship_active = 0;
        num_kills = num_kills + 1;
      } 
    }

    // Check spaceship collision with a mine
    for (int k = 0; k < num_mines; k++){
      if ((pos_x >= (mine_pos_x[k] - accuracy) && pos_x <= (mine_pos_x[k] + accuracy)) 
        && (pos_y >= (mine_pos_y[k] - accuracy) && pos_y <= (mine_pos_y[k] + accuracy))
        && mine_active[k] == 1){ 
        mine_active[k] = 2; // 0 = not active, 1 = active, 2 = display explosion then set to 0
        ship_active = 0;
      } 
    }

    // Move missiles fired from spaceship
    for (int j = 0; j < max_shots; j++){
      if (mis_avail[j] == 0 ){
        // Check missile hits on droids
        for (int k = 0; k < num_droids; k++){
          if ((mis_pos_x[j] >= droid_x[k] && mis_pos_x[j] <= (droid_x[k] + accuracy)) 
          && (mis_pos_y[j] >= droid_y[k] && mis_pos_y[j] <= (droid_y[k] + accuracy))
          && droid_active[k] == 1){ 
            droid_active[k] = 2; // 0 = not active, 1 = active, 2 = display explosion then set to 0
            mis_avail[j] = 1;
            mis_pos_x[j] = -1;
            mis_pos_y[j] = -1;
            num_kills = num_kills + 1;
          } 
        }
        // Check missile hits on command ships
        for (int k = 0; k < 2; k++){
          if ((mis_pos_x[j] >= cmd_ship_x[k] && mis_pos_x[j] <= (cmd_ship_x[k] + accuracy)) 
          && (mis_pos_y[j] >= cmd_ship_y[k] && mis_pos_y[j] <= (cmd_ship_y[k] + accuracy))
          && cmd_ship_active[k] == 1){ 
            cmd_ship_active[k] = 2; // 0 = not active, 1 = active, 2 = display explosion then set to 0
            mis_avail[j] = 1;
            mis_pos_x[j] = -1;
            mis_pos_y[j] = -1;
            num_kills = num_kills + 1;
          } 
        }
        // Check missile hits on death ships
        for (int k = 0; k < 2; k++){
          if ((mis_pos_x[j] >= death_ship_x[k] && mis_pos_x[j] <= (death_ship_x[k] + accuracy)) 
          && (mis_pos_y[j] >= death_ship_y[k] && mis_pos_y[j] <= (death_ship_y[k] + accuracy))
          && death_ship_active[k] == 1){ 
            death_ship_active[k] = 2; // 0 = not active, 1 = active, 2 = display explosion then set to 0
            mis_avail[j] = 1;
            mis_pos_x[j] = -1;
            mis_pos_y[j] = -1;
            num_kills = num_kills + 1;
          } 
        }
        // Check missile hits on mines
        for (int k = 0; k < num_mines; k++){
          if ((mis_pos_x[j] >= mine_pos_x[k] && mis_pos_x[j] <= (mine_pos_x[k] + accuracy)) 
          && (mis_pos_y[j] >= mine_pos_y[k] && mis_pos_y[j] <= (mine_pos_y[k] + accuracy))
          && mine_active[k] == 1){ 
            mine_active[k] = 2; // 0 = not active, 1 = active, 2 = display explosion then set to 0
            mis_avail[j] = 1;
            mis_pos_x[j] = -1;
            mis_pos_y[j] = -1;
          } 
        }    
        // Check missile hits on outer walls
        if ((mis_pos_x[j] > 128) || (mis_pos_x[j] < 0) || (mis_pos_y[j] > 64) || (mis_pos_y[j] < 0)){
          mis_avail[j] = 1;
          mis_pos_x[j] = -4;
          mis_pos_y[j] = -4;
        }
        // Check missile hits on score area walls
        if (((mis_pos_x[j] > 32) && (mis_pos_x[j] < 96)) && ((mis_pos_y[j] > 21) && (mis_pos_y[j] < 42))){   
          mis_avail[j] = 1;
          mis_pos_x[j] = -1;
          mis_pos_y[j] = -1;
        }
        // Draw missiles
        mis_pos_x[j] = mis_pos_x[j] + mis_vec_x[j];
        mis_pos_y[j] = mis_pos_y[j] + mis_vec_y[j];
        arduboy.drawPixel(mis_pos_x[j], mis_pos_y[j], WHITE);
      }  
    }

    // Move missiles fired from command ships
    for (int j = 0; j < enemy_max_shots; j++){
      if (enemy_mis_avail[j] == 0 ){
        // Check missile hits on space ship
          if ((enemy_mis_pos_x[j] >= pos_x && enemy_mis_pos_x[j] <= (pos_x + accuracy)) 
          && (enemy_mis_pos_y[j] >= pos_y && enemy_mis_pos_y[j] <= (pos_y + accuracy))
          && ship_active == 1){ 
            ship_active = 2; // 0 = not active, 1 = active, 2 = display explosion then set to 0
            enemy_mis_avail[j] = 1;
            enemy_mis_pos_x[j] = -1;
            enemy_mis_pos_y[j] = -1;
          } 
        // Check enemy missile hits on outer walls
        if ((enemy_mis_pos_x[j] > 128) || (enemy_mis_pos_x[j] < 0) || (enemy_mis_pos_y[j] > 64) || (enemy_mis_pos_y[j] < 0)){
          enemy_mis_avail[j] = 1;
          enemy_mis_pos_x[j] = -4;
          enemy_mis_pos_y[j] = -4;
        }
        // Check enemy missile hits on score area walls
        if (((enemy_mis_pos_x[j] > 32) && (enemy_mis_pos_x[j] < 96)) && ((enemy_mis_pos_y[j] > 21) && (enemy_mis_pos_y[j] < 42))){   
          enemy_mis_avail[j] = 1;
          enemy_mis_pos_x[j] = -1;
          enemy_mis_pos_y[j] = -1;
        }
        // Draw missiles
        enemy_mis_pos_x[j] = enemy_mis_pos_x[j] + enemy_mis_vec_x[j];
        enemy_mis_pos_y[j] = enemy_mis_pos_y[j] + enemy_mis_vec_y[j];
        arduboy.drawPixel(enemy_mis_pos_x[j], enemy_mis_pos_y[j], WHITE);
      }  
    }

    // Draw the spaceship
    if (ship_active == 1){
      Sprites::drawOverwrite(pos_x, pos_y, ship, ship_dir + thrust_flame);
      thrust_flame = 0;
    }
    else{
      explosion_sound();
      if (ani <= 4) {
        Sprites::drawOverwrite(pos_x, pos_y, explosion, 0);
      }
      if (ani > 4) {
        Sprites::drawOverwrite(pos_x, pos_y, explosion, 1);
        lives = lives - 1;
        arduboy.setCursor(20,10);
        arduboy.print("SHIP DESTROYED!");
        arduboy.display();
        delay(2000);
        level_reset();
        ship_active = 1;
      }
    }

    // Draw the droids
    for (int i = 0; i < num_droids; i++){
      if (droid_active[i] == 1){
        if (ani <= 4) {
          Sprites::drawOverwrite(droid_x[i], droid_y[i], droid_ship, 0);
        }
        if (ani > 4) {
          Sprites::drawOverwrite(droid_x[i], droid_y[i], droid_ship, 1);
        }
      }
      if (droid_active[i] == 2){     
        Sprites::drawOverwrite(droid_x[i], droid_y[i], explosion, 0);
        explosion_sound();
        droid_active[i] = 0;
        droid_x[i] = 0;
        droid_y[i] = 0;
        score = score + 10;
        }
    }

    // Draw the command ships
    for (int i = 0; i < num_cmd_ships; i++){
      if (cmd_ship_active[i] == 1){
        if (ani <= 4) {
          Sprites::drawOverwrite(cmd_ship_x[i], cmd_ship_y[i], command_ship, 0);
        }
        if (ani > 4) {
         Sprites::drawOverwrite(cmd_ship_x[i], cmd_ship_y[i], command_ship, 1);
        }
      }
        if (cmd_ship_active[i] == 2){     
          Sprites::drawOverwrite(cmd_ship_x[i], cmd_ship_y[i], explosion, 0);
          explosion_sound();
          cmd_ship_active[i] = 0;
          cmd_ship_x[i] = 0;
          cmd_ship_y[i] = 0;
          score = score + 25;
        }
    }

    // Draw the death ships
    for (int i = 0; i < num_death_ships; i++){
      if (death_ship_active[i] == 1){
        if (ani <= 2) {
           Sprites::drawOverwrite(death_ship_x[i], death_ship_y[i], death_ship, 0);
         }
        if (ani >= 3 && ani <= 5) {
           Sprites::drawOverwrite(death_ship_x[i], death_ship_y[i], death_ship, 1);
         }
         if (ani > 5) {
           Sprites::drawOverwrite(death_ship_x[i], death_ship_y[i], death_ship, 2);
         }
      }
      if (death_ship_active[i] == 2){     
        Sprites::drawOverwrite(death_ship_x[i], death_ship_y[i], explosion, 0);
        explosion_sound();
        death_ship_active[i] = 0;
        death_ship_x[i] = 0;
        death_ship_y[i] = 0;
        score = score + 45;
      }
    }

    if (ani == 9) {
      ani = 0;
    }

    // Move the droids around the course, counter clockwise
    if (current_millis - previous_millis >= droid_interval){
      previous_millis = current_millis;
      for (int i = 0; i < num_droids; i++){
        droid_vec_x[i] = dir_vec[droid_dir[i]][0];
        droid_vec_y[i] = dir_vec[droid_dir[i]][1];
        droid_x[i] = droid_x[i] + droid_vec_x[i];
        droid_y[i] = droid_y[i] + droid_vec_y[i];
        if (droid_dir[i] == 4 and droid_x[i] > (98 + random(24))){  // droid is moving to the right
          droid_dir[i] = 0;
        }
        if (droid_dir[i] == 0 and droid_y[i] < (15 - random(14))){   // droid is moving up
          droid_dir[i] = 12;
        }
        if (droid_dir[i] == 12 and droid_x[i] < (25 - random(24))){   // droid is moving left
          droid_dir[i] = 8;
        }
        if (droid_dir[i] == 8 and droid_y[i] > (41 + random(14))){   // droid is moving down
          droid_dir[i] = 4;
        }
      }
    }

    // Move the command ships around the course, counter clockwise
    if (current_millis - previous_millis_cmd >= cmd_ship_interval){
      previous_millis_cmd = current_millis;
      for (int i = 0; i < num_cmd_ships; i++){
        cmd_vec_x[i] = dir_vec[cmd_ship_dir[i]][0];
        cmd_vec_y[i] = dir_vec[cmd_ship_dir[i]][1];
        cmd_ship_x[i] = cmd_ship_x[i] + cmd_vec_x[i];
        cmd_ship_y[i] = cmd_ship_y[i] + cmd_vec_y[i];
        if (cmd_ship_dir[i] == 4 && cmd_ship_x[i] > (98 + random(24))){  // command ship is moving to the right
          cmd_ship_dir[i] = 0;
        }
        if (cmd_ship_dir[i] == 0 && cmd_ship_y[i] < (15 - random(14))){   // command ship is moving up
          cmd_ship_dir[i] = 12;
        }
        if (cmd_ship_dir[i] == 12 && cmd_ship_x[i] < (25 - random(24))){   // command ship is moving left
          cmd_ship_dir[i] = 8;
        }
        if (cmd_ship_dir[i] == 8 && cmd_ship_y[i] > (41 + random(14))){   // command ship is moving down
          cmd_ship_dir[i] = 4;
        }
      }
    }

    // Move the death ships around the course
    if (current_millis - previous_millis_death >= death_ship_interval){
      previous_millis_death = current_millis;
      for (int i = 0; i < num_death_ships; i++){
        if (death_ship_active[i] == 1){
        death_vec_x[i] = dir_vec[death_ship_dir[i]][0];
        death_vec_y[i] = dir_vec[death_ship_dir[i]][1];
        death_ship_x[i] = death_ship_x[i] + death_vec_x[i];
        death_ship_y[i] = death_ship_y[i] + death_vec_y[i];
        death_ship_dir[i] = boundaries(death_ship_x[i], death_ship_y[i], death_ship_dir[i]);
        }
      }
    }

    // Randomly drop photon and vapor mines from death ships
    for (int i = 0; i < num_death_ships; i++){
      if (death_ship_active[i] == 1 && (mine_count < num_mines)){
        if (random(120) == 1){
          mine_pos_x[mine_count] = death_ship_x[i];
          mine_pos_y[mine_count] = death_ship_y[i];
          mine_type[mine_count] = random(2);
          mine_active[mine_count] = 1;
          mine_count = mine_count + 1;
        }
      }
    }

    // Draw the mines
    for (int i = 0; i < num_mines; i++){
      if (mine_active[i] == 1){
        Sprites::drawOverwrite(mine_pos_x[i], mine_pos_y[i], mines, mine_type[i]);
      }
      if (mine_active[i] == 2){
        Sprites::drawOverwrite(mine_pos_x[i], mine_pos_y[i], explosion, 0);
        mine_active[i] = 0;
        score = score + 5;
      }
    }

    delay(20); // Adjust this value once all the routines are finished. 20 for real Arduboy and arduboy_sim. 60 for Project Abe.

    arduboy.display();

    if (score >= 500 && extra_ships_flag == 0){
      lives = lives + 1;
      extra_ships_flag = 1;
    }

    if (score >= 1000 && extra_ships_flag == 1){
      lives = lives + 1;
      extra_ships_flag = 2;
    }

    if (lives == 0){
      gameState = game_over;
    }

    if (num_kills == num_droids + num_cmd_ships + num_death_ships){
      gameState = level_complete;
    }
  }    
 }

// --------------- Functions ---------------

// Display messages
void printText(const char *message, byte x, byte y, byte textSize) {
  arduboy.setCursor(x,y);
  arduboy.setTextSize(textSize);
  arduboy.print(message);
}

// Screen boundaries and wall bounce angles based on incoming vectors
int boundaries(int object_x, int object_y, int object_dir){
  // object is moving up and to the right
  if ((object_y < 3) && (object_dir <= 3) or
    ((object_y > 40) && (object_y < 44)) && ((object_x > 24) && (object_x < 96)) && (object_dir <= 3)){
    switch (object_dir){
      case 0:
        object_dir = 8;
        break;
      case 1:
        object_dir = 7;
        break;
      case 2:
        object_dir = 6;
        break;
      case 3:
        object_dir = 5;
        break;
    }
    border_lines_y1(object_x, object_y);
    sound.tones(wallBounce);
    return object_dir;
  }
  // object is moving up and to the left
  if ((object_y < 3) && (object_dir > 12) or
    ((object_y > 40) && (object_y < 44)) && ((object_x > 24) && (object_x < 96)) && (object_dir > 12)){
    switch (object_dir){
      case 13:
        object_dir = 11;
        break;
      case 14:
        object_dir = 10;
        break;
      case 15:
        object_dir = 9;
        break;
    }
    border_lines_y1(object_x, object_y);
    sound.tones(wallBounce);
    return object_dir;
  }
  // object is moving down and to the right
  if ((object_y > 54) && (object_dir <= 8) or
    ((object_y > 12) && (object_y < 18)) && ((object_x > 24) && (object_x < 96)) && (object_dir <= 8)){
    switch (object_dir){
      case 5:
        object_dir = 3;
        break;
      case 6:
        object_dir = 2;
        break;
      case 7:
        object_dir = 1;
        break;
      case 8:
        object_dir = 0;
        break;
    }
    border_lines_y2(object_x, object_y);
    sound.tones(wallBounce);
    return object_dir;
  }
  // object is moving down and to the left
  if ((object_y > 52) && (object_dir > 8) or
    ((object_y > 12) && (object_y < 18)) && ((object_x > 24) && (object_x < 96)) && (object_dir > 8)){
    switch (object_dir){
      case 9:
        object_dir = 15;
        break;
      case 10:
        object_dir = 14;
        break;
      case 11:
        object_dir = 13;
        break;
    }
    border_lines_y2(object_x, object_y);
    sound.tones(wallBounce);
    return object_dir;
  }
  // object is moving to the right and up
  if ((object_x > 119) && (object_dir <= 4) or
    ((object_x > 22) && (object_x < 27)) && ((object_y > 13) && (object_y < 42)) && (object_dir <= 4)){
    switch (object_dir){
      case 1:
        object_dir = 15;
        break;
      case 2:
        object_dir = 14;
        break;
      case 3:
        object_dir = 13;
        break;
      case 4:
        object_dir = 12;
        break;
    }
    border_lines_x2(object_x, object_y);
    sound.tones(wallBounce);
    return object_dir;
  }
  // object is moving to the right and down
  if ((object_x > 119) && (object_dir > 4) or
    ((object_x > 22) && (object_x < 27)) && ((object_y > 13) && (object_y < 42)) && (object_dir > 4)){
    switch (object_dir){
      case 5:
        object_dir = 11;
        break;
      case 6:
        object_dir = 10;
        break;
      case 7:
        object_dir = 9;
        break;
    }
    border_lines_x2(object_x, object_y);
    sound.tones(wallBounce);
    return object_dir;
  }
  // object is moving to the left and down
  if ((object_x < 3) && (object_dir <= 12) or
    ((object_x > 94) && (object_x < 98)) && ((object_y > 13) && (object_y < 42)) && (object_dir <= 12)){
    switch (object_dir){
      case 9:
        object_dir = 7;
        break;
      case 10:
        object_dir = 6;
        break;
      case 11:
        object_dir = 5;
        break;
      case 12:
        object_dir = 4;
        break;
    }
    border_lines_x1(object_x, object_y);
    sound.tones(wallBounce);
    return object_dir;
  }
  // object is moving to the left and up
  if ((object_x < 3) && (object_dir > 12) or
    ((object_x > 94) && (object_x < 98)) && ((object_y > 13) && (object_y < 42)) && (object_dir > 12)){
    switch (object_dir){
      case 13:
        object_dir = 3;
        break;
      case 14:
        object_dir = 2;
        break;
      case 15:
        object_dir = 1;
        break;
    }
    border_lines_x1(object_x, object_y);
    sound.tones(wallBounce);
    return object_dir;
  }
return object_dir;
}

// Draw the border lines when the ship hits the invisible walls
void border_lines_y1(int object_x, int object_y){
  if (object_y < 3 && object_x >= 64){
    arduboy.drawFastHLine(64, 0, 64, WHITE);
  }
  else if (object_y < 3 ){
    arduboy.drawFastHLine(0, 0, 64, WHITE);
    }
return;
}

void border_lines_y2(int object_x, int object_y){
  if (object_y > 54 && object_x >= 64){
    arduboy.drawFastHLine(64, 62, 64, WHITE);
  }
  else if (object_y > 52){
    arduboy.drawFastHLine(0, 62, 64, WHITE); 
  }
return; 
}

void border_lines_x1(int object_x, int object_y){
  if (object_x < 3 && object_y >= 32){
    arduboy.drawFastVLine(0, 32, 32, WHITE);
  }
  else if (object_x < 3){
    arduboy.drawFastVLine(0, 0, 32, WHITE);
    }
return;
}

void border_lines_x2(int object_x, int object_y){
  if (object_x > 119 && object_y >= 32){
    arduboy.drawFastVLine(127, 32, 32, WHITE);
  }
  else if (object_x > 119){
    arduboy.drawFastVLine(127, 0, 32, WHITE);
    }
return;
}

void explosion_sound(){
  for (int i = 0; i < 5; i++) {
    sound.tone(500 + random(1000), 50);
    delay(30);
  }
}

int cmd_ship_direction(int cmd_x, int cmd_y, int cmd_dir){
 if ((cmd_x >= 97 && cmd_x < 128) && (cmd_y >= 14 && cmd_y < 64)){
          cmd_dir = 0;
        }
        if ((cmd_x >= 1 && cmd_x < 104) && (cmd_y >= 43 && cmd_y < 64)){
          cmd_dir = 4;
        }
        if ((cmd_x >= 1 && cmd_x <= 24) && (cmd_y >= 1 && cmd_y <= 50)){
          cmd_dir = 8;
        }
        if ((cmd_x >= 24 && cmd_x <= 128) && (cmd_y >= 1 && cmd_y <= 14)){
          cmd_dir = 12;
        }
return cmd_dir;
}

void score_area(){
  // Draw the score area and wall boundary dots
  arduboy.drawRect(32, 22, 64, 20, WHITE);
  arduboy.drawPixel(0,0,WHITE);
  arduboy.drawPixel(64,0,WHITE);
  arduboy.drawPixel(127,0,WHITE);
  arduboy.drawPixel(0,32,WHITE);
  arduboy.drawPixel(127,32,WHITE);
  arduboy.drawPixel(0,62,WHITE);
  arduboy.drawPixel(64,62,WHITE);
  arduboy.drawPixel(127,62,WHITE);
  // display ships available
  for (int i = 0; i < lives - 1; i++){
    if (i <= 1){
      Sprites::drawOverwrite(35, 23 + i*8, small_ship, 0);
    }    
    else{
      Sprites::drawOverwrite(41, 23 + (i-2)*8, small_ship, 0);
    } 
  }
  // display the score using small numbers
  arduboy.drawSlowXYBitmap(74,25,score_bitmap,20,6,1); //"score"
  if (score != 0){
  dis_score = score;
  digit_pos = 0;
  digit = 0;
  while(dis_score > 0) {
        digit = dis_score % 10;               // get the rightmost digit -  mod operator, remainder after an integer division.
        Sprites::drawOverwrite(90 - digit_pos, 31, small_numbers, digit);
        dis_score = dis_score / 10;           // remove the rightmost digit
        digit_pos = digit_pos + 4;
    }
  }
  else{
        Sprites::drawOverwrite(90, 31, small_numbers, 0);
  }
  // display the level using small numbers
  arduboy.drawSlowXYBitmap(49,25,level_bitmap,21,6,1); //"Level"
  if (level != 0){
  dis_score = level;
  digit_pos = 0;
  digit = 0;
  while(dis_score > 0) {
        digit = dis_score % 10;
        Sprites::drawOverwrite(58 - digit_pos, 31, small_numbers, digit);
        dis_score = dis_score / 10;
        digit_pos = digit_pos + 4;
    }
  }
  else{
        Sprites::drawOverwrite(58, 31, small_numbers, 0);
  }
}

void level_reset(){
  drift = 0;
  drift_dir = 8;
  ship_dir = 8;
  num_kills = 0;
  clock = 0;
  ani = 0;
  accel = 0;
  cycles = 0;
  mine_count = 0;
  // alternate left and right start position for spaceship
  pos_y = 2;  
  if (level % 2){
    pos_x = 10;
    }
    else{
      pos_x = 110;
    }
  // Start positions for enemies
  for (int i = 0; i < num_droids; i++){
    arduboy.initRandomSeed();
    droid_x[i] = 30 + random(70);
    droid_y[i] = 42 + random(15);
    droid_active[i] = 1;
    droid_dir[i] = 4;
  }
  for (int i = 0; i < 2; i++){
    arduboy.initRandomSeed();
    // cmd_ship_x[i] = 30 + random(70);
    cmd_ship_x[i] = 64;
    // arduboy.initRandomSeed();
    cmd_ship_y[i] = 42 + random(15);
    death_ship_x[i] = 64;
    death_ship_y[i] = 45;
    cmd_ship_active[i] = 0;
    death_ship_active[i] = 0;
    if(random(2)){
      death_ship_dir[i] = random(3) + 5;
    }
    else{
      death_ship_dir[i] = random(3) + 9;
    }
  }
  // clear any active shots
  for (int i = 0; i < max_shots; i++){
    mis_avail[i] = 1;
    enemy_mis_avail[i] = 1;
  }
  //Reset mines
  for (int i = 0; i < num_mines; i++){
    mine_active[i] = 0;
  }
}