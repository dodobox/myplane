#include "bulletbehaviourcontrolmanager.h"
#include "bulletbehaviour0control.h"

static CBulletBehaviourControlManager* _pThis = NULL;
CBulletBehaviourControlManager* CBulletBehaviourControlManager::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CBulletBehaviourControlManager();
        _pThis->Init();
    }
    return _pThis;
}
void CBulletBehaviourControlManager::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CBulletBehaviourControlManager::CBulletBehaviourControlManager(){
    for( int32 i = 0; i < EBBT_COUNT; i ++ ){
        m_vBehaviourControlList[ i ] = NULL;
    }
}
CBulletBehaviourControlManager::~CBulletBehaviourControlManager(){

}
void CBulletBehaviourControlManager::Init(){
    m_vBehaviourControlList[EBBT_0] = NEW CBulletBehaviour0Control();

    for( int32 i = 0; i < EBBT_COUNT; i ++ ){
        if( m_vBehaviourControlList[ i ] ){
            m_vBehaviourControlList[ i ]->Init();
        }
    }
}
void CBulletBehaviourControlManager::Final(){
    for( int32 i = 0; i < EBBT_COUNT; i ++ ){
        if( m_vBehaviourControlList[ i ] ){
            m_vBehaviourControlList[ i ]->Final();
            DELETE( m_vBehaviourControlList[ i ] );
        }
    }
}
CBulletBehaviourControl* CBulletBehaviourControlManager::GetBehaviourControl( EBulletBehaviourType eBehaviourType ){
    return m_vBehaviourControlList[ eBehaviourType ];
}