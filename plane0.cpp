#include "plane0.h"
#include "behaviourcontrolmanager.h"
#include "picturemanager.h"

//static const int32 m_nShapeWidth = 10;
//static const int32 m_nShapeHeight = 10;
//static const int32 m_nAnchorLeft = 4;
//static const int32 m_nAnchorTop = 2;
//static int32 m_vShape[ m_nShapeHeight ][ m_nShapeWidth ]{
//    { 0,0,0,0,1,0,0,0,0,0 },
//    { 0,0,0,0,1,0,0,0,0,0 },
//    { 1,1,1,1,1,1,1,1,1,0 },
//    { 0,0,0,0,1,0,0,0,0,0 },
//    { 0,0,0,0,1,0,0,0,0,0 },
//    { 0,0,1,1,0,1,1,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0 },
//};


CPlane0::CPlane0():
CPlane(){
    m_eType = EPT_TYPE0;
    m_fAP = 10.0f;
    m_fDP = 10.0f;
    m_fSpeed = 10.0f;
    m_nHP = 100;
}
CPlane0::~CPlane0(){

}
void CPlane0::Init( int32 x, int32 y, EPlaneDirection eDirection, EBehaviourType eBehaviourType, EPlaneCamp eCamp ){
    m_tPosition = { (float)x, (float)y };
    m_eCamp = eCamp;
    m_eBehaviourType = eBehaviourType;
    m_eDirection = eDirection;

    m_pPictureInfo = CPictureManager::GetInterface()->m_vPictureInfoList[ 0 ];

}
void CPlane0::Final(){

}
void CPlane0::Draw( CCanvas* pCanvas ){
    int32 _nShapeWidth = m_pPictureInfo->m_nWidth;
    int32 _nShapeHeight = m_pPictureInfo->m_nHeight;
    int32 _nAnchorLeft = 0;
    int32 _nAnchorTop = 0;
    uint32* _pData = (uint32*)m_pPictureInfo->m_pData;

    

    CPlane::DrawPlane( pCanvas, m_tPosition.X, m_tPosition.Y, m_eDirection, _nShapeWidth, _nShapeHeight, _nAnchorLeft, _nAnchorTop, _pData );
}
bool CPlane0::Update( float fDelta ){
    CBehaviourControlManager::GetInterface()->GetBehaviourControl( m_eBehaviourType )->Update( this, fDelta );
    return true;
}