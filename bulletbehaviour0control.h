#ifndef __BULLETBEHAVIOUR0CONTROL_H__
#define __BULLETBEHAVIOUR0CONTROL_H__

#include "bulletbehaviourcontrol.h"

class CBulletBehaviour0Control: public CBulletBehaviourControl{
public:
    CBulletBehaviour0Control();
    virtual ~CBulletBehaviour0Control();
    virtual void Init();
    virtual void Final();
    virtual void Update( CBulletBase* pBullet, float fDelta );
};




#endif
