#ifndef __BULLET1_H__
#define __BULLET1_H__

#include "bulletbase.h"

class CBullet1: public CBulletBase{
public:
    CBullet1();
    virtual ~CBullet1();
    virtual void Init();
    virtual void Final();
    virtual void Draw();
    virtual bool Update( float fDelta );


};


#endif

