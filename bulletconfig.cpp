#include "bulletconfig.h"
#include "xml.h"
#include "picturemanager.h"
#include "utils.h"

static CBulletConfig* _pThis = NULL;
CBulletConfig* CBulletConfig::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CBulletConfig();
        _pThis->Init();
    }
    return _pThis;
}
void CBulletConfig::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CBulletConfig::CBulletConfig(){
    for( int32 i = 0; i < EPT_COUNT; i ++ ){
        m_vBulletInfoList[i] = NULL;
    }
}
CBulletConfig::~CBulletConfig(){

}
void CBulletConfig::Init(){
    char _strText[1024];
    CXMLDocment _tXMLDoc( "bullets.xml" );
    CXMLNode _tRoot = _tXMLDoc.GetNode( "bullets" );
    CXMLNode _tNode = _tRoot.GetFirstNode();
    while( _tNode.Vaild() ){
        int32 _nType = _tNode.GetAttributeInt32Value( "type" );
        CBulletInfo* _pBulletInfo = NEW CBulletInfo();
        CXMLNode _tPictureNode = _tNode.GetNode( "picture" );
        _pBulletInfo->m_tPicture.m_nAnchorX = _tPictureNode.GetAttributeInt32Value( "anchorx" );
        _pBulletInfo->m_tPicture.m_nAnchorY = _tPictureNode.GetAttributeInt32Value( "anchory" );
        const char* _strFileName = _tPictureNode.GetAttributeValue( "filename" );
        FormatStr( _strText, "bullets/%s", _strFileName );
        _pBulletInfo->m_tPicture.m_pPictureInfo = CPictureManager::GetInterface()->GetPicture( _strText );

        m_vBulletInfoList[_nType] = _pBulletInfo;
        _tNode = _tNode.GetNextNode();
    }

}
void CBulletConfig::Final(){

}
CBulletInfo* CBulletConfig::GetBulletInfo( EBulletType eType ){
    return m_vBulletInfoList[eType];
}