#include "stageconfig.h"
#include "stage.h"
#include "stagemanager.h"
#include "planemanager.h"
#include "utils.h"


static  TIntPoint _vInitPosition[EAPT_COUNT] = {
    { 10, -10 },//0
    { 30, -10 },//1
    { 50, -10 },//2
    { 70, -10 },//3
    { 90, -10 },//4
};


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
    EAppearPositionType _ePositionType = m_tEvent0Parame.m_eAppearPositionType;
    if( m_tEvent0Parame.m_nCount == 1 ){
        if( _ePositionType == EAPT_RAND ){
            _ePositionType = (EAppearPositionType)Rand( EAPT_COUNT );
        }
        CPlane* _pPlane = _pPlaneManager->AddPlane( _pPlaneInstInfo->m_ePlaneType, _vInitPosition[_ePositionType].X, _vInitPosition[_ePositionType].Y, _pPlaneInstInfo );
    } else{
        int32 _vPosArray[EAPT_COUNT];
        for( int32 i = 0; i < EAPT_COUNT; i ++ ){
            _vPosArray[i] = i;
        }
        RandIntArray( _vPosArray, EAPT_COUNT );
        for( int32 i = 0; i < m_tEvent0Parame.m_nCount; i ++ ){
            _ePositionType = (EAppearPositionType)_vPosArray[i];
            CPlane* _pPlane = _pPlaneManager->AddPlane( _pPlaneInstInfo->m_ePlaneType, _vInitPosition[_ePositionType].X, _vInitPosition[_ePositionType].Y, _pPlaneInstInfo );
        }
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