#include "behaviour0control.h"
#include "plane.h"


CBehaviour0Control::CBehaviour0Control():
CBehaviourControl(){
    m_eBehaviourType = EPBT_TYPE0;
}
CBehaviour0Control::~CBehaviour0Control(){

}
void CBehaviour0Control::Init(){

}
void CBehaviour0Control::Final(){

}
void CBehaviour0Control::Update( CPlane* pPlane, float fDelta ){
    pPlane->m_tPosition.Y += pPlane->m_fSpeed * fDelta;
}