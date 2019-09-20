#ifndef __BEHAVIOURCONTROL_H__
#define __BEHAVIOURCONTROL_H__

#include "types.h"

class CPlane;
class CBehaviourControl: public CMemObject{
public:
    CBehaviourControl();
    virtual ~CBehaviourControl();
    virtual void Init() = 0;
    virtual void Final() = 0;
    virtual void Update( CPlane* pPlane, float fDelta ) = 0;

    EPlaneBehaviourType m_eBehaviourType;
};


#endif
