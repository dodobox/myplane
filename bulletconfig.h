#ifndef __BULLETCONFIG_H__
#define __BULLETCONFIG_H__

#include "types.h"
#include "picture.h"
#include <vector>

class CBulletInfo: public CMemObject{
public:
    EBulletType m_eType;
    struct{
        int32 m_nAnchorX;
        int32 m_nAnchorY;
        CPictureInfo* m_pPictureInfo;
    }m_tPicture;
};

class CBulletConfig: public CMemObject{
public:
    static CBulletConfig* GetInterface();
    static void Release();
    CBulletConfig();
    ~CBulletConfig();
    void Init();
    void Final();
    CBulletInfo* GetBulletInfo( EBulletType eType );

private:
    CBulletInfo* m_vBulletInfoList[EPT_COUNT];
};



#endif
