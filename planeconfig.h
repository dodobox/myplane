#ifndef __PLANECONFIG_H__
#define __PLANECONFIG_H__

#include "types.h"
#include "picture.h"
#include <vector>

#define MAXEMITTERPOINT (10)
class CPlaneInfo{
public:
    EPlaneType m_eType;
    struct{
        int32 m_nAnchorX;
        int32 m_nAnchorY;
        CPictureInfo* m_pPictureInfo;
    }m_tPicture;
    struct{
        EBulletEmitterType m_eEmitterType;
        TIntPoint m_vEmitterPoint[ MAXEMITTERPOINT ];
        int32 m_nEmitterPoint;
    }m_tEmitter;
};

class CPlaneConfig{
public:
    static CPlaneConfig* GetInterface();
    static void Release();
    CPlaneConfig();
    ~CPlaneConfig();
    void Init();
    void Final();
    CPlaneInfo* GetPlaneInfo( EPlaneType eType );

private:
    CPlaneInfo* m_vPlaneInfoList[EPT_COUNT];
};



#endif
