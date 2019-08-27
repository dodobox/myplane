#ifndef __PICTURE_H__
#define __PICTURE_H__

#include "types.h"

class CPictureInfo{
public:
    CPictureInfo();
    ~CPictureInfo();
    int32 m_nWidth;
    int32 m_nHeight;
    int32 m_nChannel;
    byte* m_pData;

};



#endif
