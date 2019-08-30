#ifndef __BULLETMANAGER_H__
#define __BULLETMANAGER_H__

#include "canvas.h"
#include "bulletbase.h"
#include <list>

class CBulletManager{
public:
    static CBulletManager* GetInterface();
    static void Release();
    CBulletManager();
    virtual ~CBulletManager();
    virtual void Init();
    virtual void Final();
    virtual void Update( float fDelta );
    virtual void Draw( CCanvas* pCanvas );
    virtual void AddBullet( CBulletBase* pBullet );
    virtual CBulletBase* AddBullet( EBulletType eType, int32 x, int32 y, ESpriteDirection eDirection, EBulletBehaviourType eBehaviourType, ESpriteCamp eCamp );
    void CheckCollision();
private:
    std::list<CBulletBase*> m_vBulletList;
};


#endif
