#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "types.h"

class CCanvas{
public:
    static TIntPoint m_tCanvasSize;
    static TIntRect  m_tSceneActiveRect;
    static CCanvas* CreateCanvas( ECanvasType eCavansType, int32 nWidth, int32 nHeight );
    static CCanvas* GetInterface();
    CCanvas();
    virtual ~CCanvas();
    virtual void Init( int32 nWidth, int32 nHeight ) = 0;
    virtual void Final() = 0;
    virtual void Clear() = 0;
    virtual bool SetPixel( int32 x, int32 y, uint32 nColor ) = 0;
    virtual void DrawRect( int32 x, int32 y, int32 nWidth, int32 nHeight, uint32* nColors ) = 0;
    virtual void* GetBuffer() = 0;
    virtual void Show() = 0;
    ECanvasType m_eCanvasType;
    

};


#endif
