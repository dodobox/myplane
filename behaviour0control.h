#ifndef __BEHAVIOUR0CONTROL_H__
#define __BEHAVIOUR0CONTROL_H__

#include "behaviourcontrol.h"

class CBehaviour0Control: public CBehaviourControl{
public:
    CBehaviour0Control();
    virtual ~CBehaviour0Control();
    virtual void Init();
    virtual void Final();
    virtual void Update( CPlane* pPlane, float fDelta );
};




#endif
