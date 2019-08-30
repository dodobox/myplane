#ifndef __STAGEEVENTANDTRIGGER_H__
#define __STAGEEVENTANDTRIGGER_H__

#include "stageconfig.h"
#include "xml.h"
#include <vector>
#include <list>

class CStageEventAndTrigger{
public:
    CStageEventAndTrigger();
    ~CStageEventAndTrigger();
    void Init( CXMLNode *pNode );
    void Final();
    void Update( float fDelta );
    CStagePlaneInstInfo* GetPlaneInstInfo( int32 nIndex );

private:
    void TriggerEvent( int32 nEventID );

    std::vector< CStageBulletInstInfo >m_vBulletInstInfoList;
    std::vector<CStagePlaneInstInfo>m_vPlaneInstInfoList;
    std::vector<CStageEventInfo>m_vEventInfoList;
    std::list<CStageTriggerInfo>m_vTriggerInfoList;
};



#endif
