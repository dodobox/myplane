#ifndef __PICTUERMANAGER_H__
#define __PICTUERMANAGER_H__

#include "picture.h"
#include <map>

class CPictureManager{
public:
    static CPictureManager* GetInterface();
    static void Release();
    CPictureManager();
    ~CPictureManager();
    void Init();
    void Final();
    CPictureInfo* GetPicture( const char* strFileName );

private:
    std::map< uint32, CPictureInfo* > m_vPictureInfoList;
};



#endif
