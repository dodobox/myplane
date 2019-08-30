#include "planemanager.h"
#include "collisionmap.h"
#include "plane0.h"
#include "plane1.h"
#include "utils.h"
#include <set>

static CPlaneManager* _pThis = NULL;
CPlaneManager* CPlaneManager::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CPlaneManager();
        _pThis->Init();
    }
    return _pThis;
}
void CPlaneManager::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CPlaneManager::CPlaneManager(){

}
CPlaneManager::~CPlaneManager(){

}
void CPlaneManager::Init(){
    m_vPlayerBulletInfo[EBT_0] = {
        EBT_0,
        EBBT_0,
        { 10, 100.0f },
    };


    m_tPlayerPlaneInfo[ EPT_TYPE0 ]= {
        EPT_TYPE0,
        EPC_RED,
        EPBT_KEYBOARD,
        EPD_N,
        &m_vPlayerBulletInfo[EBT_0],
        { 10, 10, 60.0f, 100 },
    };

}
void CPlaneManager::Final(){
    for( auto it = m_vPlaneList.begin(); it != m_vPlaneList.end(); it ++ ){
        CPlane* _pPlane = *it;
        _pPlane->Final();
        DELETE( _pPlane );
    }
    m_vPlaneList.clear();
}
void CPlaneManager::Update( float fDelta ){
    CheckCollision();


    for( auto it = m_vPlaneList.begin(); it != m_vPlaneList.end(); ){
        CPlane* _pPlane = *it;
        if( _pPlane->Update( fDelta ) == false ){
            _pPlane->Final();
            DELETE( _pPlane );
            it = m_vPlaneList.erase( it );
        } else{
            it ++;
        }
    }
}
void CPlaneManager::Draw( CCanvas* pCanvas ){
    for( auto it = m_vPlaneList.begin(); it != m_vPlaneList.end(); it ++ ){
        CPlane* _pPlane = *it;
        _pPlane->Draw( pCanvas );
    }
}
void CPlaneManager::AddPlane( CPlane* pPlane ){
    m_vPlaneList.push_back( pPlane );
}
CPlane* CPlaneManager::AddPlane( EPlaneType eType, int32 x, int32 y, CStagePlaneInstInfo* pStagePlaneInstInfo ){
    CPlane* _pPlane = NULL;
    switch( eType ){
    case EPT_TYPE0:{
        _pPlane = NEW CPlane0();
    }break;
    case EPT_TYPE1:{
        _pPlane = NEW CPlane1();
    }break;
    }

    _pPlane->Init( x, y, pStagePlaneInstInfo );
    AddPlane( _pPlane );
    return _pPlane;
}
CPlane* CPlaneManager::CreatePlayerPlane( EPlaneType eType ){
    CPlane* _pPlane = AddPlane( eType, 50, 10, &m_tPlayerPlaneInfo[eType] );
    return _pPlane;
}
void CPlaneManager::CheckCollision(){
    std::set<uint32> _vCollisionSet;
    CCollisionMap* _pCollisionMap = CCollisionMap::GetInterface();
    for( int32 i = 0; i < _pCollisionMap->m_tSize.Y; i ++ ){
        for( int32 j = 0; j < _pCollisionMap->m_tSize.X; j ++ ){
            CPlane* _pRedPlane = _pCollisionMap->m_ppCollisionMap[EPC_RED][i][j];
            CPlane* _pBluePlane = _pCollisionMap->m_ppCollisionMap[EPC_BLUE][i][j];
            if( _pRedPlane && _pBluePlane ){
                uint32 _nKey0 = MAKEINT32( _pRedPlane->m_nID, _pBluePlane->m_nID );
                uint32 _nKey1 = MAKEINT32( _pBluePlane->m_nID, _pRedPlane->m_nID );
                if( _vCollisionSet.find( _nKey0 ) == _vCollisionSet.end() ||
                    _vCollisionSet.find( _nKey1 ) == _vCollisionSet.end()
                    ){
                    _pRedPlane->m_nHP -= 10;
                    _pBluePlane->m_nHP -= 10;
                    _vCollisionSet.insert( _nKey0 );
                    _vCollisionSet.insert( _nKey1 );
                }
            }
        }
    }
}