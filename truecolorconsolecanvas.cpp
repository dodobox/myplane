#include "truecolorconsolecanvas.h"
#include "utils.h"
#include <stdio.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

CTrueColorConsoleCanvas::CTrueColorConsoleCanvas():
CCanvas(){
    m_eCanvasType = ECT_TRUECOLORCONSOLECANVAS;
}
CTrueColorConsoleCanvas::~CTrueColorConsoleCanvas(){

}
void CTrueColorConsoleCanvas::Init( int32 nWidth, int32 nHeight ){
    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );                      //获取控制台窗口句柄
    DWORD dwMode = 0;
    if( !GetConsoleMode( hOut, &dwMode ) ){
        return;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if( !SetConsoleMode( hOut, dwMode ) ){
        return;
    }
    m_ppFGCanvas = NEW2DARRAY( uint32, nWidth, nHeight );
}
void CTrueColorConsoleCanvas::Final(){
    DELETE2DARRAY( uint32, m_ppFGCanvas );
    //ReleaseDC( console, console_hdc );
    //DeleteDC( console_hdc );
}
void CTrueColorConsoleCanvas::Clear(){
    memset( m_ppFGCanvas[0], 0, m_tCanvasSize.X * m_tCanvasSize.Y * sizeof( uint32 ) );
}
void* CTrueColorConsoleCanvas::GetBuffer(){
    return NULL;
}

int32 CTrueColorConsoleCanvas::Get16ColorIndex( uint32 nColor ){
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

    uint32 _color64Index = _r * 100 + _g * 10 + _b;
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

bool CTrueColorConsoleCanvas::SetPixel( int32 x, int32 y, uint32 nColor ){
   // return false;
    if( x < 0 || x >= m_tCanvasSize.X || y < 0 || y >= m_tCanvasSize.Y )return false;

    if( nColor < 0xff000000 ){
        return false;
    }

    uint32 _R, _G, _B;
    GETCOLORRGB( nColor, _R, _G, _B );
    m_ppFGCanvas[ y ][ x ] = RGB( _B, _G, _R );

    //////int32 _nIndex = Get16ColorIndex( nColor );
    //////if( _nIndex < 0 ){
    //////    return false;
    //////}
    //////m_ppFGCanvas[y][x] = _vFGColorTable[ _nIndex ];
    return true;
}
//void CDCCanvas::SetBKPixel( int32 x, int32 y, uint32 nColor ){
//  //  return;
//    if( x < 0 || x >= m_tCanvasSize.X || y < 0 || y >= m_tCanvasSize.Y )return;
//    int32 _nIndex = Get16ColorIndex( nColor );
//    if( _nIndex < 0 ){
//        return;
//    }
//    m_ppFGCanvas[y][x] = _nIndex;
//}
void CTrueColorConsoleCanvas::DrawRect( int32 x, int32 y, int32 nWidth, int32 nHeight, uint32* pColors ){
    uint32* _pColors = pColors;
    for( int32 i = 0; i < nHeight; i ++ ){
        for( int32 j = 0; j < nWidth; j ++ ){
            SetPixel( x + j, y + i, *_pColors );
            _pColors ++;
        }
    }
}

void CTrueColorConsoleCanvas::Show(){
    system( "cls" );
    //HBITMAP hBitmap = ::CreateBitmap( m_tCanvasSize.X, m_tCanvasSize.Y, 1, 32, m_ppFGCanvas[0] );
    //HDC hMemDc = ::CreateCompatibleDC( console_hdc );
    //HBITMAP hOldBitmap = (HBITMAP)::SelectObject( hMemDc, hBitmap );
    //::BitBlt( console_hdc, 0, 0, m_tCanvasSize.X, m_tCanvasSize.Y, hMemDc, 0, 0, SRCCOPY );
    //::SelectObject( hMemDc, hOldBitmap );
    //::DeleteObject( hBitmap );

    for( int i = 0; i < m_tCanvasSize.Y; i++ ){
        for( int j = 0; j < m_tCanvasSize.X; j++ ){
            //::SetPixel( console_hdc, j, i, _vFGColorTable[m_ppFGCanvas[i][j]] );
            //m_ppFGCanvas[ i ][ j ];
            int32 _R, _G, _B;
            GETCOLORRGB( m_ppFGCanvas[ i ][ j ], _R, _G, _B );
            printf( "\x1B[38;2;%u;%u;%umX", _R, _G, _B );
        }
        putchar('\n');
    }

}