#ifndef __BULLET0_H__
#define __BULLET0_H__

#include "bulletbase.h"

class CBullet0: public CBulletBase{
public:
    CBullet0();
    virtual ~CBullet0();
    virtual void Init( int32 x, int32 y, ESpriteDirection eDirection, EBulletBehaviourType eBehaviourType, ESpriteCamp eCamp );
    virtual void Final();
    virtual void Draw( CCanvas* pCanvas );
    virtual bool Update( float fDelta );


};


#endif

