#include <Windows.h>
#include <list>
#include <map>
#include "memutile.h"
#include "consolecanvas.h"
#include "planemanager.h"
#include "behaviourcontrolmanager.h"
#include "picturemanager.h"
#include "planeconfig.h"
#include "bulletbehaviourcontrolmanager.h"
#include "bulletconfig.h"
#include "stagemanager.h"
#include "bulletmanager.h"
#include "collisionmap.h"
#include "bulletemittermanager.h"
#include "sound.h"
#include "guimanager.h"

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)

int main(){
    InitMemory( 1024 * 1024 * 1, &mem_getmem, &mem_freemem, &mem_print, &mem_assert, &mem_gettime );

    //    936 GBK( һ�������ΪĬ�ϱ��� )
    //    437 ����Ӣ��
    //    65001 utf - 8
    system( "chcp 437" );
    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );

    COORD size = { 100, 150 };
    SetConsoleScreenBufferSize( hOut, size ); // �������û�������С
    ////                                          //_getch();
    SMALL_RECT rc = { 0,0, 1024 - 1, 1024 - 1 }; // ���ô���λ�úʹ�С
    SetConsoleWindowInfo( hOut, true, &rc );

    CPictureManager::GetInterface();
    CBulletConfig::GetInterface();
    CBulletBehaviourControlManager::GetInterface();
    CPlaneConfig::GetInterface();
    CBehaviourControlManager::GetInterface();
    CBulletMitterManager::GetInterface();
    CBulletManager* _pBulletManager = CBulletManager::GetInterface();
    CPlaneManager* _pPlaneManager = CPlaneManager::GetInterface();
    CCanvas* _pCanvas = CCanvas::CreateCanvas( ECT_DCCAVNAS, 100, 150 );
   // CCanvas* _pCanvas = CCanvas::CreateCanvas( ECT_CONSOLECAVNAS, 100, 150 );
    //CCanvas* _pCanvas = CCanvas::CreateCanvas( ECT_TRUECOLORCONSOLECANVAS, 100, 150 );
    
    CCollisionMap* _pCollisionMap = CCollisionMap::GetInterface();
    CGUIManager* _pGUIManager = CGUIManager::GetInterface();

    CStageManager* _pStageManager = CStageManager::GetInterface();
    _pStageManager->ResetStage( 0 );
    _pPlaneManager->CreatePlayerPlane( EPT_TYPE0 );
    PlayBKSound("sound/background.wav");
    uint32 _nTime = mem_gettime();
    while( 1 ){
        uint32 _nCurTime = mem_gettime();
        float _fDelta = (float)(_nCurTime - _nTime)  * 0.001f;
        _nTime = _nCurTime;
        _pStageManager->Update( _fDelta );
        _pBulletManager->Update( _fDelta );
        _pPlaneManager->Update( _fDelta );
        _pGUIManager->Update( _fDelta );
        _pCollisionMap->Clear();
        _pCanvas->Clear();
        _pStageManager->Draw( _pCanvas );
        _pPlaneManager->Draw( _pCanvas );
        _pBulletManager->Draw( _pCanvas );
        _pGUIManager->Draw( _pCanvas );
        _pCanvas->Show();
        if( KEYDOWN( VK_ESCAPE ) ){
            break;
        }
        Sleep( 33 );
    }

    CBulletMitterManager::Release();
    CStageManager::Release();
    CGUIManager::Release();
    CPlaneManager::Release();
    CBulletManager::Release();
    CCollisionMap::Release();
    CCanvas::Release();
    CBehaviourControlManager::Release();
    CBulletBehaviourControlManager::Release();
    CBulletConfig::Release();
    CPlaneConfig::Release();
    CPictureManager::Release();

    mem_getsysallocsize();
    DumpIdle();
    DumpLeak();

    system("pause");

    return 0;
}









////
////
////#include <windows.h>
////#include <stdio.h>
////
////#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
////#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
////#endif
////
////
////
////
////#include <stdio.h>
////#include <wchar.h>
////#include <windows.h>
////
////int main(){
////    // Set output mode to handle virtual terminal sequences
////    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
////    if( hOut == INVALID_HANDLE_VALUE ){
////        return GetLastError();
////    }
////
////    DWORD dwMode = 0;
////    if( !GetConsoleMode( hOut, &dwMode ) ){
////        return GetLastError();
////    }
////
////    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
////    if( !SetConsoleMode( hOut, dwMode ) ){
////        return GetLastError();
////    }
////
////    // Try some Set Graphics Rendition (SGR) terminal escape sequences
////    wprintf( L"\x1b[31mThis text has a red foreground using SGR.31.\r\n" );
////    wprintf( L"\x1b[1mThis text has a bright (bold) red foreground using SGR.1 to affect the previous color setting.\r\n" );
////    wprintf( L"\x1b[mThis text has returned to default colors using SGR.0 implicitly.\r\n" );
////    wprintf( L"\x1b[34;46mThis text shows the foreground and background change at the same time.\r\n" );
////    wprintf( L"\x1b[0mThis text has returned to default colors using SGR.0 explicitly.\r\n" );
////    wprintf( L"\x1b[31;32;33;34;35;36;101;102;103;104;105;106;107mThis text attempts to apply many colors in the same command. Note the colors are applied from left to right so only the right-most option of foreground cyan (SGR.36) and background bright white (SGR.107) is effective.\r\n" );
////    wprintf( L"\x1b[39mThis text has restored the foreground color only.\r\n" );
////    wprintf( L"\x1b[49mThis text has restored the background color only.\r\n" );
////
////
////    wprintf( L"\x1B[38;2;255;255;0mThis text has restored the background color only.\r\n" );
////    return 0;
////}


//
//
//#include <stdio.h>
//#include <wchar.h>
//#include <windows.h>
//
//
//void SetPrintColor( unsigned char r, unsigned char g, unsigned char b ){//������vt�����ſ���
//    printf( "\x1B[38;2;%u;%u;%um", r, g, b );
//}
//
//int main(){
//    // Set output mode to handle virtual terminal sequences
//    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
//    if( hOut == INVALID_HANDLE_VALUE ){
//        return GetLastError();
//    }
//
//    DWORD dwMode = 0;
//    if( !GetConsoleMode( hOut, &dwMode ) ){
//        return GetLastError();
//    }
//
//    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//    if( !SetConsoleMode( hOut, dwMode ) ){
//        return GetLastError();
//    }
//
//    for( int32 i = 0; i < 256; i ++ ){
//        SetPrintColor( i, i, i );
//        printf("X");
//        if( i % 16 == 15 ){
//            printf( "   " );
//            for( int32 j = i + 1; j < i + 1 + 16; j ++ ){
//                SetPrintColor( i, 0, 0 );
//                printf( "X" );
//            }
//            putchar( '\n' );
//        }
//    }
//
//    // Try some Set Graphics Rendition (SGR) terminal escape sequences
//    //wprintf( L"\x1b[31mThis text has a red foreground using SGR.31.\r\n" );
//    //wprintf( L"\x1b[1mThis text has a bright (bold) red foreground using SGR.1 to affect the previous color setting.\r\n" );
//    //wprintf( L"\x1b[mThis text has returned to default colors using SGR.0 implicitly.\r\n" );
//    //wprintf( L"\x1b[34;46mThis text shows the foreground and background change at the same time.\r\n" );
//    //wprintf( L"\x1b[0mThis text has returned to default colors using SGR.0 explicitly.\r\n" );
//    //wprintf( L"\x1b[31;32;33;34;35;36;101;102;103;104;105;106;107mThis text attempts to apply many colors in the same command. Note the colors are applied from left to right so only the right-most option of foreground cyan (SGR.36) and background bright white (SGR.107) is effective.\r\n" );
//    //wprintf( L"\x1b[39mThis text has restored the foreground color only.\r\n" );
//    //wprintf( L"\x1b[49mThis text has restored the background color only.\r\n" );
//
//
//   // printf( "\x1B[38;2;%u;%u;%um", 255, 0, 0 );
//
//    //for( int i = 0; i <= 255; i++ ){
//    //    for( int j = 0; j <= 255; j++ ){
//    //        for( int k = 0; k <= 255; k++ ){
//    //            wprintf( L"\x1b[38;2;%d;%d;%dmHello,World!!\t", i, j, k );
//    //        }
//    //    }
//    //}
//
//    return 0;
//}
















////
////
////
////#include <Windows.h>
////#include <stdio.h>
////
/////************************************************************************/
/////* ���� DrawCircle
/////* ���� HDC hdc ��ͼ�ľ��
/////*      int x
/////*      int y   Բ�ĵ�x��y����
/////*      int r   Բ�İ뾶
/////*      COLORREF color      Բ�������ɫ
/////* ���� ��(x, y)����һ���뾶Ϊr��Բ����color����ɫ���
/////************************************************************************/
////void DrawCircle( HDC hdc, int x, int y, int r, COLORREF color ){
////    HBRUSH brush = (HBRUSH)CreateSolidBrush( color );        //�½�һ����ˢ
////    SelectObject( hdc, (HGDIOBJ)brush );                      //ѡ��ˢ
////    Ellipse( hdc, x - r, y - r, x + r, y + r );                       //��һ��Բ
////    DeleteObject( brush );                                    //ɾ����ˢ
////}
////
////int main(){
////    HWND console = GetConsoleWindow();                      //��ȡ����̨���ھ��
////    HDC  console_hdc = GetDC( console );                      //��ȡ��ͼdc
////    RECT rect;                                              //�����ͼ�����С�Ľṹ��
////    int x,
////        y,                          //С���xy����
////        dx = 3,                     //x������
////        dy = 3;                     //y������
////    int r = 0, g = 0, b = 0;        //С����ɫ
////    int speed;                      //С���ٶ�
////    COORD pos = { 0,4 };                //���λ��
////
////    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
////
////    GetClientRect( console, &rect );                          //���Ȼ�ȡ��ͼ����Ĵ�С
////
////    x = 10 + rand() % (rect.right);
////    y = 10 + rand() % (rect.bottom);
////
////    printf( "��ǰ���ڿ�� %d\n��ǰ���ڸ߶� %d\n������С����ɫ(r g b):", rect.right, rect.bottom );
////    scanf( "%d %d %d", &r, &g, &b );
////    printf( "������С���˶��ٶȣ�1~10��" );
////    scanf( "%d", &speed );
////    //rgb �ķ�Χ�ֱ���0~255
////    //255 255 255Ϊ��ɫ
////
////    if( speed <1 || speed > 10 || r >255 || r < 0 || g >255 || g < 0 || b >255 || g <0 ){
////        printf( "��Ч������" );
////        return 0;
////    }
////
////    while( 1 ){
////        SetConsoleCursorPosition( hOut, pos );                     //���ù��λ��
////        printf( "��ǰС��λ�� x= %d  \ty=%d  ", x, y );
////        DrawCircle( console_hdc, x, y, 10, RGB( r, g, b ) );        //��һ����ɫ��Բ
////        Sleep( 200 / speed );
////        DrawCircle( console_hdc, x, y, 10, RGB( 0, 0, 0 ) );        //��һ����ɫ��Բ��������
////
////        if( x > rect.right - 10 || x < 10 )
////            dx = -dx;
////
////        if( y > rect.bottom - 10 || y < 10 )
////            dy = -dy;
////
////        x += dx;
////        y += dy;
////    }
////
////    ReleaseDC( console, console_hdc );
////    return 0;
////}
