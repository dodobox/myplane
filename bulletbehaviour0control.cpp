#include "bulletbehaviour0control.h"
#include "bulletbase.h"


CBulletBehaviour0Control::CBulletBehaviour0Control():
CBulletBehaviourControl(){
    m_eBehaviourType = EBBT_0;
}
CBulletBehaviour0Control::~CBulletBehaviour0Control(){

}
void CBulletBehaviour0Control::Init(){

}
void CBulletBehaviour0Control::Final(){

}
void CBulletBehaviour0Control::Update( CBulletBase* pBullet, float fDelta ){
    float _fSpeed = pBullet->m_fSpeed * fDelta;
    float _fX = pBullet->m_tPosition.X + pBullet->m_tNormal.X * _fSpeed;
    float _fY = pBullet->m_tPosition.Y + pBullet->m_tNormal.Y * _fSpeed;
    pBullet->SetPosition( _fX, _fY );
}