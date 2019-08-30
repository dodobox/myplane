#include "stage.h"
#include "utils.h"

float CStage::m_fStageDistance = 0.0f;
float CStage::m_fStageTime = 0.0f;

CStage::CStage(){
    m_fStageDistance = 0.0f;
}
CStage::~CStage(){

}
void CStage::Init( int32 nStage ){
    char _strFileName[64];
    FormatStr( _strFileName, "stage%d.xml", nStage );
    CXMLDocment _tXMLDoc( _strFileName );
    CXMLNode _tRoot = _tXMLDoc.GetNode( "stage" );
    m_pBackGround = NEW CBackGround();
    m_pBackGround->Init( &_tRoot );
    m_pEventAndTrigger = NEW CStageEventAndTrigger();
    m_pEventAndTrigger->Init( &_tRoot );

}
void CStage::Final(){
    DELETE( m_pBackGround );
    DELETE( m_pEventAndTrigger );
}
void CStage::Update( float fDelta ){
    m_fStageDistance += m_pBackGround->m_fSpeed * fDelta;
    m_pBackGround->Update( fDelta );
    m_pEventAndTrigger->Update( fDelta );
}
void CStage::Draw( CCanvas* pCanvas ){
    m_pBackGround->Draw( pCanvas );
}
CStagePlaneInstInfo* CStage::GetStagePlayerInstInfo( int32 nIndex ){
    return m_pEventAndTrigger->GetPlaneInstInfo( nIndex );
}

