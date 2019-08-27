#include "plane0.h"
#include "behaviourcontrolmanager.h"
#include "picturemanager.h"

CPlane0::CPlane0():
CPlane(){
    m_eType = EPT_TYPE0;
    m_pPlaneInfo = CPlaneConfig::GetInterface()->GetPlaneInfo( m_eType );
    m_fAP = m_pPlaneInfo->m_tAttribute.m_nAP;
    m_fDP = m_pPlaneInfo->m_tAttribute.m_nDP;
    m_fSpeed = m_pPlaneInfo->m_tAttribute.m_fSpeed;
    m_nHP = m_pPlaneInfo->m_tAttribute.m_nHP;
}
CPlane0::~CPlane0(){

}
void CPlane0::Init( int32 x, int32 y, EPlaneDirection eDirection, EBehaviourType eBehaviourType, EPlaneCamp eCamp ){
    m_tPosition = { (float)x, (float)y };
    m_eCamp = eCamp;
    m_eBehaviourType = eBehaviourType;
    m_eDirection = eDirection;

    m_pPictureInfo = m_pPlaneInfo->m_tPicture.m_pPictureInfo;
    m_nPictureAnchorX = m_pPlaneInfo->m_tPicture.m_nAnchorX;
    m_nPictureAnchorY = m_pPlaneInfo->m_tPicture.m_nAnchorY;
}
void CPlane0::Final(){

}
void CPlane0::Draw( CCanvas* pCanvas ){
    int32 _nShapeWidth = m_pPictureInfo->m_nWidth;
    int32 _nShapeHeight = m_pPictureInfo->m_nHeight;
    int32 _nAnchorLeft = m_nPictureAnchorX;
    int32 _nAnchorTop = m_nPictureAnchorY;
    uint32* _pData = (uint32*)m_pPictureInfo->m_pData;
    CPlane::DrawPlane( pCanvas, m_tPosition.X, m_tPosition.Y, m_eDirection, _nShapeWidth, _nShapeHeight, _nAnchorLeft, _nAnchorTop, _pData );
}
bool CPlane0::Update( float fDelta ){
    CBehaviourControlManager::GetInterface()->GetBehaviourControl( m_eBehaviourType )->Update( this, fDelta );
    return true;
}