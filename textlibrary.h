#ifndef __TEXTLIBRARY_H__
#define __TEXTLIBRARY_H__

#include "types.h"
#include "canvas.h"

enum ETextCode{
    ETC_0,
    ETC_1,
    ETC_2,
    ETC_3,
    ETC_4,
    ETC_5,
    ETC_6,
    ETC_7,
    ETC_8,
    ETC_9,
    ETC_XIE,
    ETC_COUNT,
};
#define CHARGRAPHIWIDTH (5)
#define CHARGRAPHIHEIGHT (6)

class CTextLibrary{
public:
    static uint32 m_vTextList[ETC_COUNT][CHARGRAPHIHEIGHT][CHARGRAPHIWIDTH];
    static int32 m_vTextWidthList[ ETC_COUNT ];
    static void DrawText( CCanvas* pCavnas, int32 x, int32 y, const char* strTextCode, uint32 nColor );
};


#endif

