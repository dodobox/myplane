#include "canvas.h"
#include "consolecanvas.h"

static CCanvas* _pThis = NULL;
CCanvas* CCanvas::CreateCanvas( ECanvasType eCavansType, int32 nWidth, int32 nHeight ){
    _pThis = NEW CConsoleCanvas();
    _pThis->Init( nWidth, nHeight );
    return _pThis;
}
CCanvas* CCanvas::GetInterface(){
    return _pThis;
}
CCanvas::CCanvas():
m_eCanvasType( ECT_UNKOWN ),
m_tSize{ 0, 0 }{

}
CCanvas::~CCanvas(){

}