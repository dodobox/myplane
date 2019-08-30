#include "plane1.h"
#include "behaviourcontrolmanager.h"

CPlane1::CPlane1():
CPlane(){
    m_eType = EPT_TYPE1;
    CPlane::InitPlane();
}
CPlane1::~CPlane1(){

}
void CPlane1::Init( int32 x, int32 y, CStagePlaneInstInfo* pStagePlaneInstInfo ){
    CPlane::Init( x, y, pStagePlaneInstInfo );
}
void CPlane1::Final(){

}
void CPlane1::Draw( CCanvas* pCanvas ){
    CPlane::Draw( pCanvas );
}
bool CPlane1::Update( float fDelta ){
    CBehaviourControlManager::GetInterface()->GetBehaviourControl( m_eBehaviourType )->Update( this, fDelta );
    return CPlane::Update( fDelta );
}