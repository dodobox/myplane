#ifndef __BOMEEFFECT_H__
#define __BOMEEFFECT_H__

#include "effect.h"

class CBomeEffect: public CEffect{
public:
    CBomeEffect();
    virtual ~CBomeEffect();
    virtual void Render();
    virtual bool Update();

};

#endif
