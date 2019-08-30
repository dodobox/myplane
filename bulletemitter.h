#ifndef __BULLETEMITTER_H__
#define __BULLETEMITTER_H__

#include "types.h"

class CPlane;
class CBulletEmitter{
public:
    CBulletEmitter();
    virtual ~CBulletEmitter();
    virtual void Emittor( CPlane* pPlane ) = 0;

    EBulletEmitterType m_eBulletEmitterType;

};

class CSingleBulletEmitter: public CBulletEmitter{
public:
    CSingleBulletEmitter();
    virtual ~CSingleBulletEmitter();
    virtual void Emittor( CPlane* pPlane );

};


#endif
