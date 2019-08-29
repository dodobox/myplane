#include "stageconfig.h"
#include "stage.h"
#include "stagemanager.h"
#include "planemanager.h"


void CStageEventInfo::DoEvent(){
    switch( m_eEventType ){
    case EET_0: DoType0Event(); break;
    case EET_1:break;
    case EET_2:break;
    case EET_3:break;
    case EET_4:break;
    }
}

void CStageEventInfo::DoType0Event(){
    CStage* _pStage = CStageManager::GetInterface()->GetStage();
    CPlaneManager* _pPlaneManager = CPlaneManager::GetInterface();
    CStagePlaneInstInfo* _pPlaneInstInfo = _pStage->GetStagePlayerInstInfo( m_tEvent0Parame.m_nPlaneInstID );
    for( int32 i = 0; i < m_tEvent0Parame.m_nCount; i ++ ){
        CPlane* _pPlane = _pPlaneManager->AddPlane( _pPlaneInstInfo->m_ePlaneType, 50, -10, _pPlaneInstInfo->m_ePlaneDirection, _pPlaneInstInfo->m_eBehaviourType, _pPlaneInstInfo->m_ePlaneCamp );
        _pPlane->m_fAP = _pPlaneInstInfo->m_tAttribute.m_nAP;
        _pPlane->m_fDP = _pPlaneInstInfo->m_tAttribute.m_nDP;
        _pPlane->m_fSpeed = _pPlaneInstInfo->m_tAttribute.m_fSpeed;
        _pPlane->m_nHP = _pPlaneInstInfo->m_tAttribute.m_nHP;
    }
}




/////////////////////////////////////////////////////////////////////////////
bool CStageTriggerInfo::Check(){
    switch( m_eTriggerType ){
    case ETT_0: return CheckType0Condition(); break;
    }
}

bool CStageTriggerInfo::CheckType0Condition(){
    return CStage::m_fStageDistance > m_tTriggerType0Condition.m_nDistence;
}