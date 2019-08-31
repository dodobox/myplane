#include "consolecanvas.h"
#include "utils.h"

static uint16 _vFGColorTable[16] = {
    0,
    FOREGROUND_RED,
    FOREGROUND_GREEN,
    FOREGROUND_RED | FOREGROUND_GREEN,
    FOREGROUND_BLUE,
    FOREGROUND_RED | FOREGROUND_BLUE,
    FOREGROUND_GREEN | FOREGROUND_BLUE,
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    FOREGROUND_INTENSITY,
    FOREGROUND_INTENSITY | FOREGROUND_RED,
    FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

////public int To8Color(){
////    //8色化处理,取RGB的高1位相与。
////    var r1 = (R >> 5) & 0x4;
////    var g1 = (G >> 6) & 0x2;
////    var b1 = (B >> 7);
////    var c = (r1 | g1 | b1) + 1;//0表示透明，1-8表示颜色索引。
////    return c;
////}
////public int To16Color(){
////    //16色系统调色板:
////    //0 =  RGB(0, 0, 0) =        0x00000000;
////    //1 =  RGB(128, 0, 0) =      0x00000080;
////    //2 =  RGB(0, 128, 0) =      0x00008000;
////    //3 =  RGB(128, 128, 0) =    0x00008080;
////    //4 =  RGB(0, 0, 128) =      0x00800000;
////    //5 =  RGB(128, 0, 128) =    0x00800080;
////    //6 =  RGB(0, 128, 128) =    0x00808000;
////    //7 =  RGB(128, 128, 128) =  0x00808080;
////    //8 =  RGB(192, 192, 192) =  0x00c0c0c0;
////    //9 =  RGB(255, 0, 0) =      0x000000ff;
////    //10 = RGB(0, 255, 0) =     0x0000ff00;
////    //11 = RGB(255, 255, 0) =   0x0000ffff;
////    //12 = RGB(0, 0, 255) =     0x00ff0000;
////    //13 = RGB(255, 0, 255) =   0x00ff00ff;
////    //14 = RGB(0, 255, 255) =   0x00ffff00;
////    //15 = RGB(255, 255, 255) = 0x00ffffff;
////
////    //16色化处理，取R、G的高1位和B的高2位相与
////    var r1 = (R >> 4) & 0x8;
////    var g1 = (G >> 5) & 0x4;
////    var b1 = (B >> 6) & 0x3;
////    var c = (r1 | g1 | b1) + 1;//0表示透明，1-16表示颜色索引。
////    return c;
////}
////public int To256Color(){
////    var c = (int)(0.299 * R + 0.587 * G + 0.114 * B);//0表示透明，1-256表示颜色索引。
////    c = c & 0xFF;
////    return c;
////}


CConsoleCanvas::CConsoleCanvas():
CCanvas(){
    m_eCanvasType = ECT_CONSOLECAVNAS;
    m_ppCharInfo = NULL;
}
CConsoleCanvas::~CConsoleCanvas(){

}
void CConsoleCanvas::Init( int32 nWidth, int32 nHeight ){
    m_ppCharInfo = New2DArray<CHAR_INFO>( nWidth, nHeight );
  //  m_ppBKCanvas = New2DArray<byte>( nWidth, nHeight );
    m_ppFGCanvas = New2DArray<byte>( nWidth, nHeight );
}
void CConsoleCanvas::Final(){
    Delete2DArray( m_ppFGCanvas );
  //  Delete2DArray( m_ppBKCanvas );
    Delete2DArray( m_ppCharInfo );
}
void CConsoleCanvas::Clear(){
  //  memset( m_ppBKCanvas[0], 0, m_tCanvasSize.X * m_tCanvasSize.Y );
    memset( m_ppFGCanvas[0], 0, m_tCanvasSize.X * m_tCanvasSize.Y );
}
void* CConsoleCanvas::GetBuffer(){
    return m_ppCharInfo[ 0 ];
}


int32 CConsoleCanvas::Get16ColorIndex( uint32 nColor ){
    // 15 White   0xFFFFFF
    // 14 Aqua    0xffFF00   
    // 13 Fuchsia 0xFF00FF
    // 12 Blue    0xff0000
    // 7 Silver   0xC0C0C0
    // 8 Gray     0x808080
    // 6 Teal     0x808000
    // 5 Purple   0x800080
    // 4 Navy     0x800000		
    // 11 Yellow  0x00FFff
    // 10 Lime    0x00FF00		
    // 3 Olive    0x008080
    // 2 Green    0x008000	   
    // 9 Red      0x0000ff
    // 1 Maroon   0x000080
    // 0 Black    0x000000
    if( nColor < 0xff000000 ){
        return -1;
    }

    uint32 _R, _G, _B;
    GETCOLORRGB( nColor, _R, _G, _B );
    int32 _r = 0; 
    int32 _g = 0; 
    int32 _b = 0;

    if( _R > 244 ){
        _r = 3;
    } else if( _R > 161 ){
        _r = 2;
    } else if( _R > 64 ){
        _r = 1;
    } else{
        _r = 0;
    }

    if( _G > 244 ){
        _g = 3;
    } else if( _G > 161 ){
        _g = 2;
    } else if( _G > 64 ){
        _g = 1;
    } else{
        _g = 0;
    }

    if( _B > 244 ){
        _b = 3;
    } else if( _B > 161 ){
        _b = 2;
    } else if( _B > 64 ){
        _b = 1;
    } else{
        _b = 0;
    }

    uint32 _color64Index = _r *100 + _g * 10 + _b;
    int32 _nIndex16 = 0;

    switch( _color64Index ){
        case 00u: _nIndex16 = 0; break;
        case 01u: _nIndex16 = 4; break;
        case 02u: _nIndex16 = 0; break;
        case 03u: _nIndex16 = 12; break;
        case 10u: _nIndex16 = 2; break;
        case 11u: _nIndex16 = 6; break;
        case 12u: _nIndex16 = 14; break;
        case 13u: _nIndex16 = 14; break;
        case 20u: _nIndex16 = 10; break;
        case 21u: _nIndex16 = 14; break;
        case 22u: _nIndex16 = 14; break;
        case 23u: _nIndex16 = 14; break;
        case 30u: _nIndex16 = 10; break;
        case 31u: _nIndex16 = 14; break;
        case 32u: _nIndex16 = 14; break;
        case 33u: _nIndex16 = 14; break;
        case 100u: _nIndex16 = 1; break;
        case 101u: _nIndex16 = 5; break;
        case 102u: _nIndex16 = 13; break;
        case 103u: _nIndex16 = 13; break;
        case 110u: _nIndex16 = 3; break;
        case 111u: _nIndex16 = 7; break;
        case 112u: _nIndex16 = 7; break;
        case 113u: _nIndex16 = 7; break;
        case 120u: _nIndex16 = 11; break;
        case 121u: _nIndex16 = 7; break;
        case 122u: _nIndex16 = 15; break;
        case 123u: _nIndex16 = 15; break;
        case 130u: _nIndex16 = 11; break;
        case 131u: _nIndex16 = 8; break;
        case 132u: _nIndex16 = 14; break;
        case 133u: _nIndex16 = 14; break;

        case 200u: _nIndex16 = 9; break;
        case 201u: _nIndex16 = 5; break;
        case 202u: _nIndex16 = 13; break;
        case 203u: _nIndex16 = 13; break;
        case 210u: _nIndex16 = 3; break;
        case 211u: _nIndex16 = 9; break;
        case 212u: _nIndex16 = 13; break;
        case 213u: _nIndex16 = 13; break;
        case 220u: _nIndex16 = 11; break;
        case 221u: _nIndex16 = 11; break;
        case 222u: _nIndex16 = 8; break;
        case 223u: _nIndex16 = 15; break;
        case 230u: _nIndex16 = 11; break;
        case 231u: _nIndex16 = 11; break;
        case 232u: _nIndex16 = 10; break;
        case 233u: _nIndex16 = 15; break;
        case 300u: _nIndex16 = 9; break;
        case 301u: _nIndex16 = 0; break;
        case 302u: _nIndex16 = 0; break;
        case 303u: _nIndex16 = 13; break;
        case 310u: _nIndex16 = 9; break;
        case 311u: _nIndex16 = 9; break;
        case 312u: _nIndex16 = 13; break;
        case 313u: _nIndex16 = 13; break;
        case 320u: _nIndex16 = 11; break;
        case 321u: _nIndex16 = 11; break;
        case 322u: _nIndex16 = 15; break;
        case 323u: _nIndex16 = 15; break;
        case 330u: _nIndex16 = 11; break;
        case 331u: _nIndex16 = 11; break;
        case 332u: _nIndex16 = 15; break;
        case 333u: _nIndex16 = 15; break;
        default: _nIndex16 = 0; break;
    }
    return _nIndex16;
}
bool CConsoleCanvas::SetPixel( int32 x, int32 y, uint32 nColor ){
   // return false;
    if( x < 0 || x >= m_tCanvasSize.X || y < 0 || y >= m_tCanvasSize.Y )return false;
    int32 _nIndex = Get16ColorIndex( nColor );
    if( _nIndex < 0 ){
        return false;
    }
    m_ppFGCanvas[y][x] = _vFGColorTable[_nIndex];
    return true;
}
void CConsoleCanvas::SetBKPixel( int32 x, int32 y, uint32 nColor ){
  //  return;
    if( x < 0 || x >= m_tCanvasSize.X || y < 0 || y >= m_tCanvasSize.Y )return;
    int32 _nIndex = Get16ColorIndex( nColor );
    if( _nIndex < 0 ){
        return;
    }
    m_ppFGCanvas[y][x] = _vFGColorTable[_nIndex];
}
void CConsoleCanvas::DrawRect( int32 x, int32 y, int32 nWidth, int32 nHeight, uint32* pColors ){
    uint32* _pColors = pColors;
    for( int32 i = 0; i < nHeight; i ++ ){
        for( int32 j = 0; j < nWidth; j ++ ){
            SetBKPixel( x + j, y + i, *_pColors );
            _pColors ++;
        }
    }
}

void CConsoleCanvas::Show(){
    for( int i = 0; i < m_tCanvasSize.Y; i++ ){
        for( int j = 0; j < m_tCanvasSize.X; j++ ){
            m_ppCharInfo[i][j].Attributes = m_ppFGCanvas[i][j];
            m_ppCharInfo[i][j].Char.AsciiChar = m_ppFGCanvas[i][j] == 0 ? m_nNullCode : m_nFullCode;
        }
    }

    COORD dwBufferSize = { m_tCanvasSize.X,m_tCanvasSize.Y };//固定值(控制台窗口固定的属性值) 
    COORD dwBufferCoord = { 0, 0 };//缓冲区左上角的起始位置
    SMALL_RECT rect = { 0, 0, m_tCanvasSize.X - 1, m_tCanvasSize.Y - 1 };//显示多大的缓冲区: 大小是一个矩形
    WriteConsoleOutput( GetStdHandle( STD_OUTPUT_HANDLE ), (CONST CHAR_INFO *)m_ppCharInfo[0], dwBufferSize, dwBufferCoord, &rect );
}