#ifndef __UIINFORMATION_H__
#define __UIINFORMATION_H__

#include "uinode.h"
#include "uiimage.h"
#include "uilabel.h"

class CUIInfoMationDlg: public CUINode{
public:
    CUIInfoMationDlg();
    virtual ~CUIInfoMationDlg();
    virtual void Init();
    virtual void Final();
    void SetHP( int32 nHP );
    void SetScore( int32 nScore );
    void SetDistance( int32 nDistance, int32 nMaxDistance );

private:

    CUIImage* m_pBKImage;
    CUILabel* m_pHPLabel;
    CUILabel* m_pDistanceLabel;
    CUILabel* m_pScoreLabel;

    int32 m_nHP;
    int32 m_nScore;
    int32 m_nDistance;
    int32 m_nMaxDistance;

};


#endif
