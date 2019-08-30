#ifndef __PLANE0_H__
#define __PLANE0_H__

#include "plane.h"
#include "picture.h"

class CPlane0: public CPlane{
public:
    CPlane0();
    virtual ~CPlane0();
    virtual void Init( int32 x, int32 y, CStagePlaneInstInfo* pStagePlaneInstInfo );
    virtual void Final();
    virtual void Draw( CCanvas* pCanvas );
    virtual bool Update( float fDelta );
    virtual void Fire( int32 nType );

    float m_fFireTime;

};


#endif
