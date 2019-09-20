#ifndef __DCCANVS_H__
#define __DCCANVS_H__

#include "canvas.h"


class CDCCanvas: public CCanvas{
public:
    CDCCanvas();
    virtual ~CDCCanvas();
    virtual void Init( int32 nWidth, int32 nHeight );
    virtual void Final();
    virtual void Clear();
    virtual bool SetPixel( int32 x, int32 y, uint32 nColor );
    virtual void DrawRect( int32 x, int32 y, int32 nWidth, int32 nHeight, uint32* pColors );
    virtual void* GetBuffer();
    virtual void Show();
    //void SetBKPixel( int32 x, int32 y, uint32 nColor );
    int32 Get16ColorIndex( uint32 nColor );

    uint32 console;
    uint32   console_hdc;
    uint32** m_ppFGCanvas;
};


#endif

