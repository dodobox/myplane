#include "plane1.h"
#include "behaviourcontrolmanager.h"

static const int32 m_nShapeWidth = 10;
static const int32 m_nShapeHeight = 10;
static const int32 m_nAnchorLeft = 4;
static const int32 m_nAnchorTop = 2;
static uint32 m_vShape[ m_nShapeHeight ][ m_nShapeWidth ]{
    { 0,0,0,0,1,0,0,0,0,0 },
    { 0,0,0,0,1,0,0,0,0,0 },
    { 0,0,1,1,1,1,1,0,0,0 },
    { 0,1,0,0,1,0,0,1,0,0 },
    { 0,0,0,1,0,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0 },
};


CPlane1::CPlane1():
CPlane(){
    m_eType = EPT_TYPE1;
    m_fAP = 10.0f;
    m_fDP = 10.0f;
    m_fSpeed = 10.0f;
    m_nHP = 100;
}
CPlane1::~CPlane1(){

}
void CPlane1::Init( int32 x, int32 y, EPlaneDirection eDirection, EBehaviourType eBehaviourType, EPlaneCamp eCamp ){
    m_tPosition = { (float)x, (float)y };
    m_eCamp = eCamp;
    m_eBehaviourType = eBehaviourType;
    m_eDirection = eDirection;
}
void CPlane1::Final(){

}
void CPlane1::Draw( CCanvas* pCanvas ){
    CPlane::DrawPlane( pCanvas, m_tPosition.X, m_tPosition.Y, m_eDirection, m_nShapeWidth, m_nShapeHeight, m_nAnchorLeft, m_nAnchorTop, m_vShape[0] );
}
bool CPlane1::Update( float fDelta ){
    CBehaviourControlManager::GetInterface()->GetBehaviourControl( m_eBehaviourType )->Update( this, fDelta );
    return true;
}