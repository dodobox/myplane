#include "plane0.h"
#include "behaviourcontrolmanager.h"
#include "picturemanager.h"
#include "bulletmanager.h"
#include "bulletemittermanager.h"

CPlane0::CPlane0():
CPlane(){
    m_eType = EPT_TYPE0;
    CPlane::InitPlane();
    m_fFireTime = 0.0f;
}
CPlane0::~CPlane0(){

}
void CPlane0::Init( int32 x, int32 y, CStagePlaneInstInfo* pStagePlaneInstInfo ){
    CPlane::Init( x, y, pStagePlaneInstInfo );
}
void CPlane0::Final(){

}
void CPlane0::Draw( CCanvas* pCanvas ){
    CPlane::Draw( pCanvas );
}
bool CPlane0::Update( float fDelta ){
    m_fFireTime -= fDelta;
    CBehaviourControlManager::GetInterface()->GetBehaviourControl( m_eBehaviourType )->Update( this, fDelta );
    return CPlane::Update( fDelta );
}
void CPlane0::Fire( int32 nType ){
    if( m_fFireTime > 0.0f )return;
    m_fFireTime = 0.25f;

    CBulletEmitter* _pEmitter = CBulletMitterManager::GetInterface()->GetEmitter( m_eEmitterType );
    if( _pEmitter ){
        _pEmitter->Emittor( this );
    }
     

    ////EBulletType _eBulletType = m_pStagePlaneInstInfo->m_pBulletInstInfo->m_eBulletType;
    ////EBulletBehaviourType _eBehaviourType = m_pStagePlaneInstInfo->m_pBulletInstInfo->m_eBehaviourType;

    ////int32 _x = m_tPosition.X;
    ////int32 _y = m_tPosition.Y;

    ////CBulletBase* _pBullet = CBulletManager::GetInterface()->AddBullet( _eBulletType, _x, _y, m_eDirection, _eBehaviourType, m_eCamp );
    ////_pBullet->SetNormal( 0.0f, -1.0f );
    ////_pBullet->m_fAP = m_pStagePlaneInstInfo->m_pBulletInstInfo->m_tAttribute.m_nAP;
    ////_pBullet->m_fSpeed = m_pStagePlaneInstInfo->m_pBulletInstInfo->m_tAttribute.m_fSpeed;


}