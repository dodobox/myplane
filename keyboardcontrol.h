#ifndef __KEYBOARDCONTROL_H__
#define __KEYBOARDCONTROL_H__

#include "behaviourcontrol.h"

class CKeyboardControl: public CBehaviourControl{
public:
    CKeyboardControl();
    virtual ~CKeyboardControl();
    virtual void Init();
    virtual void Final();
    virtual void Update( CPlane* pPlane, float fDelta );
};




#endif
