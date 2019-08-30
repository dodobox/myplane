#include "behaviourcontrolmanager.h"
#include "keyboardcontrol.h"
#include "behaviour0control.h"

static CBehaviourControlManager* _pThis = NULL;
CBehaviourControlManager* CBehaviourControlManager::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CBehaviourControlManager();
        _pThis->Init();
    }
    return _pThis;
}
void CBehaviourControlManager::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CBehaviourControlManager::CBehaviourControlManager(){
    for( int32 i = 0; i < EPBT_COUNT; i ++ ){
        m_vBehaviourControlList[ i ] = NULL;
    }
}
CBehaviourControlManager::~CBehaviourControlManager(){

}
void CBehaviourControlManager::Init(){
    m_vBehaviourControlList[ EPBT_KEYBOARD ] = NEW CKeyboardControl();
    m_vBehaviourControlList[ EPBT_TYPE0 ] = NEW CBehaviour0Control();

    for( int32 i = 0; i < EPBT_COUNT; i ++ ){
        if( m_vBehaviourControlList[ i ] ){
            m_vBehaviourControlList[ i ]->Init();
        }
    }
}
void CBehaviourControlManager::Final(){
    for( int32 i = 0; i < EPBT_COUNT; i ++ ){
        if( m_vBehaviourControlList[ i ] ){
            m_vBehaviourControlList[ i ]->Final();
            DELETE( m_vBehaviourControlList[ i ] );
        }
    }
}
CBehaviourControl* CBehaviourControlManager::GetBehaviourControl( EPlaneBehaviourType eBehaviourType ){
    return m_vBehaviourControlList[ eBehaviourType ];
}