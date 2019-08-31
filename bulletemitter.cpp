#include "bulletemitter.h"
#include "plane.h"
#include "bulletbase.h"
#include "bulletmanager.h"
#include "sound.h"

CBulletEmitter::CBulletEmitter():
m_eBulletEmitterType( EBET_UNKOWN ){

}
CBulletEmitter::~CBulletEmitter(){

}

///////////////////////////////////////////////////////
CSingleBulletEmitter::CSingleBulletEmitter():
CBulletEmitter(){
    m_eBulletEmitterType = EBET_0;
}
CSingleBulletEmitter::~CSingleBulletEmitter(){

}
void CSingleBulletEmitter::Emittor( CPlane* pPlane ){

    CPlaneInfo* _pPlaneInfo = pPlane->m_pPlaneInfo;
    CStagePlaneInstInfo* _pPlaneInstInfo = pPlane->m_pStagePlaneInstInfo;
    
    EBulletType _eBulletType = _pPlaneInstInfo->m_pBulletInstInfo->m_eBulletType;
    EBulletBehaviourType _eBehaviourType = _pPlaneInstInfo->m_pBulletInstInfo->m_eBehaviourType;

    float _x = pPlane->m_tPosition.X;
    float _y = pPlane->m_tPosition.Y;


    for( int32 i = 0; i < _pPlaneInfo->m_tEmitter.m_nEmitterPoint; i ++ ){
        TIntPoint* _pEmitterPoint = &( _pPlaneInfo->m_tEmitter.m_vEmitterPoint[i]);
        float __x = _x + _pEmitterPoint->X;
        float __y = _y + _pEmitterPoint->Y;

        CBulletBase* _pBullet = CBulletManager::GetInterface()->AddBullet( _eBulletType, __x, __y, pPlane->m_eDirection, _eBehaviourType, pPlane->m_eCamp );
        switch( pPlane->m_eDirection ){
        case EPD_E:_pBullet->SetNormal( 1.0f, 0.0f ); break;
        case EPD_S:_pBullet->SetNormal( 0.0f, 1.0f ); break;
        case EPD_W:_pBullet->SetNormal( -1.0f, 0.0f ); break;
        case EPD_N:_pBullet->SetNormal( 0.0f, -1.0f ); break;
        }
        _pBullet->m_fAP = _pPlaneInstInfo->m_pBulletInstInfo->m_tAttribute.m_nAP;
        _pBullet->m_fSpeed = _pPlaneInstInfo->m_pBulletInstInfo->m_tAttribute.m_fSpeed;
    }

    PlayEffectSound( EES_0 );
}

