#include "collisionmap.h"
#include "canvas.h"
#include "plane.h"
#include <memory>

static CCollisionMap* _pThis = NULL;
CCollisionMap* CCollisionMap::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CCollisionMap();
        _pThis->Init( CCanvas::m_tCanvasSize.X, CCanvas::m_tCanvasSize.Y );
    }
    return _pThis;
}
void CCollisionMap::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}

CCollisionMap::CCollisionMap(){
    m_ppCollisionMap[EPC_RED] = NULL;
    m_ppCollisionMap[EPC_BLUE] = NULL;
}
CCollisionMap::~CCollisionMap(){

}
void CCollisionMap::Init( int32 x, int32 y ){
    m_tSize = { x, y };
    m_ppCollisionMap[EPC_RED] = NEW2DARRAY( CPlane*, x, y );
    m_ppCollisionMap[EPC_BLUE] = NEW2DARRAY( CPlane*, x, y );
    Clear();
}
void CCollisionMap::Final(){
    DELETE2DARRAY( CPlane*, m_ppCollisionMap[EPC_RED] );
    DELETE2DARRAY( CPlane*, m_ppCollisionMap[EPC_BLUE] );
}
void CCollisionMap::Clear(){
    memset( m_ppCollisionMap[EPC_RED][0], 0, sizeof( CPlane* ) * m_tSize.X * m_tSize.Y );
    memset( m_ppCollisionMap[EPC_BLUE][0], 0, sizeof( CPlane* ) * m_tSize.X * m_tSize.Y );
}
bool CCollisionMap::SetPixel( int32 x, int32 y, CPlane* pPlane ){
    if( x < 0 || x >= m_tSize.X || y < 0 || y >= m_tSize.Y )return false;
    m_ppCollisionMap[ pPlane->m_eCamp ][y][x] = pPlane;
}
CPlane* CCollisionMap::GetPixel( ESpriteCamp eCamp, int32 x, int32 y ){
    if( x < 0 || x >= m_tSize.X || y < 0 || y >= m_tSize.Y )return NULL;
    return m_ppCollisionMap[eCamp][y][x];

}