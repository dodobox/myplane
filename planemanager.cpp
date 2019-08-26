#include "planemanager.h"
#include "plane0.h"

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
CPlane* CPlaneManager::AddPlane( EPlaneType eType, int32 x, int32 y, EPlaneDirection eDirection, EBehaviourType eBehaviourType, EPlaneCamp eCamp ){
    CPlane* _pPlane = NULL;
    switch( eType ){
    case EPT_TYPE0:{
        _pPlane = NEW CPlane0();
    }break;
    }

    _pPlane->Init( x, y, eDirection, eBehaviourType, eCamp );
    AddPlane( _pPlane );
    return _pPlane;
}