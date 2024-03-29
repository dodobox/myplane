#ifndef __TRUECOLORCONSOLECANVS_H__
#define __TRUECOLORCONSOLECANVS_H__

#include "canvas.h"
#include <Windows.h>

class CTrueColorConsoleCanvas: public CCanvas{
public:
    CTrueColorConsoleCanvas();
    virtual ~CTrueColorConsoleCanvas();
    virtual void Init( int32 nWidth, int32 nHeight );
    virtual void Final();
    virtual void Clear();
    virtual bool SetPixel( int32 x, int32 y, uint32 nColor );
    virtual void DrawRect( int32 x, int32 y, int32 nWidth, int32 nHeight, uint32* pColors );
    virtual void* GetBuffer();
    virtual void Show();
    //void SetBKPixel( int32 x, int32 y, uint32 nColor );
    int32 Get16ColorIndex( uint32 nColor );

    //HWND console;
    //HDC  console_hdc;
    uint32** m_ppFGCanvas;
};


#endif

