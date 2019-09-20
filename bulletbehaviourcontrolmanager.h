#ifndef __BULLETBEHAVIOURCONTROLMANAGER_H__
#define __BULLETBEHAVIOURCONTROLMANAGER_H__

#include "bulletbehaviourcontrol.h"

class CBulletBehaviourControlManager: public CMemObject{
public:
    static CBulletBehaviourControlManager* GetInterface();
    static void Release();
    CBulletBehaviourControlManager();
    virtual ~CBulletBehaviourControlManager();
    virtual void Init();
    virtual void Final();
    CBulletBehaviourControl* GetBehaviourControl( EBulletBehaviourType eBehaviourType );

private:
    CBulletBehaviourControl* m_vBehaviourControlList[ EBBT_COUNT ];
};


#endif
