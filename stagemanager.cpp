#include "stagemanager.h"

static CStageManager* _pThis = NULL;
CStageManager* CStageManager::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CStageManager();
        _pThis->Init();
    }
    return _pThis;
}
void CStageManager::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CStageManager::CStageManager():
m_pStage( NULL ),
m_nRound( 0 ){

}
CStageManager::~CStageManager(){
    
}
void CStageManager::Init(){

}
void CStageManager::Final(){
    if( m_pStage ){
        m_pStage->Final();
        DELETE( m_pStage );
    }
}
void CStageManager::ResetStage( int32 nStage ){
    m_nRound = nStage;
    if( m_pStage ){
        m_pStage->Final();
        DELETE( m_pStage );
    }
    m_pStage = NEW CStage();
    m_pStage->Init( m_nRound );
}
void CStageManager::Update( float fDelta ){
    if( m_pStage ){
        m_pStage->Update( fDelta );
    }
}
void CStageManager::Draw( CCanvas* pCanvas ){
    if( m_pStage ){
        m_pStage->Draw( pCanvas );
    }
}
CStage* CStageManager::GetStage(){
    return m_pStage;
}