// Define DEBUGGING_ENABLED to enable Asserts, Serial port output, and extra debugging
// Note: If this is defined before the types, I get compiler errors?!?
#ifdef DEBUGGING_ENABLED
  // TODO: Figure out how to use __FlashStringHelper* string here to avoid eating up dynamic memory
  static const char* s_stackTrace[10];
  static short s_stackTraceLine[10];
  static uint8 s_stackDepth = 0;
  class DebugStackTracker
  {
  public:
    DebugStackTracker(const char* func, short line)
    {
      s_stackTrace[s_stackDepth] = func;
      s_stackTraceLine[s_stackDepth] = line;
      s_stackDepth++;
    }
    ~DebugStackTracker()
    {
      s_stackDepth--;
    }

    static void PrintStack();
  private:
  };
  // static
  void DebugStackTracker::PrintStack()
  {
    for (uint8 i = 0; i < s_stackDepth; i++)
    {
      if (i != 0)
      {
        Serial.print(" - ");
      }
      Serial.print(s_stackTrace[i]);
      Serial.print("(");
      Serial.print(s_stackTraceLine[i]);
      Serial.print(")");
    }
  }


  // Instrumentation for getting at least partial stack traces from failed asserts
  // Usage: Sprinkle these around at the top of functions to get better data from asserts
  #define DebugStack DebugStackTracker __debugStackTracker(__FUNCTION__, __LINE__)


  char g_debugStr[80];
  void DebugPrint(const __FlashStringHelper* msg) { Serial.print(msg); }
  void DebugPrintLine(const __FlashStringHelper* msg) { Serial.println(msg); }
  void __AssertFunction(const char* func, int line, bool condition, const __FlashStringHelper* msg = nullptr)
  {
    if (!condition)
    {
      Serial.print(F("Assert Failed! "));
      Serial.print(func);
      Serial.print(F("("));
      Serial.print(line);
      Serial.print(F(") - "));
      Serial.println(msg == nullptr ? F("") : msg);
      Serial.print(F("Stack: "));
      DebugStackTracker::PrintStack();
      Serial.println();
    }
  }
  #define Assert(condition, ...) __AssertFunction(__FUNCTION__, __LINE__, (condition), ##__VA_ARGS__)

#else // #ifdef DEBUGGING_ENABLED
  void DebugPrint(...) {}
  void DebugPrintLine(...) {}
  #define Assert(condition, ...) {}
  #define DebugStack {}
#endif // #else // #ifdef DEBUGGING_ENABLED
