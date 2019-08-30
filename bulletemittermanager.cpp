#include "bulletemittermanager.h"

static CBulletMitterManager* _pThis = NULL;
CBulletMitterManager* CBulletMitterManager::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CBulletMitterManager();
        _pThis->Init();
    }
    return _pThis;
}
void CBulletMitterManager::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CBulletMitterManager::CBulletMitterManager(){
    for( int32 i = 0; i < EBET_COUNT; i ++ ){
        m_vEmitterList[i] = NULL;
    }
}
CBulletMitterManager::~CBulletMitterManager(){

}
CBulletEmitter* CBulletMitterManager::GetEmitter( EBulletEmitterType eEmitter ){
    return m_vEmitterList[eEmitter];
}
void CBulletMitterManager::Init(){
    m_vEmitterList[ EBET_0 ] = NEW CSingleBulletEmitter();
}
void CBulletMitterManager::Final(){
    for( int32 i = 0; i < EBET_COUNT; i ++ ){
        DELETE( m_vEmitterList[i] );
    }
}