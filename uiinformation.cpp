#include "uiinformation.h"
#include "utils.h"

CUIInfoMationDlg::CUIInfoMationDlg():
CUINode(){
    m_eUIType = EUT_INFOMATIONDLG;
    m_pBKImage = NULL;
    m_pHPLabel = NULL;
    m_pDistanceLabel = NULL;
    m_pScoreLabel = NULL;

    m_nHP = 0;
    m_nScore = 0;
    m_nDistance = 0;
    m_nMaxDistance = 0;
}
CUIInfoMationDlg::~CUIInfoMationDlg(){

}
void CUIInfoMationDlg::Init(){
    m_pBKImage = NEW CUIImage();
    m_pBKImage->SetPosition( 0, 0 );
    m_pBKImage->SetImage("ui/infomationbk.png");

    m_pHPLabel = NEW CUILabel();
    m_pHPLabel->SetPosition( 16, 2 );
    m_pHPLabel->SetText( "0" );

    m_pScoreLabel = NEW CUILabel();
    m_pScoreLabel->SetPosition( 61, 2 );
    m_pScoreLabel->SetText( "0" );

    m_pDistanceLabel = NEW CUILabel();
    m_pDistanceLabel->SetPosition( 40, 12 );
    m_pDistanceLabel->SetText( "0/0" );



    AddChild( m_pBKImage );
    AddChild( m_pHPLabel );
    AddChild( m_pDistanceLabel );
    AddChild( m_pScoreLabel );
    CUINode::Init();
}

void CUIInfoMationDlg::Final(){
    CUINode::Final();
}
void CUIInfoMationDlg::SetHP( int32 nHP ){
    char _strText[1024];
    if( nHP != m_nHP ){
        m_nHP = nHP;
        m_pHPLabel->SetText( FormatStr( _strText, "%d", nHP ));
    }
}
void CUIInfoMationDlg::SetScore( int32 nScore ){
    char _strText[1024];
    if( nScore != m_nScore ){
        m_nScore = nScore;
        m_pScoreLabel->SetText( FormatStr( _strText, "%d", nScore ) );
    }
}
void CUIInfoMationDlg::SetDistance( int32 nDistance, int32 nMaxDistance ){
    char _strText[1024];
    if( nDistance != m_nDistance || nMaxDistance != m_nMaxDistance ){
        m_nDistance = nDistance;
        m_nMaxDistance = nMaxDistance;
        m_pDistanceLabel->SetText( FormatStr( _strText, "%d/%d", nDistance, nMaxDistance ) );
    }
}