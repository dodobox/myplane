#ifndef __STAGECONFIG_H__
#define __STAGECONFIG_H__

#include "types.h"

#define MAXPICTUREID 4
class CStageTileInfo{
public:
    int32 m_nID;
    int32 m_vPictureIDs[ MAXPICTUREID ];
    int32 m_nPicture;
};

class CStagePlaneInstInfo{
public:
    int32 m_nID;
    EPlaneType m_ePlaneType;
    EPlaneCamp m_ePlaneCamp;
    EBehaviourType m_eBehaviourType;
    EPlaneDirection m_ePlaneDirection;
    struct{
        int32 m_nAP;
        int32 m_nDP;
        float m_fSpeed;
        int32 m_nHP;
    }m_tAttribute;
};

class CStageEventInfo{
public:
    int32 m_nID;
    EEventType m_eEventType;
    union{
        struct{
            int32 m_nPlaneInst;
            int32 m_nCount;
            EAppearPositionType m_eAppearPositionType;
        }m_tEvent0Parame;
    };
};

class CStageTriggerInfo{
public:
    int32 m_nID;
    ETriggerType m_eTriggerType;
    int32 m_nEventID;
    union{
        struct{
            int32 m_nDistence;
        }m_tTriggerType0Condition;
    };


};




#endif

