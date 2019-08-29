#ifndef __STAGE_H__
#define __STAGE_H__

#include "types.h"
#include "picture.h"
#include "background.h"
#include "stageeventandtrigger.h"
#include "canvas.h"

class CStage{
public:
    static float m_fStageDistance;
    static float m_fStageTime;

    CStage();
    ~CStage();
    void Init( int32 nStage );
    void Final();
    void Update( float fDelta );
    void Draw( CCanvas* pCanvas );

    CStagePlaneInstInfo* GetStagePlayerInstInfo( int32 nIndex );
private:


    CBackGround* m_pBackGround;
    CStageEventAndTrigger* m_pEventAndTrigger;

};



#endif
