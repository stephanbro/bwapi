#include "Graphics.h"
#include "GameImpl.h"
#include "BW/BWData.h"

#include <BWAPI/CoordinateType.h>
#include <BWAPI/Color.h>

static inline void bwPlot(const int &x, const int &y, const int &color)
{
  BWAPI::BroodwarImpl.bwgame.GameScreenBuffer().plot(x, y, static_cast<u8>(color));
}

static inline void convertCoordType(int &x, int &y, const BWAPI::CoordinateType::Enum &ctype)
{
  switch ( ctype )
  {
  case BWAPI::CoordinateType::Map:
    x -= BWAPI::BroodwarImpl.bwgame.ScreenX();
    y -= BWAPI::BroodwarImpl.bwgame.ScreenY();
    break;
  case BWAPI::CoordinateType::Mouse:
    x += BWAPI::BroodwarImpl.bwgame.MouseX();
    y += BWAPI::BroodwarImpl.bwgame.MouseY();
    break;
  }
}

void bwDrawBox(int x, int y, int w, int h, int color, BWAPI::CoordinateType::Enum ctype)
{
  convertCoordType(x, y, ctype);

  for ( int i = y; i < y+h; ++i )
    BWAPI::BroodwarImpl.bwgame.GameScreenBuffer().drawLine(x, i, x+w, i, static_cast<u8>(color));
}

void bwDrawDot(int x, int y, int color, BWAPI::CoordinateType::Enum ctype)
{
  // Convert coordinate type
  convertCoordType(x, y, ctype);

  // Plot the point
  bwPlot(x, y, color);
}

// Assume x1 != x2 and y1 != y2
void bwDrawLine(int x1, int y1, int x2, int y2, int color, BWAPI::CoordinateType::Enum ctype)
{
  convertCoordType(x1,y1,ctype);
  convertCoordType(x2,y2,ctype);

  BWAPI::BroodwarImpl.bwgame.GameScreenBuffer().drawLine(x1, y1, x2, y2, static_cast<u8>(color));
}

void bwDrawText(int x, int y, const char* ptext, BWAPI::CoordinateType::Enum ctype, char size)
{
  convertCoordType(x, y, ctype);
  BWAPI::BroodwarImpl.bwgame.GameScreenBuffer().blitString(ptext, x, y, size);
}
