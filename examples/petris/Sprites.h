
constexpr uint8 A___A = 0x00;
constexpr uint8 A__OA = 0x01;
constexpr uint8 A_O_A = 0x02;
constexpr uint8 A_OOA = 0x03;
constexpr uint8 AO__A = 0x04;
constexpr uint8 AO_OA = 0x05;
constexpr uint8 AOO_A = 0x06;
constexpr uint8 AOOOA = 0x07;

enum class BlockIndex : uint8
{
  Empty             = 0x00,   // Same as SolidBlack
  SolidBlack        = 0x00,
  SolidWhite        = 0x01,
  Donut             = 0x02,
  CenterDot         = 0x03,
  X                 = 0x04,
  O                 = 0x05,
  Plus              = 0x06,
  Corners           = 0x07,
  
  TronSquareCapN    = 0x08,
  TronSquareCapE    = 0x09,
  TronSquareCapS    = 0x0A,
  TronSquareCapW    = 0x0B,
  
  TronSquareCornerNW = 0x0C,
  TronSquareCornerNE = 0x0D,
  TronSquareCornerSE = 0x0E,
  TronSquareCornerSW = 0x0F,
  
  TronSquareNS      = 0x10,
  TronSquareEW      = 0x11,
  TronSquareSN      = 0x12,
  TronSquareWE      = 0x13,
  
  TronSquareTN      = 0x14,
  TronSquareTE      = 0x15,
  TronSquareTS      = 0x16,
  TronSquareTW      = 0x17,
  
  TronAngledCapN    = 0x18,
  TronAngledCapE    = 0x19,
  TronAngledCapS    = 0x1A,
  TronAngledCapW    = 0x1B,
  
  TronAngledCornerNW = 0x1C,
  TronAngledCornerNE = 0x1D,
  TronAngledCornerSE = 0x1E,
  TronAngledCornerSW = 0x1F,
  
  SimpleDitherCapN   = 0x20,
  SimpleDitherCapE   = 0x21,
  SimpleDitherCapS   = 0x22,
  SimpleDitherCapW   = 0x23,
  
  SimpleDitherCornerNW = 0x24,
  SimpleDitherCornerNE = 0x25,
  SimpleDitherCornerSE = 0x26,
  SimpleDitherCornerSW = 0x27,

  ShadedDitherLargeCapNW = 0x28,
  ShadedDitherLargeCapNE = 0x29, // Unused
  ShadedDitherLargeCapSE = 0x2A, // Unused
  ShadedDitherLargeCapSW = 0x2B,
  
  ShadedDitherSmallCapNW = SimpleDitherCornerNW,
  ShadedDitherSmallCapNE = SimpleDitherCornerNE,
  ShadedDitherSmallCapSE = SimpleDitherCornerSE,
  ShadedDitherSmallCapSW = SimpleDitherCornerSW,

  ShadedDitherMediumCapNW = 0x2C,
  ShadedDitherMediumCapNE = 0x2D,
  ShadedDitherMediumCapSE = 0x2E, // Unused
  ShadedDitherMediumCapSW = 0x2F,

  LineCapN = 0x30,
  LineCapE = 0x31,
  LineCapS = 0x32,
  LineCapW = 0x33,

  LineCornerNE = 0x34,
  LineCornerSE = 0x35,
  LineCornerSW = 0x36,
  LineCornerNW = 0x37,

  LineTeeN = 0x38,
  LineTeeE = 0x39,
  LineTeeS = 0x3A,
  LineTeeW = 0x3B,

  LineStraightNS = 0x3C,
  LineStraightEW = 0x3D,
  LineStraightSN = 0x3E,
  LineStraightWE = 0x3F,

  Count
};

constexpr uint8 PROGMEM BlockSprites[] =
{
  // width, height,
  3, 8,
  
  // [0] BlockSprite::SolidBlack
  A___A,
  A___A,
  A___A,
  
  // [1] BlockSprite::SolidWhite
  AOOOA,
  AOOOA,
  AOOOA,

  // [2] BlockSprite::Donut
  AOOOA,
  AO_OA,
  AOOOA,
  
  // [3] BlockIndex::CenterDot
  A___A,
  A_O_A,
  A___A,
  
  // [4] BlockSprite::X
  AO_OA,
  A_O_A,  // 'x' dither
  AO_OA,

  // [5] BlockSprite::O
  A_O_A,
  AO_OA,  // 'o' dither
  A_O_A,

  // [6] BlockSprite::Plus
  A_O_A,
  AOOOA,
  A_O_A,

  // [7] BlockSprite::Corners
  AO_OA,
  A___A,
  AO_OA,


  // [0x08] BlockSprite::TronSquareCapN
  AOOOA,  // North ->
  A__OA,  // North cap
  AOOOA,

  // [0x09] BlockSprite::TronSquareCapE
  AO_OA,
  AO_OA,  // East cap
  AOOOA,

  // [0x0A] BlockSprite::TronSquareCapS
  AOOOA,
  AO__A,  // South cap
  AOOOA,

  // [0x0B] BlockSprite::TronSquareCapW
  AOOOA,
  AO_OA,  // West cap
  AO_OA,
  

  // [0x0C] BlockSprite::TronSquareCornerNW
  AOOOA,
  A__OA,  // NW corner
  AO_OA,

  // [0x0D] BlockSprite::TronSquareCornerNE
  AO_OA,
  A__OA,  // NE corner
  AOOOA,

  // [0x0E] BlockSprite::TronSquareCornerSE
  AO_OA,
  AO__A,  // SE corner
  AOOOA,

  // [0x0F] BlockSprite::TronSquareCornerSW
  AOOOA,
  AO__A,  // SW corner
  AO_OA,


  // [0x10] BlockSprite::TronSquareNS
  AOOOA,
  A___A,  // N-S block
  AOOOA,

  // [0x11] BlockSprite::TronSquareEW
  AO_OA,
  AO_OA,  // E-W block
  AO_OA,

  // [0x12] BlockSprite::TronSquareSN
  AOOOA,
  A___A,  // Same as N-S block, but here to simplify rotation code
  AOOOA,

  // [0x13] BlockSprite::TronSquareWE
  AO_OA,
  AO_OA,  // Same as E-W block, but here to simplify rotation code
  AO_OA,


  // [0x14] BlockSprite::TronSquareTN
  AO_OA,
  AO__A,  // 'T' facing North
  AO_OA,

  // [0x15] BlockSprite::TronSquareTE
  AOOOA,
  A___A,  // 'T' facing East
  AO_OA,

  // [0x16] BlockSprite::TronSquareTS
  AO_OA,
  A__OA,  // 'T' facing South
  AO_OA,

  // [0x17] BlockSprite::TronSquareTW
  AO_OA,
  A___A,  // 'T' facing West
  AOOOA,


  // [0x18] BlockSprite::TronAngledCapN
  AOO_A,  // North ->
  A__OA,  // North cap
  AOOOA,

  // [0x19] BlockSprite::TronAngledCapE
  AO_OA,
  AO_OA,  // East cap
  A_OOA,

  // [0x1A] BlockSprite::TronAngledCapS
  AOOOA,
  AO__A,  // South cap
  A_OOA,

  // [0x1B] BlockSprite::TronAngledCapW
  AOO_A,
  AO_OA,  // West cap
  AO_OA,


  // [0x1C] BlockSprite::TronAngledCornerNW
  AOO_A,
  A__OA,  // NW corner
  AO_OA,

  // [0x1D] BlockSprite::TronAngledCornerNE
  AO_OA,
  A__OA,  // NE corner; Same as TronSquareCornerNE
  AOOOA,

  // [0x1E] BlockSprite::TronAngledCornerSE
  AO_OA,
  AO__A,  // SE corner
  A_OOA,

  // [0x1F] BlockSprite::TronAngledCornerSW
  AOOOA,
  AO__A,  // SW corner; Same as TronSquareCornerSW
  AO_OA,


  // [0x20] BlockSprite::SimpleDitherCapN
  A_OOA,
  AO_OA,  // North cap
  A_OOA,

  // [0x21] BlockSprite::SimpleDitherCapE
  A_O_A,
  AO_OA,  // East cap
  AOOOA,

  // [0x22] BlockSprite::SimpleDitherCapS
  AOO_A,
  AO_OA,  // South cap
  AOO_A,

  // [0x23] BlockSprite::SimpleDitherCapW
  AOOOA,
  AO_OA,  // West cap
  A_O_A,


  // [0x24] BlockSprite::SimpleDitherCornerNW
  A_OOA,
  AO_OA,  // NW corner
  A_O_A,

  // [0x25] BlockSprite::SimpleDitherCornerNE
  A_O_A,
  AO_OA,  // NE corner
  A_OOA,

  // [0x26] BlockSprite::SimpleDitherCornerSE
  A_O_A,
  AO_OA,  // SE corner
  AOO_A,

  // [0x27] BlockSprite::SimpleDitherCornerSW
  AOO_A,
  AO_OA,  // SW corner
  A_O_A,


  // [0x28] BlockSprite::ShadedDitherLargeCapNW
  AOOOA,
  AO_OA,  // NW large cap
  A_OOA,

  // [0x29] BlockSprite::ShadedDitherLargeCapNE
  A_OOA,
  AO_OA,  // NE large cap; Unused
  AOOOA,

  // [0x2A] BlockSprite::ShadedDitherLargeCapSE
  AOO_A,
  AO_OA,  // SE large cap; Unused
  AOOOA,

  // [0x2B] BlockSprite::ShadedDitherLargeCapSW
  AOOOA,
  AO_OA,  // SW large cap
  AOO_A,


  // Alias for the same blocks
  // [0x24] : BlockSprite::ShadedDitherSmallCapNW = SimpleDitherCornerNW
  // [0x25] : BlockSprite::ShadedDitherSmallCapNE = SimpleDitherCornerNE
  // [0x26] : BlockSprite::ShadedDitherSmallCapSE = SimpleDitherCornerSE
  // [0x27] : BlockSprite::ShadedDitherSmallCapSW = SimpleDitherCornerSW


  // [0x2C] BlockSprite::ShadedDitherMediumCapNW
  AOOOA,
  A_OOA,  // NW medium cap
  AO_OA,

  // [0x2D] BlockSprite::ShadedDitherMediumCapNE
  AO_OA,
  A_OOA,  // NE medium cap
  AOOOA,

  // [0x2E] BlockSprite::ShadedDitherMediumCapSE
  AO_OA,
  AOO_A,  // SE medium cap; Unused
  AOOOA,

  // [0x2F] BlockSprite::ShadedDitherMediumCapSW
  AOOOA,
  AOO_A,  // SW medium cap
  AO_OA,

  // LineCapN = 0x30,
  A___A,
  AOO_A,
  A___A,
  
  // LineCapE = 0x31,
  A_O_A,
  A_O_A,
  A___A,

  // LineCapS = 0x32,
  A___A,
  A_OOA,
  A___A,
  
  // LineCapW = 0x33,
  A___A,
  A_O_A,
  A_O_A,

  // LineCornerNE = 0x34,
  A_O_A,
  AOO_A,
  A___A,
  
  // LineCornerSE = 0x35,
  A_O_A,
  A_OOA,
  A___A,
  
  // LineCornerSW = 0x36,
  A___A,
  A_OOA,
  A_O_A,

  // LineCornerNW = 0x37,
  A___A,
  AOO_A,
  A_O_A,

  // LineTeeN = 0x38,
  A_O_A,
  A_OOA,
  A_O_A,
  
  // LineTeeE = 0x39,
  A___A,
  AOOOA,
  A_O_A,
  
  // LineTeeS = 0x3A,
  A_O_A,
  AOO_A,
  A_O_A,
  
  // LineTeeW = 0x3B,
  A_O_A,
  AOOOA,
  A___A,


  // LineStraightNS = 0x3C,
  A___A,
  AOOOA,
  A___A,
  
  // LineStraightEW = 0x3D,
  A_O_A,
  A_O_A,
  A_O_A,
  
  // LineStraightSN = 0x3E,
  A___A,
  AOOOA,
  A___A,
  
  // LineStraightWE = 0x3F,
  A_O_A,
  A_O_A,
  A_O_A,

};

static_assert(sizeof(BlockSprites) == int(BlockIndex::Count) * BlockSprites[0] * (BlockSprites[1] / 8) + 2,
  "Sanity check to make sure BlockIndex enum and BlockSprites array are the same size");
