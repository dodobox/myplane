#include "uilabel.h"
#include "textlibrary.h"

CUILabel::CUILabel():
CUINode(){
    m_eUIType = EUT_LABEL;
}
CUILabel::~CUILabel(){

}
void CUILabel::Init(){
    CUINode::Init();
}
void CUILabel::Final(){
    CUINode::Final();
    m_vText.clear();
}
void CUILabel::SetText( char* strText ){
    m_vText.clear();
    char* _strText = strText;
    while( *_strText ){
        m_vText.push_back( *_strText );
        _strText++;
    }
    m_vText.push_back( 0 );
}
void CUILabel::Update( float fDelta ){
    CUINode::Update( fDelta );
}
void CUILabel::Draw( CCanvas* pCanvas ){
    CUINode::Draw( pCanvas );
    CTextLibrary::DrawText( pCanvas, m_tPositon.X, m_tPositon.Y, m_vText.data(), 0 );
}