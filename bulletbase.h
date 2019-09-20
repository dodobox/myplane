#ifndef __BULLETBASE_H__
#define __BULLETBASE_H__

#include "types.h"
#include "canvas.h"
#include "bulletconfig.h"

class CBulletBase: public CMemObject{
public:
    CBulletBase();
    virtual ~CBulletBase();
    virtual void Init( int32 x, int32 y, ESpriteDirection eDirection, EBulletBehaviourType eBehaviourType, ESpriteCamp eCamp );
    virtual void Final();
    virtual void Draw( CCanvas* pCanvas );
    virtual bool Update( float fDelta );

//protected:

    void InitBullet();
    void DrawBullet( CCanvas* pCanvas, int32 x, int32 y, ESpriteDirection eDirection, int32 nShapeWidth, int32 nShapeHeight, int32 nAnchorLeft, int32 nAnchorTop, uint32 *pShape );
    void SetPosition( float x, float y );
    void SetNormal( float x, float y );
    int32 m_nID;
    CBulletInfo* m_pBulletInfo;
    TIntRect m_tPosDimension;   //·¶Î§
    ESpriteCamp m_eCamp;
    EBulletType m_eType;
    EBulletBehaviourType m_eBehaviourType;
    ESpriteDirection m_eDirection;
    TFloatPoint m_tPosition;
    TFloatPoint m_tOriginPositon;
    TFloatPoint m_tNormal;
    bool m_bLife;
    float m_fAP;
    float m_fSpeed;

    friend class CBulletBehaviourControl;

};


#endif

