#ifndef __EFFECTMANAGER_H__
#define __EFFECTMANAGER_H__

#include "types.h"

class CEffectManager{
public:
    static CEffectManager* GetInterface();
    static void Release();
    CEffectManager();
    virtual ~CEffectManager();
    virtual void Draw();
    virtual void Update( float td );
    bool PlayEffect( EEffectType eType, float x, float y );
private:

};


#endif

