#include "bullet0.h"
#include "bulletbehaviourcontrolmanager.h"
#include "picturemanager.h"

CBullet0::CBullet0():
CBulletBase(){
    m_eType = EBT_0;
    CBulletBase::InitBullet();
}
CBullet0::~CBullet0(){

}
void CBullet0::Init( int32 x, int32 y, ESpriteDirection eDirection, EBulletBehaviourType eBehaviourType, ESpriteCamp eCamp ){
    CBulletBase::Init( x, y, eDirection, eBehaviourType, eCamp );
}
void CBullet0::Final(){

}
void CBullet0::Draw( CCanvas* pCanvas ){
    CBulletBase::Draw( pCanvas );
}
bool CBullet0::Update( float fDelta ){
    CBulletBehaviourControlManager::GetInterface()->GetBehaviourControl( m_eBehaviourType )->Update( this, fDelta );
    return CBulletBase::Update( fDelta );
}