#ifndef __PLANE1_H__
#define __PLANE1_H__

#include "plane.h"

class CPlane1: public CPlane{
public:
    CPlane1();
    virtual ~CPlane1();
    virtual void Init( int32 x, int32 y, EPlaneDirection eDirection, EBehaviourType eBehaviourType, EPlaneCamp eCamp );
    virtual void Final();
    virtual void Draw( CCanvas* pCanvas );
    virtual bool Update( float fDelta );



};


#endif
