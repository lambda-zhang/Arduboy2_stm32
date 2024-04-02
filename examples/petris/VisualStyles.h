
// These are the first two bits of the first byte of visual style data
// Depending on the type, the other 6 bits may be used for additional data
enum class VisualStyleType : uint8
{
  SolidBlock              = 0x00,
  PerBlockNoRotation      = 0x01,
  PerBlockWithRotation    = 0x02,
  PerOrientationAndBlock  = 0x03,

  Count,
};
constexpr uint8 k_visualStyleTypeBits = 2;
constexpr uint8 k_visualStyleTypeMask = (1 << k_visualStyleTypeBits) - 1;
static_assert(int(VisualStyleType::Count) <= (1 << k_visualStyleTypeBits), "VisualStyleType needs to fit in the bits available");


enum class VisualStyle : uint8
{
  SolidBlack,
  SolidWhite,
  Donut,
  CenterDot,
  X,
  O,
  Plus,
  Line,
  TronSquare,
  TronAngled,
  SimpleDither,
  ShadedDither,

  Count,
};

const char k_styleName0[] PROGMEM = "SolidBlack";
const char k_styleName1[] PROGMEM = "SolidWhite";
const char k_styleName2[] PROGMEM = "Donut";
const char k_styleName3[] PROGMEM = "Dot";
const char k_styleName4[] PROGMEM = "X";
const char k_styleName5[] PROGMEM = "O";
const char k_styleName6[] PROGMEM = "Plus";
const char k_styleName7[] PROGMEM = "Line";
const char k_styleName8[] PROGMEM = "TronSquare";
const char k_styleName9[] PROGMEM = "TronAngled";
const char k_styleName10[] PROGMEM = "SimpleDither";
const char k_styleName11[] PROGMEM = "ShadedDither";

// For accessing an array of strings in program memory, see...
// http://www.nongnu.org/avr-libc/user-manual/pgmspace.html
PGM_P const k_styleNames[] PROGMEM =
{
  k_styleName0,
  k_styleName1,
  k_styleName2,
  k_styleName3,
  k_styleName4,
  k_styleName5,
  k_styleName6,
  k_styleName7,
  k_styleName8,
  k_styleName9,
  k_styleName10,
  k_styleName11,
};
static_assert(countof(k_styleNames) == uint8(VisualStyle::Count), "Make sure data matches the enum");


// Helper for generating solid visual styles
// These are ones that can be described by a single byte
// Bits [0..1] are the VisualStyleType and bits [2..7] are the BlockIndex
constexpr uint8 MakeSolidVisualStyle(VisualStyleType type, BlockIndex block)
{
  static_assert(uint8(BlockIndex::Count) <= (1 << (8 - k_visualStyleTypeBits)), "Verify all BlockIndex entries can fit in the remaining bits");
  return uint8(type) | (uint8(block) << k_visualStyleTypeBits);
}

// Unpacks values that were packed in MakeSolidVisualStyle
// 'outSolidBlockIndex' will only have valid data in it if VisualStyleType is SolidBlock
VisualStyleType GetVisualStyleTypeFromFirstByte(uint8 firstByte, BlockIndex& outSolidBlockIndex)
{
  // Sign-extention shouldn't happen here since firstByte is an unsigned value
  outSolidBlockIndex = BlockIndex(firstByte >> k_visualStyleTypeBits);
  VisualStyleType type = VisualStyleType(firstByte & k_visualStyleTypeMask);
  return type;
}

constexpr const uint8 k_perBlockStyleDataOffset = 1;  // Offset in bytes of style data (first byte is header)
constexpr const uint8 k_perBlockStyleStride = 4;      // How many bytes are used per piece
constexpr const uint8 k_perBlockStyleTotalSize = k_perBlockStyleDataOffset + (k_perBlockStyleStride * uint8(PieceIndex::Count));

constexpr const uint8 k_perBlockAndOrientationStyleDataOffset = 1;  // Offset in bytes of style data (first byte is header)
constexpr const uint8 k_perBlockAndOrientationStride = 4 * uint8(PieceOrientation::Count);      // How many bytes are used per piece
constexpr const uint8 k_perBlockAndOrientationStyleTotalSize = k_perBlockAndOrientationStyleDataOffset + (k_perBlockAndOrientationStride * uint8(PieceIndex::Count));

constexpr uint8 PROGMEM k_styleDataSolidBlack[] = {MakeSolidVisualStyle(VisualStyleType::SolidBlock, BlockIndex::SolidBlack)};
constexpr uint8 PROGMEM k_styleDataSolidWhite[] = {MakeSolidVisualStyle(VisualStyleType::SolidBlock, BlockIndex::SolidWhite)};
constexpr uint8 PROGMEM k_styleDataDonut[] = {MakeSolidVisualStyle(VisualStyleType::SolidBlock, BlockIndex::Donut)};
constexpr uint8 PROGMEM k_styleDataCenterDot[] = {MakeSolidVisualStyle(VisualStyleType::SolidBlock, BlockIndex::CenterDot)};
constexpr uint8 PROGMEM k_styleDataX[] = {MakeSolidVisualStyle(VisualStyleType::SolidBlock, BlockIndex::X)};
constexpr uint8 PROGMEM k_styleDataO[] = {MakeSolidVisualStyle(VisualStyleType::SolidBlock, BlockIndex::O)};
constexpr uint8 PROGMEM k_styleDataPlus[] = {MakeSolidVisualStyle(VisualStyleType::SolidBlock, BlockIndex::Plus)};

constexpr uint8 PROGMEM k_styleDataLine[] =
{
  uint8(VisualStyleType::PerBlockWithRotation),
  // Piece order - O, I, T, L, J, S, Z,
  uint8(BlockIndex::LineCornerSW), uint8(BlockIndex::LineCornerSE), uint8(BlockIndex::LineCornerNW), uint8(BlockIndex::LineCornerNE), // O-Block
  uint8(BlockIndex::LineCapW), uint8(BlockIndex::LineStraightEW), uint8(BlockIndex::LineStraightEW), uint8(BlockIndex::LineCapE), // I-Block
  uint8(BlockIndex::LineCapW), uint8(BlockIndex::LineTeeN), uint8(BlockIndex::LineCapE), uint8(BlockIndex::LineCapN), // T-Block
  uint8(BlockIndex::LineCapW), uint8(BlockIndex::LineStraightEW), uint8(BlockIndex::LineCornerSE), uint8(BlockIndex::LineCapN), // L-Block
  uint8(BlockIndex::LineCornerSW), uint8(BlockIndex::LineStraightEW), uint8(BlockIndex::LineCapE), uint8(BlockIndex::LineCapN), // J-Block
  uint8(BlockIndex::LineCapW), uint8(BlockIndex::LineCornerSE), uint8(BlockIndex::LineCornerNW), uint8(BlockIndex::LineCapE), // S-Block
  uint8(BlockIndex::LineCornerSW), uint8(BlockIndex::LineCapE), uint8(BlockIndex::LineCapW), uint8(BlockIndex::LineCornerNE), // Z-Block
};
static_assert(countof(k_styleDataLine) == k_perBlockStyleTotalSize);

constexpr uint8 PROGMEM k_styleDataTronSquare[] =
{
  uint8(VisualStyleType::PerBlockWithRotation),
  // Piece order - O, I, T, L, J, S, Z,
  uint8(BlockIndex::TronSquareCornerSW), uint8(BlockIndex::TronSquareCornerSE), uint8(BlockIndex::TronSquareCornerNW), uint8(BlockIndex::TronSquareCornerNE), // O-Block
  uint8(BlockIndex::TronSquareCapW), uint8(BlockIndex::TronSquareEW), uint8(BlockIndex::TronSquareEW), uint8(BlockIndex::TronSquareCapE), // I-Block
  uint8(BlockIndex::TronSquareCapW), uint8(BlockIndex::TronSquareTN), uint8(BlockIndex::TronSquareCapE), uint8(BlockIndex::TronSquareCapN), // T-Block
  uint8(BlockIndex::TronSquareCapW), uint8(BlockIndex::TronSquareEW), uint8(BlockIndex::TronSquareCornerSE), uint8(BlockIndex::TronSquareCapN), // L-Block
  uint8(BlockIndex::TronSquareCornerSW), uint8(BlockIndex::TronSquareEW), uint8(BlockIndex::TronSquareCapE), uint8(BlockIndex::TronSquareCapN), // J-Block
  uint8(BlockIndex::TronSquareCapW), uint8(BlockIndex::TronSquareCornerSE), uint8(BlockIndex::TronSquareCornerNW), uint8(BlockIndex::TronSquareCapE), // S-Block
  uint8(BlockIndex::TronSquareCornerSW), uint8(BlockIndex::TronSquareCapE), uint8(BlockIndex::TronSquareCapW), uint8(BlockIndex::TronSquareCornerNE), // Z-Block
};
static_assert(countof(k_styleDataTronSquare) == k_perBlockStyleTotalSize);

constexpr uint8 PROGMEM k_styleDataTronAngled[] =
{
  uint8(VisualStyleType::PerBlockWithRotation),
  // Piece order - O, I, T, L, J, S, Z,
  uint8(BlockIndex::TronAngledCornerSW), uint8(BlockIndex::TronAngledCornerSE), uint8(BlockIndex::TronAngledCornerNW), uint8(BlockIndex::TronAngledCornerNE), // O-Block
  uint8(BlockIndex::TronAngledCapW), uint8(BlockIndex::TronSquareEW), uint8(BlockIndex::TronSquareEW), uint8(BlockIndex::TronAngledCapE), // I-Block
  uint8(BlockIndex::TronAngledCapW), uint8(BlockIndex::TronSquareTN), uint8(BlockIndex::TronAngledCapE), uint8(BlockIndex::TronAngledCapN), // T-Block
  uint8(BlockIndex::TronAngledCapW), uint8(BlockIndex::TronSquareEW), uint8(BlockIndex::TronAngledCornerSE), uint8(BlockIndex::TronAngledCapN), // L-Block
  uint8(BlockIndex::TronAngledCornerSW), uint8(BlockIndex::TronSquareEW), uint8(BlockIndex::TronAngledCapE), uint8(BlockIndex::TronAngledCapN), // J-Block
  uint8(BlockIndex::TronAngledCapW), uint8(BlockIndex::TronAngledCornerSE), uint8(BlockIndex::TronAngledCornerNW), uint8(BlockIndex::TronAngledCapE), // S-Block
  uint8(BlockIndex::TronAngledCornerSW), uint8(BlockIndex::TronAngledCapE), uint8(BlockIndex::TronAngledCapW), uint8(BlockIndex::TronAngledCornerNE), // Z-Block
};
static_assert(countof(k_styleDataTronAngled) == k_perBlockStyleTotalSize);

constexpr uint8 PROGMEM k_styleDataSimpleDither[] =
{
  uint8(VisualStyleType::PerOrientationAndBlock),
  // Piece order - O, I, T, L, J, S, Z,
  // O-Block
  uint8(BlockIndex::SimpleDitherCornerSW), uint8(BlockIndex::X), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCornerNE),
  uint8(BlockIndex::SimpleDitherCornerNW), uint8(BlockIndex::X), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCornerSE),
  uint8(BlockIndex::SimpleDitherCornerNE), uint8(BlockIndex::X), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCornerSW),
  uint8(BlockIndex::SimpleDitherCornerSE), uint8(BlockIndex::X), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCornerNW),

  // I-Block
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapE),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapS),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapW),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapN),

  // T-Block
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::X),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::X),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::X),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::X),

  // L-Block
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapN),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapE),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapS),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapW),

  // J-Block
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapN),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapE),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapS),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapW),

  // S-Block
  uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCornerSE), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapE),
  uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCornerSW), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapS),
  uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCornerNW), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapW),
  uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCornerNE), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapN),

  // Z-Block
  uint8(BlockIndex::SimpleDitherCornerSW), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapW), uint8(BlockIndex::X),
  uint8(BlockIndex::SimpleDitherCornerNW), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapN), uint8(BlockIndex::X),
  uint8(BlockIndex::SimpleDitherCornerNE), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapE), uint8(BlockIndex::X),
  uint8(BlockIndex::SimpleDitherCornerSE), uint8(BlockIndex::X), uint8(BlockIndex::SimpleDitherCapS), uint8(BlockIndex::X),
};
static_assert(countof(k_styleDataSimpleDither) == k_perBlockAndOrientationStyleTotalSize);

constexpr uint8 PROGMEM k_styleDataShadedDither[] =
{
  uint8(VisualStyleType::PerOrientationAndBlock),
  // Piece order - O, I, T, L, J, S, Z,
  // O-Block
  uint8(BlockIndex::ShadedDitherSmallCapSW), uint8(BlockIndex::X), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherSmallCapNE),
  uint8(BlockIndex::ShadedDitherSmallCapNW), uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::ShadedDitherSmallCapSE),
  uint8(BlockIndex::ShadedDitherSmallCapNE), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::X), uint8(BlockIndex::ShadedDitherSmallCapSW),
  uint8(BlockIndex::ShadedDitherSmallCapSE), uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::ShadedDitherSmallCapNW),

  // I-Block
  uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::ShadedDitherLargeCapNE),
  uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::ShadedDitherLargeCapSW),
  uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::ShadedDitherLargeCapNW),
  uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::ShadedDitherLargeCapNW),

  // T-Block
  uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::ShadedDitherMediumCapNW),
  uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::ShadedDitherMediumCapNE),
  uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherMediumCapSW),
  uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherMediumCapNW),

  // L-Block
  uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::O), uint8(BlockIndex::X), uint8(BlockIndex::ShadedDitherLargeCapNW),
  uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::ShadedDitherLargeCapNE),
  uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherLargeCapSW),
  uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::ShadedDitherLargeCapNW),

  // J-Block
  uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::ShadedDitherLargeCapNW),
  uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::ShadedDitherLargeCapNE),
  uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherLargeCapSW),
  uint8(BlockIndex::X), uint8(BlockIndex::O), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherLargeCapNW),

  // S-Block
  uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherSmallCapSE), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherLargeCapNE),
  uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherSmallCapSW), uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::ShadedDitherLargeCapSW),
  uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::ShadedDitherSmallCapNW), uint8(BlockIndex::X), uint8(BlockIndex::ShadedDitherLargeCapNW),
  uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::ShadedDitherSmallCapNE), uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::ShadedDitherLargeCapNW),

  // Z-Block
  uint8(BlockIndex::ShadedDitherSmallCapSW), uint8(BlockIndex::ShadedDitherMediumCapNE), uint8(BlockIndex::ShadedDitherLargeCapNW), uint8(BlockIndex::ShadedDitherMediumCapNE),
  uint8(BlockIndex::ShadedDitherSmallCapNW), uint8(BlockIndex::ShadedDitherMediumCapSW), uint8(BlockIndex::ShadedDitherLargeCapNW), uint8(BlockIndex::X),
  uint8(BlockIndex::ShadedDitherSmallCapNE), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherLargeCapNE), uint8(BlockIndex::ShadedDitherMediumCapSW),
  uint8(BlockIndex::ShadedDitherSmallCapSE), uint8(BlockIndex::ShadedDitherMediumCapNW), uint8(BlockIndex::ShadedDitherLargeCapSW), uint8(BlockIndex::ShadedDitherMediumCapNW),
};
static_assert(countof(k_styleDataSimpleDither) == k_perBlockAndOrientationStyleTotalSize);


constexpr const uint8* k_visualStyles[] PROGMEM =
{
  k_styleDataSolidBlack,
  k_styleDataSolidWhite,
  k_styleDataDonut,
  k_styleDataCenterDot,
  k_styleDataX,
  k_styleDataO,
  k_styleDataPlus,
  k_styleDataLine,
  k_styleDataTronSquare,
  k_styleDataTronAngled,
  k_styleDataSimpleDither,
  k_styleDataShadedDither
};
static_assert(countof(k_visualStyles) == uint8(VisualStyle::Count), "Make sure data matches the enum");

class VisualStyleHelper
{
  public:
    VisualStyleHelper(VisualStyle visualStyle) : m_visualStyle(visualStyle) {}

    BlockIndex GetBlockForPiece(PieceIndex pieceIndex, PieceOrientation orientation, uint8 index) const;

  private:
    VisualStyle m_visualStyle;
};

BlockIndex VisualStyleHelper::GetBlockForPiece(PieceIndex pieceIndex, PieceOrientation orientation, uint8 index) const
{
  Assert(index < 4);
  #ifndef STM32F103xB
  uint8* pgm_styleData = pgm_read_word(&k_visualStyles[uint8(m_visualStyle)]);
  #else
  const uint8* pgm_styleData = k_visualStyles[uint8(m_visualStyle)];
  #endif /* STM32F103xB */
  uint8 firstByte = pgm_read_byte(&pgm_styleData[0]);

  BlockIndex blockIndex;
  VisualStyleType styleType = GetVisualStyleTypeFromFirstByte(firstByte, blockIndex);

  switch (styleType)
  {
    case VisualStyleType::SolidBlock:
      // nothing else to do; blockIndex was already set by call to GetVisualStyleTypeFromFirstByte
      break;

    case VisualStyleType::PerBlockWithRotation:
    {
      const uint8 offsetIntoStyleData = k_perBlockStyleDataOffset + (k_perBlockStyleStride * uint8(pieceIndex)) + index;
      blockIndex = BlockIndex(pgm_read_byte(&pgm_styleData[offsetIntoStyleData]));
      // Take piece orientationinto account
      static_assert(uint8(PieceOrientation::Count) == 4, "Rotation code here, and data format expects there to be 4 orientations");
      constexpr uint8 orientationMask = 0x03;
      blockIndex = BlockIndex((uint8(blockIndex) & ~orientationMask) | ((uint8(blockIndex) + uint8(orientation)) & orientationMask));
      break;
    }

    case VisualStyleType::PerOrientationAndBlock:
    {
      const uint8 offsetIntoStyleData =
        k_perBlockAndOrientationStyleDataOffset
        + (k_perBlockAndOrientationStride * uint8(pieceIndex))
        + (k_perBlockStyleStride * uint8(orientation))
        + index;
        blockIndex = BlockIndex(pgm_read_byte(&pgm_styleData[offsetIntoStyleData]));
      break;
    }
    default:
      Assert(false, F("VisualStyleType not implemented!"));
  }

  return blockIndex;
}
