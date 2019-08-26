#ifndef __CONSOLECANVS_H__
#define __CONSOLECANVS_H__

#include "canvas.h"
#include <Windows.h>

class CConsoleCanvas: public CCanvas{
public:
    CConsoleCanvas();
    virtual ~CConsoleCanvas();
    virtual void Init( int32 nWidth, int32 nHeight );
    virtual void Final();
    virtual void Clear();
    virtual bool SetPixel( int32 x, int32 y, uint32 nColor );
    virtual void* GetBuffer();
    virtual void Show();

    const char m_nFullCode = 'X';
    const char m_nNullCode = ' ';
    CHAR_INFO** m_ppCharInfo;
};


#endif

