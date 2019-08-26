#ifndef __PLANEMANAGER_H__
#define __PLANEMANAGER_H__

#include "canvas.h"
#include "plane.h"
#include <list>

class CPlaneManager{
public:
    static CPlaneManager* GetInterface();
    static void Release();
    CPlaneManager();
    virtual ~CPlaneManager();
    virtual void Init();
    virtual void Final();
    virtual void Update( float fDelta );
    virtual void Draw( CCanvas* pCanvas );
    virtual void AddPlane( CPlane* pPlane );
    virtual CPlane* AddPlane( EPlaneType eType, int32 x, int32 y, EPlaneDirection eDirection, EBehaviourType eBehaviourType, EPlaneCamp eCamp );
private:
    std::list<CPlane*> m_vPlaneList;
};


#endif
