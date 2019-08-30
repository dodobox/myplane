#include "bulletmanager.h"
#include "collisionmap.h"
#include "Bullet0.h"
#include "plane.h"
#include "utils.h"

static CBulletManager* _pThis = NULL;
CBulletManager* CBulletManager::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CBulletManager();
        _pThis->Init();
    }
    return _pThis;
}
void CBulletManager::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CBulletManager::CBulletManager(){

}
CBulletManager::~CBulletManager(){

}
void CBulletManager::Init(){

}
void CBulletManager::Final(){
    for( auto it = m_vBulletList.begin(); it != m_vBulletList.end(); it ++ ){
        CBulletBase* _pBullet = *it;
        _pBullet->Final();
        DELETE( _pBullet );
    }
    m_vBulletList.clear();
}
void CBulletManager::Update( float fDelta ){
    CheckCollision();

    for( auto it = m_vBulletList.begin(); it != m_vBulletList.end(); ){
        CBulletBase* _pBullet = *it;
        if( _pBullet->Update( fDelta ) == false ){
            _pBullet->Final();
            DELETE( _pBullet );
            it = m_vBulletList.erase( it );
        } else{
            it ++;
        }
    }
}
void CBulletManager::Draw( CCanvas* pCanvas ){
    for( auto it = m_vBulletList.begin(); it != m_vBulletList.end(); it ++ ){
        CBulletBase* _pBullet = *it;
        _pBullet->Draw( pCanvas );
    }
}
void CBulletManager::AddBullet( CBulletBase* pBullet ){
    m_vBulletList.push_back( pBullet );
}
CBulletBase* CBulletManager::AddBullet( EBulletType eType, int32 x, int32 y, ESpriteDirection eDirection, EBulletBehaviourType eBehaviourType, ESpriteCamp eCamp ){
    CBulletBase* _pBullet = NULL;
    switch( eType ){
    case EPT_TYPE0:{
        _pBullet = NEW CBullet0();
    }break;
    }

    _pBullet->Init( x, y, eDirection, eBehaviourType, eCamp );
    AddBullet( _pBullet );
    return _pBullet;
}
void CBulletManager::CheckCollision(){
    CCollisionMap* _pCollisionMap = CCollisionMap::GetInterface();
    for( auto it = m_vBulletList.begin(); it != m_vBulletList.end(); it ++ ){
        CBulletBase* _pBullet = *it;
        ESpriteCamp _eBulletCamp = _pBullet->m_eCamp;
        ESpriteCamp _eEnemyCamp = _eBulletCamp == EPC_RED ? EPC_BLUE : EPC_RED;
        TFloatPoint& _tPT = _pBullet->m_tPosition;
        TFloatPoint& _tOriginPT = _pBullet->m_tOriginPositon;
        int32 _x = _tOriginPT.X;
        int32 _nMinY = Min<float>( _tPT.Y, _tOriginPT.Y );
        int32 _nMaxY = Max<float>( _tPT.Y, _tOriginPT.Y );
        for( int32 _y = _nMinY; _y <= _nMaxY; _y ++ ){
            CPlane* _pPlane = _pCollisionMap->GetPixel( _eEnemyCamp, _x, _y );
            if( _pPlane ){
                _pPlane->m_nHP -= 5;
                _pBullet->m_bLife = false;
                break;
            }
        }
    }
}

