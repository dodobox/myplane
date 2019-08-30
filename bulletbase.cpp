#include "bulletbase.h"
#include "utils.h"

CBulletBase::CBulletBase():
m_nID( -1 ),
m_pBulletInfo( NULL ),
m_tPosDimension{0,0,0,0},
m_eCamp( EPC_UNKOWN ),
m_eType( EBT_UNKOWN ),
m_eBehaviourType( EBBT_UNKOWN ),
m_eDirection( EPD_UNKOWN ),
m_tPosition{ 0, 0 },
m_tOriginPositon{ 0, 0 },
m_tNormal{ 0, 0 },
m_bLife( true ),
m_fAP( 0 ),
m_fSpeed( 0 ){
    static int32 _nID = 0;
    m_nID = _nID++;

}
CBulletBase::~CBulletBase(){

}
void CBulletBase::InitBullet(){
    m_pBulletInfo = CBulletConfig::GetInterface()->GetBulletInfo( m_eType );

    m_tPosDimension.m_nLeft = m_pBulletInfo->m_tPicture.m_nAnchorX;
    m_tPosDimension.m_nTop = m_pBulletInfo->m_tPicture.m_nAnchorY;
    m_tPosDimension.m_nRight = m_pBulletInfo->m_tPicture.m_pPictureInfo->m_nWidth - m_pBulletInfo->m_tPicture.m_nAnchorX;
    m_tPosDimension.m_nBottom = m_pBulletInfo->m_tPicture.m_pPictureInfo->m_nHeight - m_pBulletInfo->m_tPicture.m_nAnchorY;
}
void CBulletBase::Init( int32 x, int32 y, ESpriteDirection eDirection, EBulletBehaviourType eBehaviourType, ESpriteCamp eCamp ){
    m_tPosition = { (float)x, (float)y };
    m_tOriginPositon = { (float)x, (float)y };
    m_eCamp = eCamp;
    m_eBehaviourType = eBehaviourType;
    m_eDirection = eDirection;
}
void CBulletBase::Final(){

}
void CBulletBase::SetPosition( float x, float y ){
    m_tOriginPositon.X = m_tPosition.X;
    m_tOriginPositon.Y = m_tPosition.Y;
    m_tPosition.X = x;
    m_tPosition.Y = y;
}
void CBulletBase::SetNormal( float x, float y ){
    m_tNormal = { x, y };
}
bool CBulletBase::Update( float fDelta ){
    if( !m_bLife ){
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
void CBulletBase::Draw( CCanvas* pCanvas ){
    if( !m_bLife ){
        return;
    }
    int32 _nShapeWidth = m_pBulletInfo->m_tPicture.m_pPictureInfo->m_nWidth;
    int32 _nShapeHeight = m_pBulletInfo->m_tPicture.m_pPictureInfo->m_nHeight;
    int32 _nAnchorLeft = m_pBulletInfo->m_tPicture.m_nAnchorX;
    int32 _nAnchorTop = m_pBulletInfo->m_tPicture.m_nAnchorY;
    uint32* _pData = (uint32*)m_pBulletInfo->m_tPicture.m_pPictureInfo->m_pData;
    DrawBullet( pCanvas, m_tPosition.X, m_tPosition.Y, m_eDirection, _nShapeWidth, _nShapeHeight, _nAnchorLeft, _nAnchorTop, _pData );
}
void CBulletBase::DrawBullet( CCanvas* pCanvas, int32 x, int32 y, ESpriteDirection eDirection, int32 nShapeWidth, int32 nShapeHeight, int32 nAnchorLeft, int32 nAnchorTop, uint32 *pShape ){
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
                pCanvas->SetPixel( _nX + i, _nY - j, pShape[j * nShapeWidth + i] );
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
                pCanvas->SetPixel( _nX + i, _nY + j, pShape[j * nShapeWidth + i] );
            }
        }
    }break;
    }
}