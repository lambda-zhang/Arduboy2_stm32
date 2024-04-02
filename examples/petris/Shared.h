// Shared build configuration and shared types


//==========================================================================
// Build configuration
//--------------------------------------------------------------------------

// TEST - runs unit tests instead of the game
#if defined CONFIGURATION_TEST
  #if defined(CONFIGURATION_DEBUG) || defined (CONFIGURATION_RELEASE)
    #error Multiple configurations were defined! Only one is allowed.
  #endif
  #define TEST_BUILD
  //#define GAME_BUILD
  #define DEBUGGING_ENABLED

// DEBUG - runs the game with debug features enabled
#elif defined CONFIGURATION_DEBUG
  #if defined(CONFIGURATION_TEST) || defined (CONFIGURATION_RELEASE)
    #error Multiple configurations were defined! Only one is allowed.
  #endif
  //#define TEST_BUILD
  #define GAME_BUILD
  #define DEBUGGING_ENABLED

// RELEASE - runs the game without any debugging
#elif defined CONFIGURATION_RELEASE
  #if defined(CONFIGURATION_TEST) || defined (CONFIGURATION_DEBUG)
    #error Multiple configurations were defined! Only one is allowed.
  #endif
  //#define TEST_BUILD
  #define GAME_BUILD
  //#define DEBUGGING_ENABLED   // Debugging is not enabled for release builds

#else
  #error No valid build configuration defined!
#endif

//--------------------------------------------------------------------------
// Build configuration
//==========================================================================


//==========================================================================
// Shared types
//--------------------------------------------------------------------------

// Type aliases
using uint8 = uint8_t;
using int8 = int8_t;
using uint16 = uint16_t;
using int16 = int16_t;
using uint32 = uint32_t;
using int32 = int32_t;

// Aliased types for giving the illusion of type-safety
// Some day, maybe these will be replaced with a templated type-safe solution?
using GameTicks = uint8;

//--------------------------------------------------------------------------
// Shared types
//==========================================================================


//==========================================================================
// Utility functions
//--------------------------------------------------------------------------

template<typename T>
constexpr T Min(T a, T b) { return (a <= b) ? a : b; }

template<typename T>
constexpr uint8 countof(const T& a) { return sizeof(a) / sizeof(a[0]); }

//--------------------------------------------------------------------------
// Utility functions
//==========================================================================
