#include <SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "EEPROM.h"
#include "../2048-Arduboy/defines.h"
#include "../2048-Arduboy/platform.h"
#include "../2048-Arduboy/controller.h"
#include "../2048-Arduboy/game.h"

#define ZOOM_SCALE 4U

SDL_Window* AppWindow = NULL;
SDL_Renderer* AppRenderer = NULL;
SDL_Surface* AppSurface = NULL;
uint8_t sBuffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];
EEPROM eeprom;
uint32_t StartTime;
uint8_t zoom_scale;

// Replicate the Arduboy screen buffer here:
uint8_t InputMask = 0;
void cleanup();

// Helper
void SetColour(uint8_t colour) {

  if (colour == COLOUR_WHITE) {
    SDL_SetRenderDrawColor(AppRenderer, 255, 255, 255, 255);
  } else {
    SDL_SetRenderDrawColor(AppRenderer, 0, 0, 0, 255);
  }
}


// From Platform.h
uint8_t Platform::ButtonState()
{
  return InputMask;
}

uint8_t* Platform::GetBuffer() {
  return sBuffer;
}

void Platform::PutPixel(uint8_t x, uint8_t y, uint8_t colour) {

  if ((x < 0) || (y < 0) || (x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT)) {
    return;
  }
  SetColour(colour);
  SDL_RenderDrawPoint(AppRenderer, x, y);
}

void Platform::DrawBuffer() {
  // Transpose sBuffer to screen. Faster than PutPixel one by one
  uint16_t i, bit;
  SDL_Rect sq;

  sq.w = sq.h = zoom_scale;

  for (i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT / 8; i++) {
    // 1 byte = 8 vertical pixels
    for (bit=0; bit<8; bit++) {
      if ((sBuffer[i] >> bit) & 0x01) {
        sq.y = zoom_scale * (i / DISPLAY_WIDTH * 8 + 7 - bit);
        sq.x = zoom_scale * (i % DISPLAY_WIDTH);
        if (SDL_FillRect(AppSurface, &sq, 0xFFFFFFFF)) {
          std::cerr << SDL_GetError() << "\n";
        }
      }
    }
  }
}

void Platform::DrawBitmap(const uint8_t* data, int16_t x, int16_t y,
    uint8_t w, uint8_t h, uint8_t colour)
{
  for (uint16_t j = 0; j < h; j++)
  {
    for (uint16_t i = 0; i < w; i++)
    {
      uint16_t blockX = i / 8;
      uint16_t blockY = j / 8;
      uint16_t blocksPerWidth = w / 8;
      uint16_t blockIndex = blockY * blocksPerWidth + blockX;
      uint8_t pixels = data[blockIndex * 8 + i % 8];
      uint8_t mask = 1 << (j % 8);
      if (pixels & mask)
      {
        PutPixel(x + i, y + j, colour);
      }
    }
  }
}

void Platform::DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    uint8_t colour) {

  SetColour(colour);

  if (SDL_RenderDrawLine(AppRenderer, x0, y0, x1, y1)) {
    std::cout << SDL_GetError() << "\n";
  }
}

void Platform::DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h,
    uint8_t colour) {
  SDL_Rect rect;

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SetColour(colour);

  if (SDL_RenderDrawRect(AppRenderer, &rect) < 0) {
    std::cout << SDL_GetError() << "\n";
  }
}

void Platform::DrawFilledRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour) {
  SDL_Rect rect;

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SetColour(colour);

  if (SDL_RenderFillRect(AppRenderer, &rect) < 0) {
    std::cout << SDL_GetError() << "\n";
  }
}

void Platform::DrawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t colour) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  PutPixel(x0, y0+r, colour);
  PutPixel(x0, y0-r, colour);
  PutPixel(x0+r, y0, colour);
  PutPixel(x0-r, y0, colour);

  while (x<y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    PutPixel(x0 + x, y0 + y, colour);
    PutPixel(x0 - x, y0 + y, colour);
    PutPixel(x0 + x, y0 - y, colour);
    PutPixel(x0 - x, y0 - y, colour);
    PutPixel(x0 + y, y0 + x, colour);
    PutPixel(x0 - y, y0 + x, colour);
    PutPixel(x0 + y, y0 - x, colour);
    PutPixel(x0 - y, y0 - x, colour);
  }
}

void Platform::DrawFilledCircle(int16_t x0, int16_t y0, uint8_t r,
    uint8_t colour) {

  SetColour(colour);

  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  // Horizontal center line
  DrawLine(x0-r, y0, x0+r, y0, colour);

  while (x<y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    DrawLine(x0+x, y0-y, x0-x, y0-y, colour);
    DrawLine(x0+y, y0-x, x0-y, y0-x, colour);
    DrawLine(x0+x, y0+y, x0-x, y0+y, colour);
    DrawLine(x0+y, y0+x, x0-y, y0+x, colour);
  }
}

void Platform::FillScreen(uint8_t colour) {

  SetColour(colour);

  if (SDL_RenderClear(AppRenderer)) {
    std::cout << SDL_GetError() << "\n";
  }
}

void Platform::Clear() {
  FillScreen(COLOUR_BLACK);
}

#ifdef DEV_DEB
void Platform::DebugPrint(uint16_t value, bool endl) {
  std::cout << value << ":";
  if (endl) {
    std::cout << "\n";
  }
  std::cout.flush();
}

void Platform::DebugPrint(int16_t value, bool endl) {
  std::cout << value << ":";
  if (endl) {
    std::cout << "\n";
  }
  std::cout.flush();
}

void Platform::DebugPrint(float value, bool endl) {
  std::cout << value << ":";
  if (endl) {
    std::cout << "\n";
  }
  std::cout.flush();
}

void Platform::DebugPrint(const uint8_t* text, bool endl) {
  std::cout << text;
  if (endl) {
    std::cout << "\n";
  }
}
#endif


// TODO: EEPROM
SavedState Platform::ToEEPROM(const uint8_t *bytes,
    const uint16_t offset, const uint16_t sz) {

  if (offset < 0) {
    return WrongOffset;
  }

  uint16_t insertAt = offset + EEPROM_STORAGE_SPACE_START;

  if (insertAt + sz > eeprom.length()) {
    return TooBig;
  }

  eeprom.write(bytes, insertAt, sz);
  return Saved;
}

SavedState Platform::FromEEPROM(uint8_t *bytes, const uint16_t offset,
    const uint16_t sz) {
  uint16_t getFrom = offset + EEPROM_STORAGE_SPACE_START;

  if (getFrom < 0) {
    return WrongOffset;
  }
  if (getFrom + sz > eeprom.length()) {
    return TooBig;
  }

  eeprom.read(bytes, getFrom, sz);
  return Saved;
}


int16_t Platform::Random(int16_t i0, int16_t i1) {
  // Return random variable between i0 and i1, inclusively
  int16_t r;

  if (i0 >= i1) return i0;

  r = random() % (i1 - i0);
  return i0 + r;
}

uint32_t Platform::GenerateRandomSeed() {
  struct timespec ts;

  if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
    std::cerr << "Error in GenerateRandomSeed" << "\n";
    return 0;
  }
  return (uint32_t)ts.tv_nsec & 0xFFFFFFFF;
}

void Platform::InitRandomSeed() {
  srandom(GenerateRandomSeed());
}

uint32_t Platform::Millis() {
  struct timespec ts;
  uint32_t ms;

  if (clock_gettime(CLOCK_REALTIME, &ts)) {
    std::cerr << "Can't get clock_gettime" << "\n";
  }
  ms = ((1000 * ts.tv_sec  + ts.tv_nsec / 1000000) & 0xFFFFFFFF) - StartTime;
  return ms;
}

// Local Functions
//
void Initialize() {
  struct timespec ts;
  memset(sBuffer, 0, sizeof(sBuffer));
  // Initialize timer from start of program
  if (clock_gettime(CLOCK_REALTIME, &ts)) {
    std::cerr << "Can't get clock_gettime" << "\n";
  }
  StartTime = (1000 * ts.tv_sec + ts.tv_nsec / 1000000) & 0xFFFFFFFF;

  // Initialize game
  InitGame();
}

int main(int argc, char* argv[])
{
  zoom_scale = ZOOM_SCALE;
  if (argc == 2) {
    zoom_scale = atoi(argv[1]);
    if ((zoom_scale < 1) || (zoom_scale > 8)) {
      zoom_scale = ZOOM_SCALE;
      std::cerr << "Zoom must be between 1 and 8" << "\n";
    }
  }

  if (SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << SDL_GetError() << "\n";
    return -1;
  }

  if (SDL_CreateWindowAndRenderer(DISPLAY_WIDTH * zoom_scale,
        DISPLAY_HEIGHT * zoom_scale, 0, &AppWindow, &AppRenderer)) {
    std::cerr << SDL_GetError() << "\n";
    cleanup();
    return -1;
  }
  if (SDL_RenderSetLogicalSize(AppRenderer, DISPLAY_WIDTH, DISPLAY_HEIGHT)) {
    std::cerr << SDL_GetError() << "\n";
    cleanup();
    return -1;
  }
  if ((AppSurface=SDL_GetWindowSurface(AppWindow)) == NULL) {
    std::cerr << SDL_GetError() << "\n";
    cleanup();
    return -1;
  }

  Initialize();

  bool running = true;
  InputMask = 0;

  while (running)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {


        case SDL_QUIT:
          running = false;
          break;

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            case SDLK_a:
              InputMask |= INPUT_A;
              break;

            case SDLK_b:
              InputMask |= INPUT_B;
              break;

            case SDLK_LEFT:
              InputMask |= INPUT_LEFT;
              break;

            case SDLK_RIGHT:
              InputMask |= INPUT_RIGHT;
              break;

            case SDLK_UP:
              InputMask |= INPUT_UP;
              break;

            case SDLK_DOWN:
              InputMask |= INPUT_DOWN;
              break;

            case SDLK_ESCAPE:
              running = false;
              break;
          }
          break;

        case SDL_KEYUP:
          switch (event.key.keysym.sym) {

            case SDLK_a:
              InputMask &= ~INPUT_A;
              break;

            case SDLK_b:
              InputMask &= ~INPUT_B;
              break;

            case SDLK_LEFT:
              InputMask &= ~INPUT_LEFT;
              break;

            case SDLK_RIGHT:
              InputMask &= ~INPUT_RIGHT;
              break;

            case SDLK_UP:
              InputMask &= ~INPUT_UP;
              break;

            case SDLK_DOWN:
              InputMask &= ~INPUT_DOWN;
              break;
          }
          break;
        }
      }
    if (!eeprom.isSaved()) {
      eeprom.save();
    }

    bool modified = StepGame();
    if (modified)
      SDL_RenderPresent(AppRenderer);

    // FrameRate
    SDL_Delay(1000 / FRAME_RATE);

  }

  cleanup();
  return 0;
}

void cleanup() {
  if (AppRenderer) {
    SDL_ClearError();
    SDL_DestroyRenderer(AppRenderer);
    std::cerr << SDL_GetError() << "\n";
  }

  if (AppWindow) {
    SDL_DestroyWindow(AppWindow);
    SDL_ClearError();
    std::cerr << SDL_GetError() << "\n";
  }

  SDL_Quit();
}
// vim:ft=cpp:fdm=syntax
