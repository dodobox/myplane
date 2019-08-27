#ifndef __PLANECONFIG_H__
#define __PLANECONFIG_H__

#include "types.h"
#include "picture.h"
#include <vector>

class CPlaneInfo{
public:
    EPlaneType m_eType;
    struct{
        int32 m_nAnchorX;
        int32 m_nAnchorY;
        CPictureInfo* m_pPictureInfo;
    }m_tPicture;
    struct{
        int32 m_nAP;
        int32 m_nDP;
        float m_fSpeed;
        int32 m_nHP;
    }m_tAttribute;
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