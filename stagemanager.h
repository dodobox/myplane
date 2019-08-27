#ifndef __STAGEMANAGER_H__
#define __STAGEMANAGER_H__

#include "stage.h"

class CStageManager{
public:
    static CStageManager* GetInterface();
    static void Release();
    CStageManager();
    ~CStageManager();
    void Init();
    void Final();
    void Update( float fDelta );
    void Draw();

private:
    CStage* m_pStage;
};


#endif
