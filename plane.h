#ifndef __PLANE_H__
#define __PLANE_H__

#include "types.h"
#include "canvas.h"

class CPlane{
public:
    CPlane();
    virtual ~CPlane();
    virtual void Init( int32 x, int32 y, EPlaneDirection eDirection, EBehaviourType eBehaviourType, EPlaneCamp eCamp ) = 0;
    virtual void Final() = 0;
    virtual void Draw( CCanvas* pCanvas ) = 0;
    virtual bool Update( float fDelta ) = 0;
    void DrawPlane( CCanvas* pCanvas, int32 x, int32 y, EPlaneDirection eDirection, int32 nShapeWidth, int32 nShapeHeight, int32 nAnchorLeft, int32 nAnchorTop, uint32 *pShape );
    int32 m_nID;
    EPlaneCamp m_eCamp;
    EPlaneType m_eType;
    EBehaviourType m_eBehaviourType;
    EPlaneDirection m_eDirection;
    TFloatPoint m_tPosition;
    
    float m_fAP;
    float m_fDP;
    float m_fSpeed;
    int32 m_nHP;

};


#endif
