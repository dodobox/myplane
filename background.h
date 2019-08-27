#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "stageconfig.h"
#include "xml.h"
#include <vector>

class CBackGround{
public:
    CBackGround();
    ~CBackGround();
    void Init( CXMLNode *pNode );
    void Final();
    void Update( float fDelta );

    std::vector<CPictureInfo*>m_vPictureList;
    std::vector<CStageTileInfo>m_vTileInfoList;
};


#endif
