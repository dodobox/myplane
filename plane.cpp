#include "plane.h"

CPlane::CPlane():
m_nID( -1 ),
m_pPlaneInfo( NULL ),
m_eCamp( EPC_UNKOWN ),
m_eType( EPT_UNKOWN ),
m_eBehaviourType( EBT_UNKOWN ),
m_eDirection( EPD_UNKOWN ),
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

void CPlane::DrawPlane( CCanvas* pCanvas, int32 x, int32 y, EPlaneDirection eDirection, int32 nShapeWidth, int32 nShapeHeight, int32 nAnchorLeft, int32 nAnchorTop, uint32 *pShape ){

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
                if( pShape[j * nShapeWidth + i] > 0xff000000 ){
                    pCanvas->SetPixel( _nX + i, _nY - j, 1 );
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
                if( pShape[j * nShapeWidth + i] != 0 ){
                    pCanvas->SetPixel( _nX + i, _nY + j, 1 );
                }
            }
        }
    }break;
    }
}