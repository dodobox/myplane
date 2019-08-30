#ifndef __COLLISIONMAP_H__
#define __COLLISIONMAP_H__

#include "types.h"

class CPlane;
class CCollisionMap{
public:
    static CCollisionMap* GetInterface();
    static void Release();
    CCollisionMap();
    ~CCollisionMap();
    void Init( int32 x, int32 y );
    void Final();
    void Clear();
    bool SetPixel( int32 x, int32 y, CPlane* pPlane );
    CPlane* GetPixel( ESpriteCamp eCamp, int32 x, int32 y );

    TIntPoint m_tSize;
    CPlane*** m_ppCollisionMap[EPC_COUNT];
};


#endif
