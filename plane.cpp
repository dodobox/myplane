#include "plane.h"
#include "utils.h"
#include "collisionmap.h"

CPlane::CPlane():
m_nID( -1 ),
m_pPlaneInfo( NULL ),
m_pStagePlaneInstInfo( NULL ),
m_eCamp( EPC_UNKOWN ),
m_eType( EPT_UNKOWN ),
m_eBehaviourType( EPBT_UNKOWN ),
m_eDirection( EPD_UNKOWN ),
m_eEmitterType( EBET_UNKOWN ),
m_tPosition{ 0, 0 },
m_fAP( 0 ),
m_fDP( 0 ),
m_fSpeed( 0 ),
m_nHP( 0 ){
    static int32 _nID = 0;
    m_nID = _nID++;
}

CPlane::~CPlane(){

}

void CPlane::InitPlane(){
    m_pPlaneInfo = CPlaneConfig::GetInterface()->GetPlaneInfo( m_eType );
    m_eEmitterType = m_pPlaneInfo->m_tEmitter.m_eEmitterType;
    m_tPosDimension.m_nLeft = m_pPlaneInfo->m_tPicture.m_nAnchorX;
    m_tPosDimension.m_nTop = m_pPlaneInfo->m_tPicture.m_nAnchorY;
    m_tPosDimension.m_nRight = m_pPlaneInfo->m_tPicture.m_pPictureInfo->m_nWidth - m_pPlaneInfo->m_tPicture.m_nAnchorX;
    m_tPosDimension.m_nBottom = m_pPlaneInfo->m_tPicture.m_pPictureInfo->m_nHeight - m_pPlaneInfo->m_tPicture.m_nAnchorY;
}
void CPlane::Init( int32 x, int32 y, CStagePlaneInstInfo* pStagePlaneInstInfo ){
    m_tPosition = { (float)x, (float)y };
    m_pStagePlaneInstInfo = pStagePlaneInstInfo;
    m_eCamp = pStagePlaneInstInfo->m_ePlaneCamp;
    m_eBehaviourType = pStagePlaneInstInfo->m_eBehaviourType;
    m_eDirection = pStagePlaneInstInfo->m_ePlaneDirection;
    m_fAP = (float)pStagePlaneInstInfo->m_tAttribute.m_nAP;
    m_fDP = (float)pStagePlaneInstInfo->m_tAttribute.m_nDP;
    m_fSpeed = pStagePlaneInstInfo->m_tAttribute.m_fSpeed;
    m_nHP = pStagePlaneInstInfo->m_tAttribute.m_nHP;
}

bool CPlane::Update( float fDelta ){
    if( m_nHP <= 0 ){
        return false;
    }
    
    float _fLeft = m_tPosition.X + m_tPosDimension.m_nLeft;
    float _fTop = m_tPosition.Y + m_tPosDimension.m_nTop;
    float _fRight = m_tPosition.X + m_tPosDimension.m_nRight;
    float _fBottom = m_tPosition.Y + m_tPosDimension.m_nBottom;
        
    bool _bIntersect = RectIntersectRect<float>( _fLeft, _fTop, _fRight, _fBottom, CCanvas::m_tSceneActiveRect.m_nLeft, CCanvas::m_tSceneActiveRect.m_nTop, CCanvas::m_tSceneActiveRect.m_nRight, CCanvas::m_tSceneActiveRect.m_nBottom );
    if( !_bIntersect ){
        return false;
    }

    return true;
}

void CPlane::Draw( CCanvas* pCanvas ){
    int32 _nShapeWidth = m_pPlaneInfo->m_tPicture.m_pPictureInfo->m_nWidth;
    int32 _nShapeHeight = m_pPlaneInfo->m_tPicture.m_pPictureInfo->m_nHeight;
    int32 _nAnchorLeft = m_pPlaneInfo->m_tPicture.m_nAnchorX;
    int32 _nAnchorTop = m_pPlaneInfo->m_tPicture.m_nAnchorY;
    uint32* _pData = (uint32*)m_pPlaneInfo->m_tPicture.m_pPictureInfo->m_pData;
    DrawPlane( pCanvas, m_tPosition.X, m_tPosition.Y, m_eDirection, _nShapeWidth, _nShapeHeight, _nAnchorLeft, _nAnchorTop, _pData );
}

void CPlane::DrawPlane( CCanvas* pCanvas, int32 x, int32 y, ESpriteDirection eDirection, int32 nShapeWidth, int32 nShapeHeight, int32 nAnchorLeft, int32 nAnchorTop, uint32 *pShape ){
    CCollisionMap* _pCollisionMap = CCollisionMap::GetInterface();
    switch( eDirection ){
    case EPD_E:{
        int32 _nX = x - nAnchorLeft;
        int32 _nY = y - nAnchorTop;
        for( int32 j = 0; j < nShapeHeight; j ++ ){
            for( int32 i = 0; i < nShapeWidth; i ++ ){
                if( pShape[j * nShapeWidth + i] != 0 ){
                    pCanvas->SetPixel( _nX + i, _nY + j, 1 );
                }
            }
        }
    }break;
    case EPD_S:{
        int32 _nX = x - nAnchorLeft;
        int32 _nY = y + nAnchorTop;
        for( int32 j = 0; j < nShapeHeight; j ++ ){
            for( int32 i = 0; i < nShapeWidth; i ++ ){
                if( pCanvas->SetPixel( _nX + i, _nY - j, pShape[j * nShapeWidth + i] ) ){
                    _pCollisionMap->SetPixel( _nX + i, _nY - j, this );
                }
            }
        }
    }break;
    case EPD_W:{
        int32 _nX = x - nAnchorLeft;
        int32 _nY = y - nAnchorTop;
        for( int32 j = 0; j < nShapeHeight; j ++ ){
            for( int32 i = 0; i < nShapeWidth; i ++ ){
                if( pShape[j * nShapeWidth + i] != 0 ){
                    pCanvas->SetPixel( _nX + i, _nY + j, 1 );
                }
            }
        }
    }break;
    case EPD_N:{
        int32 _nX = x - nAnchorLeft;
        int32 _nY = y - nAnchorTop;
        for( int32 j = 0; j < nShapeHeight; j ++ ){
            for( int32 i = 0; i < nShapeWidth; i ++ ){
                if( pCanvas->SetPixel( _nX + i, _nY + j, pShape[j * nShapeWidth + i] ) ){
                    _pCollisionMap->SetPixel( _nX + i, _nY + j, this );
                }
            }
        }
    }break;
    }
}
void CPlane::Fire( int32 nType ){

}