#ifndef __BULLETEMITTERMANAGER_H__
#define __BULLETEMITTERMANAGER_H__

#include "types.h"
#include "bulletemitter.h"

class CBulletMitterManager: public CMemObject{
public:
    static CBulletMitterManager* GetInterface();
    static void Release();
    CBulletMitterManager();
    virtual ~CBulletMitterManager();
    void Init();
    void Final();
    CBulletEmitter* GetEmitter( EBulletEmitterType eEmitter );

private:
    CBulletEmitter* m_vEmitterList[ EBET_COUNT ];
};


#endif

