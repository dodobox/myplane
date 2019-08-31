#include "planeconfig.h"
#include "xml.h"
#include "picturemanager.h"
#include "utils.h"

static CPlaneConfig* _pThis = NULL;
CPlaneConfig* CPlaneConfig::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CPlaneConfig();
        _pThis->Init();
    }
    return _pThis;
}
void CPlaneConfig::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CPlaneConfig::CPlaneConfig(){
    for( int32 i = 0; i < EPT_COUNT; i ++ ){
        m_vPlaneInfoList[i] = NULL;
    }
}
CPlaneConfig::~CPlaneConfig(){

}
void CPlaneConfig::Init(){
    char _strText[1024];
    CXMLDocment _tXMLDoc( "planes.xml" );
    CXMLNode _tRoot = _tXMLDoc.GetNode( "planes" );
    CXMLNode _tNode = _tRoot.GetFirstNode();
    while( _tNode.Vaild() ){
        int32 _nType = _tNode.GetAttributeInt32Value( "type" );
        CPlaneInfo* _pPlaneInfo = NEW CPlaneInfo();
       // _pPlaneInfo->m_eEmitterType = (EBulletEmitterType)_tNode.GetAttributeInt32Value( "emitter" );
        CXMLNode _tPictureNode = _tNode.GetNode( "picture" );
        _pPlaneInfo->m_tPicture.m_nAnchorX = _tPictureNode.GetAttributeInt32Value( "anchorx" );
        _pPlaneInfo->m_tPicture.m_nAnchorY = _tPictureNode.GetAttributeInt32Value( "anchory" );
        const char* _strFileName = _tPictureNode.GetAttributeValue("filename");
        FormatStr( _strText, "planes/%s", _strFileName );
        _pPlaneInfo->m_tPicture.m_pPictureInfo = CPictureManager::GetInterface()->GetPicture( _strText );
        CXMLNode _tEmitterNode = _tNode.GetNode( "emitter" );
        _pPlaneInfo->m_tEmitter.m_eEmitterType = (EBulletEmitterType)_tEmitterNode.GetAttributeInt32Value("type");
        _pPlaneInfo->m_tEmitter.m_nEmitterPoint = 0;
        CXMLNode _tEmitterPointNode = _tEmitterNode.GetFirstNode();
        while( _tEmitterPointNode.Vaild() ){
            _pPlaneInfo->m_tEmitter.m_vEmitterPoint[_pPlaneInfo->m_tEmitter.m_nEmitterPoint].X = _tEmitterPointNode.GetAttributeInt32Value( "x" );
            _pPlaneInfo->m_tEmitter.m_vEmitterPoint[_pPlaneInfo->m_tEmitter.m_nEmitterPoint].Y = _tEmitterPointNode.GetAttributeInt32Value( "y" );
            _pPlaneInfo->m_tEmitter.m_nEmitterPoint ++;
            _tEmitterPointNode = _tEmitterPointNode.GetNextNode();
        }

        m_vPlaneInfoList[ _nType ] = _pPlaneInfo;
        _tNode = _tNode.GetNextNode();
    }

}
void CPlaneConfig::Final(){

}
CPlaneInfo* CPlaneConfig::GetPlaneInfo( EPlaneType eType ){
    return m_vPlaneInfoList[ eType ];
}