#pragma once

#if defined(__amigaos4__)
  #include <proto/exec.h>
  #define D(x)
  #define bug(fmt, args...)  {DebugPrintF("[%s:%ld %s] ", __FILE__, __LINE__, __FUNCTION__); DebugPrintF(fmt, ##args);}
  #define dbug(fmt, args...)  {D(bug(fmt, ##args));} // TODO: this needs to be tested
#endif
