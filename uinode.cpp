#include "uinode.h"

CUINode::CUINode():
m_eUIType(EUT_NODE),
m_bVisible( true ),
m_tPositon{ 0,0 }{

}
CUINode::~CUINode(){

}
void CUINode::Init(){

}
void CUINode::Final(){
    Clear();
}
void CUINode::SetPosition( int32 x, int32 y ){
    m_tPositon = { x,y };
}
void CUINode::Clear(){
    for( auto it = m_vNodeList.begin(); it != m_vNodeList.end(); it ++ ){
        CUINode* _pNode = *it;
        DELETE( _pNode );
    }
    m_vNodeList.clear();
}
void CUINode::AddChild( CUINode* pNode ){
    m_vNodeList.push_back( pNode );
}
void CUINode::Update( float fDelta ){
    for( auto it = m_vNodeList.begin(); it != m_vNodeList.end(); it ++ ){
        CUINode* _pNode = *it;
        _pNode->Update( fDelta );
    }
}
void CUINode::Draw( CCanvas* pCanvas ){
    for( auto it = m_vNodeList.begin(); it != m_vNodeList.end(); it ++ ){
        CUINode* _pNode = *it;
        _pNode->Draw( pCanvas );
    }
}


