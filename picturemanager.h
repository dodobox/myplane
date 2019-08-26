#ifndef __PICTUERMANAGER_H__
#define __PICTUERMANAGER_H__

#include "picture.h"
#include <vector>

class CPictureManager{
public:
    static CPictureManager* GetInterface();
    static void Release();
    CPictureManager();
    ~CPictureManager();

    void Init();
    void Final();
   // CPictureInfo* GetPicture( const char* strFileName );

    std::vector< CPictureInfo* > m_vPictureInfoList;
};



#endif
