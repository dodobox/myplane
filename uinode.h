#ifndef __UINODE_H__
#define __UINODE_H__

#include "canvas.h"
#include <list>

class CUINode: public CMemObject{
public:
    CUINode();
    virtual ~CUINode();
    virtual void Init();
    virtual void Final();
    virtual void Update( float fDelta );
    virtual void Draw( CCanvas* pCanvas );
    void Clear();
    void AddChild( CUINode* pNode );
    void SetPosition( int32 x, int32 y );
protected:
    EUIType m_eUIType;
    bool m_bVisible;
    TIntPoint m_tPositon;

    std::list<CUINode*>m_vNodeList;
};

#endif
