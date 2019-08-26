#include "consolecanvas.h"

CConsoleCanvas::CConsoleCanvas():
CCanvas(){
    m_eCanvasType = ECT_CONSOLECAVNAS;
    m_ppCharInfo = NULL;
}
CConsoleCanvas::~CConsoleCanvas(){

}
void CConsoleCanvas::Init( int32 nWidth, int32 nHeight ){
    m_tSize = { nWidth, nHeight };
    m_ppCharInfo = New2DArray<CHAR_INFO>( nWidth, nHeight );
}
void CConsoleCanvas::Final(){
    Delete2DArray( m_ppCharInfo );
}
void CConsoleCanvas::Clear(){
    const WORD WhiteColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    for( int i = 0; i < m_tSize.Y; i++ ){
        for( int j = 0; j < m_tSize.X; j++ ){
            m_ppCharInfo[ i ][ j ].Attributes = 0;
            m_ppCharInfo[ i ][ j ].Char.AsciiChar = m_nNullCode;
        }
    }
}
void* CConsoleCanvas::GetBuffer(){
    return m_ppCharInfo[ 0 ];
}
bool CConsoleCanvas::SetPixel( int32 x, int32 y, uint32 nColor ){

        // Name            BG  FG
        // Black           30  40
        // Red             31  41
        // Green           32  42
        // Yellow          33  43
        // Blue            34  44
        // Magenta         35  45
        // Cyan            36  46
        // White           37  47
        // Bright Black    90  100
        // Bright Red      91  101
        // Bright Green    92  102
        // Bright Yellow   93  103
        // Bright Blue     94  104
        // Bright Magenta  95  105
        // Bright Cyan     96  106
        // Bright White    97  107
    const WORD WhiteColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    //const WORD RedColor = FOREGROUND_RED;
    //const WORD GreenColor = FOREGROUND_GREEN;
    //const WORD BlueColor = FOREGROUND_BLUE;
    //const WORD YellowColor = FOREGROUND_RED | FOREGROUND_GREEN;
    if( x < 0 || x >= m_tSize.X || y < 0 || y >= m_tSize.Y )return false;
    m_ppCharInfo[ y ][ x ].Attributes = WhiteColor;
    m_ppCharInfo[ y ][ x ].Char.AsciiChar = m_nFullCode;
    return true;
}

void CConsoleCanvas::Show(){
    COORD dwBufferSize = { m_tSize.X,m_tSize.Y };//固定值(控制台窗口固定的属性值) 
    COORD dwBufferCoord = { 0, 0 };//缓冲区左上角的起始位置
    SMALL_RECT rect = { 0, 0, m_tSize.X - 1, m_tSize.Y - 1 };//显示多大的缓冲区: 大小是一个矩形
    WriteConsoleOutput( GetStdHandle( STD_OUTPUT_HANDLE ), (CONST CHAR_INFO *)GetBuffer(), dwBufferSize, dwBufferCoord, &rect );
}