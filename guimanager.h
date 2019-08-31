#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "uinode.h"

enum EUIUpdateInfoType{
    EUUIT_0,    //更新hp
    EUUIT_1,    //更新score
    EUUIT_2,    //更新distance
};

class CUIInfoMationDlg;
class CGUIManager: public CUINode{
public:
    static CGUIManager* GetInterface();
    static void Release();
    CGUIManager();
    virtual ~CGUIManager();
    virtual void Init();
    virtual void Final();
    virtual void Update( float fDelta );
    virtual void Draw( CCanvas* pCanvas );
    void UpdateInfo( EUIUpdateInfoType eType, int32 nParame0, int32 nParame1 );

private:
    CUIInfoMationDlg* m_pInfomationDlg;
};


#endif
