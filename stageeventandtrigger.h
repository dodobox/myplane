#ifndef __STAGEEVENTANDTRIGGER_H__
#define __STAGEEVENTANDTRIGGER_H__

#include "stageconfig.h"
#include "xml.h"
#include <vector>

class CStageEventAndTrigger{
public:
    CStageEventAndTrigger();
    ~CStageEventAndTrigger();
    void Init( CXMLNode *pNode );
    void Final();
    void Update( float fDelta );

    std::vector<CStagePlaneInstInfo>m_vPlaneInstInfoList;
    std::vector<CStageEventInfo>m_vEventInfoList;
    std::vector<CStageTriggerInfo>m_vTriggerInfoList;
};



#endif
