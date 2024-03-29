#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "EEPROM.h"

void addhome(char* path, const char* fn);

EEPROM::EEPROM() {
  load();
  saved = true;
}

void EEPROM::read(uint8_t* data, uint16_t idx, uint16_t sz) {
  if (idx + sz > size) {
    std::cout << "Read behind end of EEPROM" << "\n";
  }
  memcpy(data, eeprom + idx, sz);
}

void EEPROM::write(const uint8_t* data, uint16_t idx, uint16_t sz) {
  if (idx + sz > size) {
    std::cout << "Write behind end of EEPROM" << "\n";
  }
  memcpy(eeprom + idx, data, sz);
  saved = false;
}

void EEPROM::save() {
  // Save to file
  char filepath[1024];

  addhome(filepath, filename);
  std::ofstream ofile(filepath, std::ofstream::binary);

  if (!ofile) {
    std::cerr << "Can't open " << filename << " for writing" << "\n";
  }
  ofile.write((char*)eeprom, size);
  saved = true;
}

void EEPROM::load() {
  // Load from file
  char filepath[1024];

  addhome(filepath, filename);
  std::ifstream ifile(filepath, std::ifstream::binary);

  if (!ifile) {
    memset(eeprom, 0xFF, EEPROM::size);
    return;
  }
  ifile.read((char*)eeprom, size);
}

void addhome(char* path, const char* fn) {
  // Fill in path with HOME directory plus add fn
  char* home = std::getenv("HOME");

  strcpy(path, home);
  strcat(path, fn);
}

