#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "stageconfig.h"
#include "xml.h"
#include "canvas.h"
#include "picture.h"
#include <vector>
#include <list>

class CBackGround{
public:
    CBackGround();
    ~CBackGround();
    void Init( CXMLNode *pNode );
    void Final();
    void Update( float fDelta );
    void Draw( CCanvas* pCanvas );

//private:
    void InitScrollItems();
    CPictureInfo* GetNextPictureInfo();
    void UpdateScrollQueue( float fDeltaDistance );
    struct TScrollItemInfo{
        CPictureInfo* m_pPictureInfo;
        float m_fLeft;
        float m_fTop;
    };
    std::list<TScrollItemInfo>m_vScrollQueue;     //¹ö¶¯¶ÓÁÐ
    std::vector<CPictureInfo*>m_vPictureList;
    std::vector<CStageTileInfo>m_vTileInfoList;
    int32 m_nTileIndex;
    float m_fScrollPictureTop;
    float m_fSpeed;
};


#endif
