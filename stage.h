#ifndef __STAGE_H__
#define __STAGE_H__

#include "types.h"
#include "picture.h"
#include "background.h"
#include "stageeventandtrigger.h"

class CStage{
public:
    CStage();
    ~CStage();
    void Init();
    void Final();
    void Update( float fDelta );

    CBackGround* m_pBackGround;
    CStageEventAndTrigger* m_pEventAndTrigger;

};



#endif
