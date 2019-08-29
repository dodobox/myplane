#ifndef __STAGEMANAGER_H__
#define __STAGEMANAGER_H__

#include "stage.h"
#include "canvas.h"

class CStageManager{
public:
    static CStageManager* GetInterface();
    static void Release();
    CStageManager();
    ~CStageManager();
    void Init();
    void Final();
    void ResetStage( int32 nStage );
    void Update( float fDelta );
    void Draw( CCanvas* pCanvas );
    CStage* GetStage();

private:
    CStage* m_pStage;
    int32 m_nRound;
};


#endif
