#ifndef __BULLETBEHAVIOURCONTROL_H__
#define __BULLETBEHAVIOURCONTROL_H__

#include "types.h"

class CBulletBase;
class CBulletBehaviourControl{
public:
    CBulletBehaviourControl();
    virtual ~CBulletBehaviourControl();
    virtual void Init() = 0;
    virtual void Final() = 0;
    virtual void Update( CBulletBase* pBullet, float fDelta ) = 0;

    EBulletBehaviourType m_eBehaviourType;
};


#endif
