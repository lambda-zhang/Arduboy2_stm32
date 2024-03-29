#include <stdint.h>

#define EEPROM_STORAGE_SPACE_START 0x10

class EEPROM {
  public:
    EEPROM();
    ~EEPROM() {}
    void read(uint8_t* data, uint16_t idx, uint16_t sz);
    void write(const uint8_t* data, uint16_t idx, uint16_t sz);
    uint16_t length() {return size;}
    bool isSaved() {return saved;}
    // Called periodically to persist data, for instance in game loop
    void save(); // Save to file


  private:
    void load(); // Load from file
    bool saved;
    static constexpr uint16_t size = 0x400;
    static constexpr char filename[] = "/tmp/EEPROM.bin";
    uint8_t eeprom[size];
};
// vim:ft=cpp
