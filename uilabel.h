#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "uinode.h"
#include <vector>

class CUILabel: public CUINode{
public:
    CUILabel();
    virtual ~CUILabel();
    virtual void Init();
    virtual void Final();
    virtual void Update( float fDelta );
    virtual void Draw( CCanvas* pCanvas );
    void SetText( char* strText );

private:
    std::vector< char >m_vText;
};


#endif
