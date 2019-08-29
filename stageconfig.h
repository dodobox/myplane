#ifndef __STAGECONFIG_H__
#define __STAGECONFIG_H__

#include "types.h"

#define MAXPICTUREID 4
class CStageTileInfo{
public:
    int32 m_vPictureIDs[ MAXPICTUREID ];
    int32 m_nPicture;
};

class CStagePlaneInstInfo{
public:
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
    EEventType m_eEventType;
    union{
        struct{
            int32 m_nPlaneInstID;
            int32 m_nCount;
            EAppearPositionType m_eAppearPositionType;
        }m_tEvent0Parame;
    };

    void DoEvent();
    void DoType0Event();

};

class CStageTriggerInfo{
public:
    ETriggerType m_eTriggerType;
    int32 m_nEventID;
    union{
        struct{
            int32 m_nDistence;
        }m_tTriggerType0Condition;
    };

    bool Check();
    bool CheckType0Condition();
};




#endif

