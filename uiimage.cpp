#include "uiimage.h"

CUIImage::CUIImage():
CUINode(),
m_pPicture( NULL ){
    m_eUIType = EUT_IMAGE;
}
CUIImage::~CUIImage(){

}
void CUIImage::Init(){
    CUINode::Init();
}
void CUIImage::Final(){
    CUINode::Final();
}
void CUIImage::SetImage( const char* strFileName ){
    m_pPicture = CPictureManager::GetInterface()->GetPicture( strFileName );
}
void CUIImage::Update( float fDelta ){
    CUINode::Update( fDelta );
}
void CUIImage::Draw( CCanvas* pCanvas ){
    CUINode::Draw( pCanvas );
    if( m_pPicture ){
        pCanvas->DrawRect( m_tPositon.X, m_tPositon.Y, m_pPicture->m_nWidth, m_pPicture->m_nHeight, (uint32*)m_pPicture->m_pData );
    }
}