#include "canvas.h"
#include "consolecanvas.h"
#include "dccanvas.h"

TIntPoint CCanvas::m_tCanvasSize = { 0,0 };
TIntRect  CCanvas::m_tSceneActiveRect = { 0,0,0,0 };
static CCanvas* _pThis = NULL;
CCanvas* CCanvas::CreateCanvas( ECanvasType eCavansType, int32 nWidth, int32 nHeight ){
    CCanvas::m_tCanvasSize = { nWidth,  nHeight };
    CCanvas::m_tSceneActiveRect = { -20,-40, nWidth + 20, nHeight + 40 };
    switch( eCavansType ){
    case ECT_CONSOLECAVNAS : _pThis = NEW CConsoleCanvas(); break;
    case ECT_DCCAVNAS: _pThis = NEW CDCCanvas(); break;
    }
    _pThis->Init( nWidth, nHeight );
    return _pThis;
}
CCanvas* CCanvas::GetInterface(){
    return _pThis;
}
CCanvas::CCanvas():
m_eCanvasType( ECT_UNKOWN ){

}
CCanvas::~CCanvas(){

}