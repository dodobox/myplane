#ifndef __PLANE_H__
#define __PLANE_H__

#include "types.h"
#include "canvas.h"
#include "planeconfig.h"
#include "stageconfig.h"

class CPlane{
public:
    CPlane();
    virtual ~CPlane();
    void InitPlane();
    virtual void Init( int32 x, int32 y, CStagePlaneInstInfo* pStagePlaneInstInfo );
    virtual void Final() = 0;
    virtual void Draw( CCanvas* pCanvas );
    virtual bool Update( float fDelta );
    virtual void Fire( int32 nType );

//protected:
    void DrawPlane( CCanvas* pCanvas, int32 x, int32 y, ESpriteDirection eDirection, int32 nShapeWidth, int32 nShapeHeight, int32 nAnchorLeft, int32 nAnchorTop, uint32 *pShape );
    int32 m_nID;
    CPlaneInfo* m_pPlaneInfo;
    CStagePlaneInstInfo* m_pStagePlaneInstInfo;
    TIntRect m_tPosDimension;   //·¶Î§
    ESpriteCamp m_eCamp;
    EPlaneType m_eType;
    EPlaneBehaviourType m_eBehaviourType;
    ESpriteDirection m_eDirection;
    EBulletEmitterType m_eEmitterType;
    TFloatPoint m_tPosition;
    
    
    float m_fAP;
    float m_fDP;
    float m_fSpeed;
    int32 m_nHP;

    friend class CBehaviourControl;

};


#endif
