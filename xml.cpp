#include "xml.h"
//#include "../include/datastream.h"
//#include "../include/system.h"
#include "rapidxml.h"
#include "utils.h"
#include <string>


CXMLNode::CXMLNode( object32 pObject ){
    m_pObject = pObject;
}
CXMLNode CXMLNode::GetNode( const char* strNodeName ){
    rapidxml::xml_node<char>* _pxmlNode = ((rapidxml::xml_document<char>*)m_pObject)->first_node( strNodeName );
    return CXMLNode( _pxmlNode );
}

CXMLNode CXMLNode::GetFirstNode(){
    rapidxml::xml_node<char>* _pxmlNode = ((rapidxml::xml_document<char>*)m_pObject)->first_node();
    return CXMLNode( _pxmlNode );
}

CXMLNode CXMLNode::GetNextNode(){
    rapidxml::xml_node<char>* _pxmlNode = ((rapidxml::xml_document<char>*)m_pObject)->next_sibling();
    return CXMLNode( _pxmlNode );
}

CXMLNode CXMLNode::GetNextNode( const char* strNodeName ){
    rapidxml::xml_node<char>* _pxmlNode = ((rapidxml::xml_document<char>*)m_pObject)->next_sibling( strNodeName );
    return CXMLNode( _pxmlNode );
}

int32 CXMLNode::GetNodeCount( const char* strNodeName ){
	int32 _nResult = 0;
	rapidxml::xml_node<char>* _pxmlNode = ((rapidxml::xml_document<char>*)m_pObject)->first_node( strNodeName );
	while ( _pxmlNode ){
		_nResult ++;
		_pxmlNode = _pxmlNode->next_sibling( strNodeName );
	}
	return _nResult;
}

int32 CXMLNode::GetChildCount(){
    int32 _nResult = 0;
    rapidxml::xml_node<char>* _pxmlNode = ((rapidxml::xml_document<char>*)m_pObject)->first_node();
    while ( _pxmlNode ){
        _nResult ++;
        _pxmlNode = _pxmlNode->next_sibling();
    }
    return _nResult;
}

const char* CXMLNode::GetName(){
    return ((rapidxml::xml_document<char>*)m_pObject)->name();
}

const char* CXMLNode::GetValue(){
    return ((rapidxml::xml_document<char>*)m_pObject)->value();
}
int32 CXMLNode::GetInt32Value(){
    const char* _pValue = GetValue();
    if( _pValue ){
        return atoi( _pValue );
    }
    return 0;
}
float CXMLNode::GetFloatValue(){
    const char* _pValue = GetValue();
    if( _pValue ){
        return atof( _pValue );
    }
    return 0.0f;
}


const char* CXMLNode::GetAttributeValue( const char* strAttriName ){
    rapidxml::xml_attribute<char>* _strAttr = ((rapidxml::xml_document<char>*)m_pObject)->first_attribute( strAttriName );
    if ( _strAttr ){
        return _strAttr->value();
    }
    return NULL;
}
int32 CXMLNode::GetAttributeInt32Value( const char* strAttriName ){
    const char* _pValue = GetAttributeValue( strAttriName );
    if( _pValue ){
        return atoi( _pValue );
    }
    return 0;
}
float CXMLNode::GetAttributeFloatValue( const char* strAttriName ){
    const char* _pValue = GetAttributeValue( strAttriName );
    if( _pValue ){
        return atof( _pValue );
    }
    return 0.0f;
}


CXMLDocment::CXMLDocment( const char* strFileName )
: m_pObject( NULL )
, m_strData( NULL ){

    //system::CopyNewStr( m_strData, strFileName );
    int32 _nSize = 0;
    GetFileData( strFileName, (byte**)&m_strData, &_nSize );

    m_pObject = NEW rapidxml::xml_document<char>;
    ((rapidxml::xml_document<char>*)m_pObject)->parse<0>( m_strData );
}

CXMLDocment::~CXMLDocment(){
    int32* p = (int32*)m_pObject;
    DELETE( p );
    DELETE( m_strData );
	//DELETESCHAR( m_strData );
}

CXMLNode CXMLDocment::GetNode( const char* strNodeName ){
    rapidxml::xml_node<char>* _pxmlNode = ((rapidxml::xml_document<char>*)m_pObject)->first_node( strNodeName );
    return CXMLNode( _pxmlNode );
}

CXMLNode CXMLDocment::GetFirstNode(){
    rapidxml::xml_node<char>* _pxmlNode = ((rapidxml::xml_document<char>*)m_pObject)->first_node();
    return CXMLNode( _pxmlNode );
}

