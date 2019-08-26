#ifndef __BEHAVIOURCONTROLMANAGER_H__
#define __BEHAVIOURCONTROLMANAGER_H__

#include "behaviourcontrol.h"

class CBehaviourControlManager{
public:
    static CBehaviourControlManager* GetInterface();
    static void Release();
    CBehaviourControlManager();
    virtual ~CBehaviourControlManager();
    virtual void Init();
    virtual void Final();
    CBehaviourControl* GetBehaviourControl( EBehaviourType eBehaviourType );

private:
    CBehaviourControl* m_vBehaviourControlList[ EBT_COUNT ];
};


#endif