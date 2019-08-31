#include "guimanager.h"
#include "uiinformation.h"
#include "utils.h"

static CGUIManager* _pThis = NULL;
CGUIManager* CGUIManager::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CGUIManager();
        _pThis->Init();
    }
    return _pThis;
}
void CGUIManager::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CGUIManager::CGUIManager():
CUINode(){
    m_eUIType = EUT_UIMANAGER;
}
CGUIManager::~CGUIManager(){

}
void CGUIManager::Init(){
    CUINode::Init();
    m_pInfomationDlg = NEW CUIInfoMationDlg();
    m_pInfomationDlg->Init();
    AddChild( m_pInfomationDlg );
}
void CGUIManager::Final(){
    CUINode::Final();
}
void CGUIManager::Update( float fDelta ){
    CUINode::Update( fDelta );
}
void CGUIManager::Draw( CCanvas* pCanvas ){
    CUINode::Draw( pCanvas );
}
void CGUIManager::UpdateInfo( EUIUpdateInfoType eType, int32 nParame0, int32 nParame1 ){
    switch( eType ){
    case EUUIT_0: m_pInfomationDlg->SetHP( nParame0 );   break;    //更新hp
    case EUUIT_1: m_pInfomationDlg->SetScore( nParame0 );  break;    //更新score
    case EUUIT_2: m_pInfomationDlg->SetDistance( nParame0, nParame1 ); break;    //更新distance
    }
}