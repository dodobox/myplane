#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "types.h"

class CEffect: public CMemObject{
public:
    CEffect();
    virtual ~CEffect();
    virtual bool Init();
    virtual void Render();
    virtual bool Update();
};


#endif

