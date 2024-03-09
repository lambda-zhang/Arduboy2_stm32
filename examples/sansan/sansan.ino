// SanSan
//  by chamekan

#include <Arduboy2.h>
#include <ArduboyTones.h>

#include "bitmaps.h"
#include "sin.h"
#include "obj.h"

#define G 256
#define GMAX 3*256
#define b2t(a) (uint8_t)pgm_read_byte_near(bt + (a))

PROGMEM const uint8_t bt[] =
{
  0xff, 8, 16, 12, 0, 4, 0xff, 0xff, 24, 0xff, 20, 0xff, 28, 0xff, 0xff, 0xff
};

enum Mode {
  TITLE = 0,
  INIT,
  GAME,
  GAMEOVER,
} mode = TITLE;

PROGMEM const uint16_t sound1[] = {
  NOTE_C4,50,
  NOTE_C4,50,
  NOTE_A4,100,
  NOTE_G4,100,
  NOTE_F4,100,
  NOTE_C4,300,
  NOTE_REST,50,
  TONES_END
};
PROGMEM const uint16_t sound2[] = {
  NOTE_C5,100,
  NOTE_C5,100,
  NOTE_B4,100,
  NOTE_G4,100,
  NOTE_C4,300,
  NOTE_REST,50,
  TONES_END
};

char text[30];

bool button_prev = false;
bool flag_sound = true;
bool flag_se_exp = false;

uint8_t lv = 0;

uint32_t sc = 0;
uint32_t hi = 0;
int16_t x = (12*3)*256;
int16_t y =  (6+16)*256;
int16_t vx = 1;
int16_t vy = 0;

int16_t bxi = 0;
int16_t byi = 0;
int16_t bvx = 0;
int16_t bvy = 0;
bool flag_bag = false;
uint16_t tm_bag;
int16_t el = 4;
int16_t d;
uint8_t th = 0;
int8_t vth = 0;
int16_t l;

bool alive = true;
uint16_t tm_dead;

//uint8_t left = 99;

uint8_t m[8][20];

//-----------------------------------------------------------------------------
void setup(){
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
  sound.volumeMode(VOLUME_ALWAYS_HIGH);
  // Serial.begin(115200);
  // Serial.begin(9600);
}
//-----------------------------------------------------------------------------
void loop(){
  if (!arduboy.nextFrame()) return;
  //  arduboy.clear();
  switch(mode){
  case TITLE:
    title();
    break;
  case GAME:
    game();
    break;
  }
}
//-----------------------------------------------------------------------------
void title(){
  if(tm == 0){
    x = 44;
    y = 42;
  }
  arduboy.clear();
  arduboy.drawBitmap(0, 0, logo, 128, 64, WHITE);
  if(!flag_sound){
    arduboy.fillRect(83, 47, 8, 7, WHITE);
  }
  
  sprintf(text, "%09lu0", hi);
  for(uint8_t i = 0; i < 10; i++){
    if(text[i] == 0){ break; }
    arduboy.drawBitmap(i*5+64,57, num[text[i]-'0'], 4, 4, BLACK);
  }
  if(tm % 16 < 8) {
    arduboy.drawBitmap(x-4 -6, y-4 -1, sb[8], 8, 16, BLACK);
    arduboy.drawBitmap(x-4 -6, y-4 -1, sw[8], 8, 16, WHITE);
    arduboy.drawBitmap(x-6, y-6, sb[18], 16, 16, BLACK);
    arduboy.drawBitmap(x-6, y-6, sw[18], 16, 16, WHITE);
  } else {         
    arduboy.drawBitmap(x-4 -6, y-4   , sb[8], 8, 16, BLACK);
    arduboy.drawBitmap(x-4 -6, y-4   , sw[8], 8, 16, WHITE);
    arduboy.drawBitmap(x-6, y-6, sb[19], 16, 16, BLACK);
    arduboy.drawBitmap(x-6, y-6, sw[19], 16, 16, WHITE);
  }
  arduboy.display();
  tm++;
  if(arduboy.pressed(UP_BUTTON)){
    y = 42;   
  }
  if(arduboy.pressed(DOWN_BUTTON)){
    y = 42+7;   
  }
  if((arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON))){
    if(!button_prev){
      if(y == 42){
        initgame();
        mode = GAME;
      } else {
        flag_sound = !flag_sound;
      }
    }
    button_prev = true;
  } else {
    button_prev = false;
  }
}
//-----------------------------------------------------------------------------
void game(){
  arduboy.fillScreen(WHITE);
  // Draw BG

  // Trees
  for(uint8_t i = 0; i < 17; i++){
    //if(tm % 2 == 0){
      arduboy.drawBitmap(i*8-tm%8, 0, sb[2], 16, 16, BLACK);
      arduboy.drawBitmap(i*8-tm%8, 0, sw[2], 16, 16, WHITE);
    //}
  }
  
  // Snow
  for(uint8_t i = 0; i < 17; i+=2){
     arduboy.drawBitmap(i*8-tm%8+random(0, 5)-2, random(0, 5)-2, sw[3+tm%2], 16, 16, WHITE);
  }
  
  for(uint8_t j = 0; j < 8; j++){
    for(uint8_t i = 0; i < 17; i++){
      if(m[j][(i+tm/16*2)%20]==1){
        arduboy.drawBitmap(i*8-tm%16, j*8+2, sb[0], 16, 16, BLACK);
        arduboy.drawBitmap(i*8-tm%16, j*8+2, sw[0], 16, 16, WHITE);
      } else if(m[j][(i+tm/16*2)%20]==0x10){
 //       arduboy.fillRect(i*8-tm%16 -1, j*8+2-1, 10, 10, WHITE);
        arduboy.drawBitmap(i*8-tm%16, j*8+2, sb[6], 16, 16, BLACK);
        arduboy.drawBitmap(i*8-tm%16, j*8+2, sw[6], 16, 16, WHITE);

      }
    }
  }

  draw_obj(enemy, i_enemy);
  
  int16_t xi = x/256;
  int16_t yi = y/256;

  // Draw Bag
  if(alive) {
    if(!flag_bag) {
  
      if(tm % 8 < 4) {
        arduboy.drawBitmap(xi-4 -6*vx, yi-4 -1, sb[8], 8, 16, BLACK);
        arduboy.drawBitmap(xi-4 -6*vx, yi-4 -1, sw[8], 8, 16, WHITE);
      } else {         
        arduboy.drawBitmap(xi-4 -6*vx, yi-4   , sb[8], 8, 16, BLACK);
        arduboy.drawBitmap(xi-4 -6*vx, yi-4   , sw[8], 8, 16, WHITE);
      }
      
    } else {
      if(((tm - tm_bag))%16>= 14) flag_bag = false;
      int16_t l = el * sn(((tm - tm_bag))%16) / 256;
  
      bxi = xi +  (l *cs(th) )/256;
      byi = yi +  (l *sn(th) )/256;
  
      int16_t rx1 = (9 *cs((8+th)))/256/2;
      int16_t ry1 = (9 *sn((8+th)))/256/2;
  
      int16_t rx2 = (9 *cs((24+th)))/256/2;
      int16_t ry2 = (9 *sn((24+th)))/256/2;
  
      arduboy.drawBitmap(bxi-4, byi-4, sb[8], 8, 16, BLACK);
      arduboy.drawBitmap(bxi-4, byi-4, sw[8], 8, 16, WHITE);  
  
      arduboy.fillTriangle(xi, yi,
                           bxi + rx1, byi + ry1,
                           bxi + rx2, byi + ry2, WHITE);
  
      arduboy.drawLine(xi, yi, bxi + rx1, byi + ry1, BLACK);
      arduboy.drawLine(xi, yi, bxi + rx2, byi + ry2, BLACK);
  
      //arduboy.drawBitmap(bxi-4, byi-4, sb[9], 16, 16, BLACK);
  
      //arduboy.drawLine(xi+6, yi+6, bx, by, BLACK);
  
      //arduboy.setCursor(0, 56);
      //sprintf(text, "(%3d, %3d) %d",bxi, byi, l);
      //arduboy.print(text);
    }
  
    // Draw SanSan  
    if(vx > 0){
      if(tm % 8 < 4) {
          arduboy.drawBitmap(xi-6, yi-6, sb[18], 16, 16, BLACK);
          arduboy.drawBitmap(xi-6, yi-6, sw[18], 16, 16, WHITE);  
      } else {
          arduboy.drawBitmap(xi-6, yi-6, sb[19], 16, 16, BLACK);
          arduboy.drawBitmap(xi-6, yi-6, sw[19], 16, 16, WHITE);
      }
    }else{
      if(tm % 8 < 4) {
          arduboy.drawBitmap(xi-6, yi-6, sb[16], 16, 16, BLACK);
          arduboy.drawBitmap(xi-6, yi-6, sw[16], 16, 16, WHITE);  
      } else {
          arduboy.drawBitmap(xi-6, yi-6, sb[17], 16, 16, BLACK);
          arduboy.drawBitmap(xi-6, yi-6, sw[17], 16, 16, WHITE);
      }
    }
  } else {
    arduboy.drawBitmap(xi-6, yi-6, sb[20+(tm - tm_dead)/2%4], 16, 16, BLACK);
    arduboy.drawBitmap(xi-6, yi-6, sw[20+(tm - tm_dead)/2%4], 16, 16, WHITE);
  }

  // Draw bullet
  draw_obj2(bullet, i_bullet);

  // --------------------------------------------
  // Draw Score  
  arduboy.fillRect(123, 0, 5, 64, BLACK);
  //sprintf(text, "%06lu0:;%02u", sc, left);
  sprintf(text, "%09lu0", sc);
  for(uint8_t i = 0; i < 10; i++){
    if(text[i] == 0){ break; }
    arduboy.drawBitmap(124, i*5, num[text[i]-'0'], 4, 4, WHITE);
  }

  // Screen Capture Here!
  /*  
  */

  // --------------------------------------------
  // Button Pressed
  if(alive){
    if(arduboy.pressed(UP_BUTTON) && !arduboy.pressed(A_BUTTON)){
      if(vy == 0 && y > 6*256) vy = -256*15/2;
    }
    if (arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(A_BUTTON)){
      if(vy == 0 && y <= 38*256) y += 256*3;
    }
    if (arduboy.pressed(LEFT_BUTTON)){
      vx = -1;
      if(!arduboy.pressed(A_BUTTON)){
        x -= 512;
        if(x < 28*256) x = 28*256;
      }  
    }
    if (arduboy.pressed(RIGHT_BUTTON)){
      vx = 1;
      if( !arduboy.pressed(A_BUTTON)){
      if(x > (128-28-5)*256) x = (128-28-5)*256;
        x += 512;
      }
    }

    if(arduboy.pressed(A_BUTTON)){
      if(!flag_bag){
        if(flag_sound) sound.tone(440, 8);
        flag_bag = true;
        tm_bag = tm;
        
        th = b2t(arduboy.buttonsState() >> 4);
        if(th == 0xff){
          if(vx > 0) th = 0; else th = 16;
        }
        vth = 0;
        el = 24;
      } else {
         if (flag_bag && tm - tm_bag < 3){
           uint8_t th2 = b2t(arduboy.buttonsState() >> 4);
           if(th2 != 0xff){
             th = th2;
           }   
         } else {
           //if(arduboy.pressed(UP_BUTTON)   || arduboy.pressed(LEFT_BUTTON))  vth = -1;
           //if(arduboy.pressed(DOWN_BUTTON) || arduboy.pressed(RIGHT_BUTTON)) vth =  1;
          uint8_t th2 = b2t(arduboy.buttonsState() >> 4);
          if(th2 != 0xff){
            if(th2 != th && vth == 0){
              if((th2 - th +32)%32 <= 16) vth = 2; else vth = -2;
            }
          }
        }
      }
    }   
	
    // SanSan Phisycs
    vy += G;
    if(vy > GMAX) vy = GMAX;
    y += vy + G;
    /*
    if(vy > 0 && (y/256)%16 < 3){
      y = ((y/256)/16*16)*256;
      vy = 0;
    }
    */


    // Hole
    uint8_t map = m[(y/256 + 6)/8][((x/256 + 4)/8+tm/8)%20];
    if(vy >= 0 && (y/256 + 10)%16 < 4 && (map == 1 || map == 2)){
      //ya = y/256;
      y = ((y/256 + 10)/16*16-10)*256;
      //yb = y/256;
      vy = 0;
    }
    if(!(map == 1 || map == 2)){
      if(vy == 0 && y <= 38*256) y += 256*3;
    }

    // Christmas Present
    map = m[(y/256)/8][((x/256)/8+tm/8)%20];
    if(map == 0x10){
      if(flag_sound) {
        sound.tone(NOTE_C6,8, NOTE_G6,8);
      }
      m[(y/256)/8][((x/256)/8+tm/8)%20] = 0;
      sc += 10;      
    }
    
    // Bag Phisycs
    th = (th + vth + 32)%32;

    #ifdef DEBUG
    arduboy.setCursor(0, 56);
    sprintf(text, "%d %d", tm, i_enemy);
    arduboy.print(text);
    #endif
  }
  // --------------------------------------------
  // Add Map
  if(tm%16 == 0){
    uint8_t my = (16+tm/8)%20;
    if(random(0, 3) == 0){
      m[random(0 , 4)*2][my] = 0x10;
    }
    m[1][my] = 1; m[1][my+1] = 2;
    m[3][my] = 1; m[3][my+1] = 2;
    m[5][my] = 1; m[5][my+1] = 2;
    m[7][my] = 1; m[7][my+1] = 2;
    if(random(0, 8) == 0){
      uint8_t r=random(0 , 3)*2+1;
      m[r][my] = 0; m[r][my+1] = 0;
    }
  }
  
  // --------------------------------------------
  // Add Enemies
  if(tm%(70 - lv) == 0){
    if(random(0,4)<=2){
      add_enemies10();
    } else {
      add_enemies11();
    }
  }
  
  // --------------------------------------------
  // Add velocity
  add_velocity(enemy, i_enemy);
  add_velocity(bullet, i_bullet);

  // --------------------------------------------
  // Process of Enemies
  for(uint8_t i=0; i<i_enemy; i++){
    if(enemy[i].stat != 255 && enemy[i].stat != 200){             
      enemy[i].anim = tm/4%2;
      //if(random(0, 20) == 0){
      //  enemy[i].vx = -(enemy[i].vx+256)-256;
      //}
    }
    if(enemy[i].stat == 255 && ((tm - enemy[i].tm) % 2) == 0){
      enemy[i].anim = 4+ (enemy[i].anim +1-4)%4;
      //if(++enemy[i].anim > 4){
      if(tm - enemy[i].tm > 24) {
        enemy[i].stat = 0;
      }
    }
    if(enemy[i].stat == 10){
      process_enemies10(i);
    }
    if(enemy[i].stat == 20){
      process_enemies20(i);
    }
    if(enemy[i].stat == 30){
      process_enemies30(i);
    }
  }

  // --------------------------------------------
  // Collision
  
  // Bag and Enemies
  flag_se_exp = false;
  if(flag_bag){
    for(uint8_t i=0; i<i_enemy; i++){
      int16_t dx = enemy[i].x/256 - bxi;
      int16_t dy = enemy[i].y/256 - byi;
      if(enemy[i].stat != 255 && enemy[i].stat != 200 &&  dx>-8 && dx<8 && dy>-8 && dy<8){
        sc += enemy[i].stat/10;
        flag_se_exp = true;
        enemy[i].stat = 255;
        enemy[i].sp   = enemy[i].sp/8*8;
        enemy[i].anim = 4;
        enemy[i].vx   = 2*cs(th);
        enemy[i].vy   = 2*sn(th);
        enemy[i].tm   = tm;
      }
    }
  }

  // SanSan and Enemies
  if(alive){
    for(uint8_t i=0; i<i_enemy; i++){
      int16_t dx = enemy[i].x/256 - x/256;
      int16_t dy = enemy[i].y/256 - y/256;
      if(enemy[i].stat != 255 && enemy[i].stat != 200 &&  dx>-5 && dx<5 && dy>-5 && dy<5){
        gameover();
      }
    }
  }

  // SanSan and Bullets
  if(alive){
    for(uint8_t i=0; i<i_bullet; i++){
      int16_t dx = bullet[i].x/256 - x/256;
      int16_t dy = bullet[i].y/256 - y/256;
      if(dx>-4 && dx<4 && dy>-4 && dy<4){
        gameover();
      }
    }
  }

  if(flag_sound && flag_se_exp){
    for(uint8_t i = 0; i < 10; i++){
      sound.tone(random(220, 881), 8);
    }
  }
  
  // --------------------------------------------
  check_range(enemy, i_enemy, -24, -24, 128+24, 64+24);
  check_range(bullet, i_bullet, -24, -24, 128+24, 64+24);
  // --------------------------------------------
  remove_obj(enemy, &i_enemy);
  remove_obj(bullet, &i_bullet);

  //  arduboy.fillRect(0, 56, 80, 32, BLACK);

  // --------------------------------------------
  // Game Over
  if(!alive && tm - tm_dead >= 30 && tm - tm_dead <=120) {
    arduboy.drawBitmap(28, 14, gw, 66, 24, WHITE);
    arduboy.drawBitmap(28, 14, gb, 66, 24, BLACK);
  
    sprintf(text, "%09lu0", hi);
    for(uint8_t i = 0; i < 10; i++){
      if(text[i] == 0){ break; }
      arduboy.drawBitmap(i*5+43,26, num[text[i]-'0'], 4, 4, BLACK);
    }
    sprintf(text, "%09lu0", sc);
    for(uint8_t i = 0; i < 10; i++){
      if(text[i] == 0){ break; }
      arduboy.drawBitmap(i*5+43,32, num[text[i]-'0'], 4, 4, BLACK);
    }
  }


  arduboy.display();
  if(flag_sound) {
    if(tm == 0) {
      sound.tones(sound1);
      while (sound.playing()) {}
      flag_bag = false;
    }
    if(!alive && tm - tm_dead == 0) {
      sound.tones(sound2);
      while (sound.playing()) {}
    }
  }

  tm++;
  lv = tm/480;
  if(lv > 20) lv = 20;
  if(!alive &&  tm - tm_dead > 120){
    tm = 0;
    mode = TITLE;
  }
}
//-----------------------------------------------------------------------------
// Add Enemies Functions

// Nazo Right
void add_enemies10() {
  for(uint8_t i = 0; i < 4; i++){
    if(i_enemy < ENEMY_NUM){
      uint8_t en = random(0,3); 
      int16_t ex = 120*256 + random(0,3)*8*256;
      int16_t ey = (i*16+6)*256;
      uint8_t anim = 0;
      int16_t evx = -5*32-256 +random(0, 32)-16;
        
      set_obj(enemy, &i_enemy, (en+1)*10, 24+8*en, anim,
         ex, ey,
         evx, 0,
         tm);
    }
  }
}
// Nazo Left
void add_enemies11() {
  for(uint8_t i = 0; i < 4; i++){
    if(i_enemy < ENEMY_NUM){
      uint8_t en = random(0,3); 
      int16_t ex = -8*256 - random(0,3)*8*256;
      int16_t ey = (i*16+6)*256;
      uint8_t anim = 0;
      int16_t evx = 5*32 +random(0, 32)-16;             
        
      set_obj(enemy, &i_enemy, (en+1)*10, 24+8*en+2, anim,
         ex, ey,
         evx, 0,
         tm);
    }
  }
}

//-----------------------------------------------------------------------------
// Process of Enemies

// Nazo
void process_enemies10(uint8_t ii){
  if(enemy[ii].vy == 0){
    uint8_t dx = x/256 - enemy[ii].x/256;
    uint8_t sy = sign(y/256 - enemy[ii].y/256);
    if(-20 <= dx && dx <= 20 && enemy[ii].y/256 != y && random(0, 4 - lv/10) == 0) {
      enemy[ii].vx = -256;
      enemy[ii].vy = sy*256;
    }
  }
}
// Ghost
void process_enemies20(uint8_t ii){
  enemy[ii].vy = sn(tm%32)*3/2;
}

// Snowman
void process_enemies30(uint8_t ii){
  // Bullet
  if(enemy[ii].stat != 255 && dist(x,y,enemy[ii].x,enemy[ii].y) >= 30*30 && random(0, 64 - lv) == 0 && i_bullet < BULLET_NUM){
    //uint8_t d = atn((x-enemy[ii].x)/256,(y-enemy[ii].y)/256);
    //uint8_t d = atn((enemy[ii].x-x)/256,(enemy[ii].y-y)/256);
    //d=(d+random(-2, 3))%32;
    d = random(0, 32);
    set_obj(bullet, &i_bullet, 100, 11, 0, enemy[ii].x, enemy[ii].y, cs(d)*3/2-256, sn(d)*3/2, 0);
  }
}
//-----------------------------------------------------------------------------
void initgame(){
  tm = 0;
  lv = 0;
  alive = true;
  sc = 0;
  i_enemy = 0;
  i_bullet = 0;
  x = (12*3)*256;
  y =  (6+16)*256;
  vx = 1;
  vy = 0;
  flag_bag = false;

  for(uint8_t j = 0; j < 8; j++){
    for(uint8_t i = 0; i < 20; i++){
      if(j%2 == 1){
        if(i%2 == 0){
          m[j][i] = 1;
        } else{
          m[j][i] = 2;
        }
      } else {
        m[j][i] = 0;
      }
    }
  }
  /*
  m[1][0] = 0;
  m[1][1] = 0;
  m[3][8] = 0;
  m[3][9] = 0;
  m[5][12] = 0;
  m[5][13] = 0;

  m[0][12] = 0x10;
  m[2][12] = 0x10;
  */
}
//-----------------------------------------------------------------------------
void gameover(){
        flag_se_exp = true;
        alive = false;
        flag_bag = false;
        tm_dead = tm;
        if(sc > hi) hi = sc;
}

