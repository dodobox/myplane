#include "stageeventandtrigger.h"

CStageEventAndTrigger::CStageEventAndTrigger(){

}
CStageEventAndTrigger::~CStageEventAndTrigger(){

}
void CStageEventAndTrigger::Init( CXMLNode *pNode ){

    ///////////////////////////////////////////////////////////////////////
    //planes
    CXMLNode _tPlanesNode = pNode->GetNode( "planes" );
    CXMLNode _tPlaneNode = _tPlanesNode.GetFirstNode();
    while( _tPlaneNode.Vaild() ){
        CStagePlaneInstInfo _tStagePlaneInstInfo;
        _tStagePlaneInstInfo.m_ePlaneType = (EPlaneType)_tPlaneNode.GetAttributeInt32Value("type");
        _tStagePlaneInstInfo.m_ePlaneCamp = (EPlaneCamp)_tPlaneNode.GetAttributeInt32Value( "camp" );
        _tStagePlaneInstInfo.m_eBehaviourType = (EBehaviourType)_tPlaneNode.GetAttributeInt32Value( "behaviortype" );
        _tStagePlaneInstInfo.m_ePlaneDirection = (EPlaneDirection)_tPlaneNode.GetAttributeInt32Value( "directiontype" );
        CXMLNode _tPlaneAttrNode = _tPlaneNode.GetNode( "attribute" );
        _tStagePlaneInstInfo.m_tAttribute.m_nAP = _tPlaneAttrNode.GetAttributeInt32Value("ap");
        _tStagePlaneInstInfo.m_tAttribute.m_nDP = _tPlaneAttrNode.GetAttributeInt32Value( "dp" );
        _tStagePlaneInstInfo.m_tAttribute.m_fSpeed = _tPlaneAttrNode.GetAttributeFloatValue( "speed" );
        _tStagePlaneInstInfo.m_tAttribute.m_nHP = _tPlaneAttrNode.GetAttributeInt32Value( "hp" );
        m_vPlaneInstInfoList.push_back( _tStagePlaneInstInfo );
        _tPlaneNode = _tPlaneNode.GetNextNode();
    }
    
    //////////////////////////////////////////////////////////////////////
    //events
    CXMLNode _tEventsNode = pNode->GetNode( "events" );
    CXMLNode _tEventNode = _tEventsNode.GetFirstNode();
    while( _tEventNode.Vaild() ){
        CStageEventInfo _tStageEventInfo;
        _tStageEventInfo.m_eEventType = (EEventType)_tEventNode.GetAttributeInt32Value("type");

        CXMLNode _tEventParamesNode = _tEventNode.GetNode("parames");
        switch( _tStageEventInfo.m_eEventType ){
        case EET_0:{
            _tStageEventInfo.m_tEvent0Parame.m_nPlaneInstID = _tEventParamesNode.GetAttributeInt32Value( "plane" );
            _tStageEventInfo.m_tEvent0Parame.m_nCount = _tEventParamesNode.GetAttributeInt32Value( "count" );
            _tStageEventInfo.m_tEvent0Parame.m_eAppearPositionType = (EAppearPositionType)_tEventParamesNode.GetAttributeInt32Value( "pos" );
        }break;
        }

        m_vEventInfoList.push_back( _tStageEventInfo );
        _tEventNode = _tEventNode.GetNextNode();
    }
    
    //////////////////////////////////////////////////////////////////////
    //tirggets
    CXMLNode _tTriggersNode = pNode->GetNode( "triggers" );
    CXMLNode _tTriggerNode = _tTriggersNode.GetFirstNode();
    while( _tTriggerNode.Vaild() ){
        CStageTriggerInfo _tStageTriggerInfo;
        _tStageTriggerInfo.m_eTriggerType = (ETriggerType)_tTriggerNode.GetAttributeInt32Value( "type" );
        _tStageTriggerInfo.m_nEventID = _tTriggerNode.GetAttributeInt32Value( "event" );


        CXMLNode _tTriggerConditionNode = _tTriggerNode.GetNode( "condition" );
        switch( _tStageTriggerInfo.m_eTriggerType ){
        case ETT_0:{
            _tStageTriggerInfo.m_tTriggerType0Condition.m_nDistence = _tTriggerConditionNode.GetAttributeInt32Value( "distance" );
        }break;
        }

        m_vTriggerInfoList.push_back( _tStageTriggerInfo );
        _tTriggerNode = _tTriggerNode.GetNextNode();
    }
}
void CStageEventAndTrigger::Final(){
    m_vTriggerInfoList.clear();
    m_vEventInfoList.clear();
    m_vPlaneInstInfoList.clear();
}
void CStageEventAndTrigger::Update( float fDelta ){
    for( auto it = m_vTriggerInfoList.begin(); it != m_vTriggerInfoList.end(); ){
        CStageTriggerInfo* _pStageTriggerInfo = &(*it);
        if( _pStageTriggerInfo->Check() ){
            int32 _nEventID = _pStageTriggerInfo->m_nEventID;
            TriggerEvent( _nEventID );
            it = m_vTriggerInfoList.erase( it );
        } else{
            it ++;
        }
    }
}
void CStageEventAndTrigger::TriggerEvent( int32 nEventID ){
    CStageEventInfo* _pStageEventInfo = &(m_vEventInfoList[ nEventID ]);
    _pStageEventInfo->DoEvent();
}

CStagePlaneInstInfo* CStageEventAndTrigger::GetPlaneInstInfo( int32 nIndex ){
    return &m_vPlaneInstInfoList[ nIndex ];
}