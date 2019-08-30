#include "background.h"
#include "picturemanager.h"
#include "utils.h"

//#define MAXSCREENHEIGHT (110.0f)

CBackGround::CBackGround(){
    m_nTileIndex = 0;
    m_fSpeed = 1.0f;
}
CBackGround::~CBackGround(){

}
void CBackGround::Init( CXMLNode *pNode ){
    CXMLNode _tPicturesNode = pNode->GetNode( "pictures" );
    CXMLNode _tPicNode = _tPicturesNode.GetFirstNode();
    while( _tPicNode.Vaild() ){
        const char* _strFileName = _tPicNode.GetAttributeValue( "filename" );
        CPictureInfo* _pPictureInfo = CPictureManager::GetInterface()->GetPicture( _strFileName );
        m_vPictureList.push_back( _pPictureInfo );
        _tPicNode = _tPicNode.GetNextNode();
    }

    CXMLNode _tMapsNode = pNode->GetNode( "maps" );
    m_fSpeed = _tMapsNode.GetAttributeFloatValue("scrollspeed");
    CXMLNode _tTileNode = _tMapsNode.GetFirstNode();
    while( _tTileNode.Vaild() ){
        CStageTileInfo _tStageTileInfo;
        CXMLNode _tTilePicturesNode = _tTileNode.GetNode("pictures");
        CXMLNode _tTilePicNode = _tTilePicturesNode.GetFirstNode();
        int32 _nIndex = 0;
        while( _tTilePicNode.Vaild() ){
             if( _nIndex < MAXPICTUREID ){
                 _tStageTileInfo.m_vPictureIDs[_nIndex] = _tTilePicNode.GetAttributeInt32Value( "id" );
                 _tStageTileInfo.m_nPicture = _nIndex + 1;
             }
             _nIndex ++;
            _tTilePicNode = _tTilePicNode.GetNextNode();
        }
        m_vTileInfoList.push_back( _tStageTileInfo );
        _tTileNode = _tTileNode.GetNextNode();
    }

    ////////////////////////////////////////
    InitScrollItems();
    
}
void CBackGround::Final(){
    for( auto it = m_vPictureList.begin(); it != m_vPictureList.end(); it ++ ){
        CPictureManager::GetInterface()->Remove( *it );
    }
    m_vPictureList.clear();
    m_vTileInfoList.clear();
}
void CBackGround::Update( float fDelta ){
    float _fDeltaDistance = m_fSpeed * fDelta;
    UpdateScrollQueue( _fDeltaDistance );
}
void CBackGround::Draw( CCanvas* pCanvas ){
    for( auto it = m_vScrollQueue.begin(); it != m_vScrollQueue.end(); it ++ ){
        TScrollItemInfo* _pScrollItemInfo = &(*it);
        pCanvas->DrawRect( _pScrollItemInfo->m_fLeft,
                           _pScrollItemInfo->m_fTop,
                           _pScrollItemInfo->m_pPictureInfo->m_nWidth,
                           _pScrollItemInfo->m_pPictureInfo->m_nHeight,
                           (uint32*)_pScrollItemInfo->m_pPictureInfo->m_pData );
    }
}
void CBackGround::InitScrollItems(){
    int32 _nScrollTop = CCanvas::m_tCanvasSize.Y;
    while( _nScrollTop > 0.0f ){
        //添加第一张图片
        CPictureInfo* _pPictureInfo = GetNextPictureInfo();
        _nScrollTop -= _pPictureInfo->m_nHeight;
        TScrollItemInfo _tScrollItemInfo;
        _tScrollItemInfo.m_fLeft = 0.0f;
        _tScrollItemInfo.m_fTop = _nScrollTop;
        _tScrollItemInfo.m_pPictureInfo = _pPictureInfo;
        m_vScrollQueue.push_back( _tScrollItemInfo );
    }
}
CPictureInfo* CBackGround::GetNextPictureInfo(){
    int32 _nTileIndex = m_nTileIndex % m_vTileInfoList.size();
    m_nTileIndex ++;
    CStageTileInfo* _pStageTileInfo = &(m_vTileInfoList[_nTileIndex]);
    int32 _nPictureID = _pStageTileInfo->m_vPictureIDs[Rand( _pStageTileInfo->m_nPicture )];
    CPictureInfo* _pPictureInfo = m_vPictureList[_nPictureID];
    return _pPictureInfo;
}
void CBackGround::UpdateScrollQueue( float fDeltaDistance ){
    float _fMinScrollItemTop = 9999.0f;
    for( auto it = m_vScrollQueue.begin(); it != m_vScrollQueue.end(); ){
        TScrollItemInfo* _pScrollItemInfo = &(*it);
        _pScrollItemInfo->m_fTop += fDeltaDistance;
        if( _pScrollItemInfo->m_fTop > CCanvas::m_tCanvasSize.Y ){   //移出了屏幕的
            it = m_vScrollQueue.erase( it );
        } else{
            _fMinScrollItemTop = Min<float>( _fMinScrollItemTop, _pScrollItemInfo->m_fTop );
            it ++;
        }
    }

    //添加图片
    while( _fMinScrollItemTop > 0.0f ){//不够了
        CPictureInfo* _pPictureInfo = GetNextPictureInfo();
        _fMinScrollItemTop = _fMinScrollItemTop - _pPictureInfo->m_nHeight;
        TScrollItemInfo _tScrollItemInfo;
        _tScrollItemInfo.m_fLeft = 0.0f;
        _tScrollItemInfo.m_fTop = _fMinScrollItemTop;
        _tScrollItemInfo.m_pPictureInfo = _pPictureInfo;
        m_vScrollQueue.push_back( _tScrollItemInfo );
    }
}
