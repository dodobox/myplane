#ifndef WINDFORCE_SYSTEM_XML_H_
#define WINDFORCE_SYSTEM_XML_H_

//#include "windforce.h"
//#include "datastream.h"
#include "types.h"

class CXMLNode{
public:
    CXMLNode(){}
    CXMLNode( object32 pObject );
    CXMLNode GetNode( const char* strNodeName );
    CXMLNode GetFirstNode();
    CXMLNode GetNextNode();
    CXMLNode GetNextNode( const char* strNodeName );
	int32 GetNodeCount( const char* strNodeName );
    int32 GetChildCount();
    const char* GetName();
    const char* GetValue();
    int32 GetInt32Value();
    float GetFloatValue();

    const char* GetAttributeValue( const char* strAttriName );
    int32 GetAttributeInt32Value( const char* strAttriName );
    float GetAttributeFloatValue( const char* strAttriName );

    bool Vaild(){ return m_pObject != NULL; }

public:
    object32 m_pObject;
};

class CXMLDocment{
public:
    CXMLDocment( const char* strFileName );
    //CXMLDocment( system::IStream &tStream );
    virtual ~CXMLDocment();
    CXMLNode GetNode( const char* strNodeName );
    CXMLNode GetFirstNode();
    
private:
    object32 m_pObject;
	char* m_strData;
}; 




#endif