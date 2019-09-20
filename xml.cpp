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
    xml_node* _pxmlNode = ((xml_document*)m_pObject)->first_node( strNodeName );
    return CXMLNode( _pxmlNode );
}

CXMLNode CXMLNode::GetFirstNode(){
    xml_node* _pxmlNode = ((xml_document*)m_pObject)->first_node();
    return CXMLNode( _pxmlNode );
}

CXMLNode CXMLNode::GetNextNode(){
    xml_node* _pxmlNode = ((xml_document*)m_pObject)->next_sibling();
    return CXMLNode( _pxmlNode );
}

CXMLNode CXMLNode::GetNextNode( const char* strNodeName ){
    xml_node* _pxmlNode = ((xml_document*)m_pObject)->next_sibling( strNodeName );
    return CXMLNode( _pxmlNode );
}

int32 CXMLNode::GetNodeCount( const char* strNodeName ){
	int32 _nResult = 0;
	xml_node* _pxmlNode = ((xml_document*)m_pObject)->first_node( strNodeName );
	while ( _pxmlNode ){
		_nResult ++;
		_pxmlNode = _pxmlNode->next_sibling( strNodeName );
	}
	return _nResult;
}

int32 CXMLNode::GetChildCount(){
    int32 _nResult = 0;
    xml_node* _pxmlNode = ((xml_document*)m_pObject)->first_node();
    while ( _pxmlNode ){
        _nResult ++;
        _pxmlNode = _pxmlNode->next_sibling();
    }
    return _nResult;
}

const char* CXMLNode::GetName(){
    return ((xml_document*)m_pObject)->name();
}

const char* CXMLNode::GetValue(){
    return ((xml_document*)m_pObject)->value();
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
        return (float)atof( _pValue );
    }
    return 0.0f;
}


const char* CXMLNode::GetAttributeValue( const char* strAttriName ){
    xml_attribute* _strAttr = ((xml_document*)m_pObject)->first_attribute( strAttriName );
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
        return (float)atof( _pValue );
    }
    return 0.0f;
}


CXMLDocment::CXMLDocment( const char* strFileName )
: m_pObject( NULL )
, m_strData( NULL ){

    //system::CopyNewStr( m_strData, strFileName );
    int32 _nSize = 0;
    GetFileData( strFileName, (byte**)&m_strData, &_nSize );

    xml_document* _pDoc = (xml_document*)MALLOC( sizeof( xml_document ));
    _pDoc->xml_document::xml_document();
    _pDoc->parse<0>( m_strData );
    m_pObject = _pDoc;
}

CXMLDocment::~CXMLDocment(){
    xml_document* _pDoc = (xml_document*)m_pObject;
    _pDoc->xml_document::~xml_document();
    FREE( _pDoc );
    FREE( m_strData );
	//DELETESCHAR( m_strData );
}

CXMLNode CXMLDocment::GetNode( const char* strNodeName ){
    xml_node* _pxmlNode = ((xml_document*)m_pObject)->first_node( strNodeName );
    return CXMLNode( _pxmlNode );
}

CXMLNode CXMLDocment::GetFirstNode(){
    xml_node* _pxmlNode = ((xml_document*)m_pObject)->first_node();
    return CXMLNode( _pxmlNode );
}

