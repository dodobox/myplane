#include <Windows.h>
#include <list>
#include <map>


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

//////#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)
//////
//////const WORD WhiteColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
//////const WORD RedColor = FOREGROUND_RED;
//////const WORD GreenColor = FOREGROUND_GREEN;
//////const WORD BlueColor = FOREGROUND_BLUE;
//////const WORD YellowColor = FOREGROUND_RED | FOREGROUND_GREEN;
//////
//////char g_nCode = '*';
//////
//////CHAR_INFO charInfoAarray[ 100 ][ 100 ];
//////
//////struct TPlane;
//////struct TGraphPT{
//////    TPlane* m_pPlane;
//////};
//////
//////TGraphPT g_vRedGraph[ 100 ][ 100 ];
//////TGraphPT g_vBlueGraph[ 100 ][ 100 ];
//////
//////void SetRedGraph( int x, int y, TPlane* pPlane ){
//////    if( x < 0 || x > 99 || y < 0 || y > 99 )return;
//////    g_vRedGraph[ y ][ x ].m_pPlane = pPlane;
//////}
//////
//////void SetBlueGraph( int x, int y, TPlane* pPlane ){
//////    if( x < 0 || x > 99 || y < 0 || y > 99 )return;
//////    g_vBlueGraph[ y ][ x ].m_pPlane = pPlane;
//////}
//////
//////
//////struct TPT{
//////    int x, y;
//////};
//////
//////void ClearScreen(){
//////    for( int i = 0; i < 100; i++ ){
//////        for( int j = 0; j < 100; j++ ){
//////            charInfoAarray[ i ][ j ].Attributes = 0;
//////            charInfoAarray[ i ][ j ].Char.AsciiChar = ' ';
//////        }
//////    }
//////}
//////
//////void SetScreenInfo( int x, int y, WORD attribute, char code ){
//////    if( x < 0 || x > 99 || y < 0 || y > 99 )return;
//////    charInfoAarray[ y ][ x ].Attributes = attribute;
//////    charInfoAarray[ y ][ x ].Char.AsciiChar = code;
//////}
//////
//////struct TBulletInfo{
//////    int m_nFlag;
//////    TPT pt;
//////    TPT originPT;
//////
//////    void Init( int nFlag, int _x, int _y ){
//////        m_nFlag = nFlag;
//////        pt.x = _x;
//////        pt.y = _y;
//////
//////        originPT.x = _x;
//////        originPT.y = _y;
//////    }
//////
//////    bool Update(){
//////        originPT.y = pt.y;
//////        pt.y -= 3;
//////        return pt.y > 0;
//////    }
//////
//////    void Draw(){
//////        SetScreenInfo( pt.x, pt.y, RedColor, '+' );
//////    }
//////};
//////
//////struct TBulletManager{
//////    void AddBullet( TBulletInfo *pBulletInfo ){
//////        m_vBulletList.push_back( pBulletInfo );
//////    }
//////    void Update(){
//////        for( std::list<TBulletInfo*>::iterator it = m_vBulletList.begin(); it != m_vBulletList.end(); ){
//////            TBulletInfo *_pBulletInfo = *it;
//////            if( _pBulletInfo->Update() ){
//////                it ++;
//////            } else{
//////                delete _pBulletInfo;
//////                it = m_vBulletList.erase( it );
//////            }
//////        }
//////    }
//////    void Draw(){
//////        for( std::list<TBulletInfo*>::iterator it = m_vBulletList.begin(); it != m_vBulletList.end(); it ++ ){
//////            TBulletInfo *_pBulletInfo = *it;
//////            _pBulletInfo->Draw();
//////        }
//////    }
//////    std::list<TBulletInfo*> m_vBulletList;
//////};
//////
//////TBulletManager g_tBulletManager;
//////
//////
//////
//////struct TPlane{
//////    virtual void Init( int x, int y ){}
//////    virtual bool Update(){ return false;  }
//////    virtual void Draw(){}
//////
//////    int m_nType;
//////    TPT pt;
//////    int hp;
//////
//////};
//////
//////struct PlayerPlane: public TPlane{
//////    PlayerPlane(){
//////        this->m_nType = 0;
//////        this->pt.x = 15;
//////        this->pt.y = 80;
//////        this->hp = 100;
//////    }
//////    
//////    virtual void Draw(){
//////        int _x = this->pt.x;
//////        int _y = this->pt.y - 2;
//////
//////        TPT _vShape[ 100 ];
//////        int _nShape = 0;
//////
//////        _vShape[ _nShape++ ] = { _x, _y + 0 };
//////        _vShape[ _nShape++ ] = { _x, _y + 1 };
//////        for( int i = _x - 5; i <= _x + 5; i ++ ){
//////            _vShape[ _nShape++ ] = { i, _y + 2 };
//////        }
//////        _vShape[ _nShape++ ] = { _x, _y + 3 };
//////        _vShape[ _nShape++ ] = { _x, _y + 4 };
//////        for( int i = _x - 2; i <= _x + 2; i ++ ){
//////            _vShape[ _nShape++ ] = { i, _y + 5 };
//////        }
//////        
//////        for( int i = 0; i < _nShape; i ++ ){
//////            SetScreenInfo( _vShape[i].x, _vShape[ i ].y, WhiteColor, g_nCode );
//////            //g_vRedGraph[ _vShape[ i ].y ][ _vShape[ i ].x ].m_pPlane = this;
//////            SetRedGraph( _vShape[ i ].x, _vShape[ i ].y, this );
//////        }        
//////    }
//////        
//////    virtual bool Update(){
//////        int _nLeft = KEYDOWN( 'A' );
//////        int _nRight = KEYDOWN( 'D' );
//////        int _nUp = KEYDOWN( 'W' );
//////        int _nDown = KEYDOWN( 'S' );
//////        int _nFire = KEYDOWN( VK_SPACE );
//////
//////
//////        if( _nLeft ){
//////            this->pt.x -= 3;
//////            if( this->pt.x < 5 ){
//////                this->pt.x = 5;
//////            }
//////        }
//////        if( _nRight ){
//////            this->pt.x += 3;
//////            if( this->pt.x > 93 ){
//////                this->pt.x = 93;
//////            }
//////        }
//////        if( _nUp ){
//////            this->pt.y -= 2;
//////
//////            if( this->pt.y < 2 ){
//////                this->pt.y = 2;
//////            }
//////
//////        }
//////        if( _nDown ){
//////            this->pt.y += 2;
//////            if( this->pt.y > 95 ){
//////                this->pt.y = 95;
//////            }
//////        }
//////        if( _nFire ){
//////            TBulletInfo* _pNewBuller = new TBulletInfo();
//////            _pNewBuller->Init( 0, this->pt.x, this->pt.y - 3 );
//////            g_tBulletManager.AddBullet( _pNewBuller  );
//////        }
//////        return hp > 0;
//////    }
//////};
//////
//////
//////struct TPlaneType0: public TPlane{
//////
//////    virtual void Init( int x, int y ){
//////        this->m_nType = 1;
//////        this->pt.x = x;
//////        this->pt.y = y;
//////        this->hp = 20;
//////    }
//////
//////    virtual void Draw(){
//////        int _x = this->pt.x;
//////        int _y = this->pt.y - 2;
//////
//////        TPT _vShape[ 100 ];
//////        int _nShape = 0;
//////
//////        _vShape[ _nShape++ ] = { _x - 3, _y - 1 };
//////        _vShape[ _nShape++ ] = { _x + 3, _y - 1 };
//////        _vShape[ _nShape++ ] = { _x - 2, _y + 0 };
//////        _vShape[ _nShape++ ] = { _x + 2, _y + 0 };
//////        _vShape[ _nShape++ ] = { _x - 1, _y + 1 };
//////        _vShape[ _nShape++ ] = { _x + 1, _y + 1 };
//////        _vShape[ _nShape++ ] = { _x, _y + 2 };
//////        _vShape[ _nShape++ ] = { _x, _y + 3 };
//////        _vShape[ _nShape++ ] = { _x, _y + 4 };
//////
//////        for( int i = 0; i < _nShape; i ++ ){
//////            SetScreenInfo( _vShape[ i ].x, _vShape[ i ].y, YellowColor, g_nCode );
//////            //g_vBlueGraph[ _vShape[ i ].y ][ _vShape[ i ].x ].m_pPlane = this;
//////            SetBlueGraph( _vShape[ i ].x, _vShape[ i ].y, this );
//////        }
//////    }
//////
//////    virtual bool Update(){
//////        this->pt.y ++;
//////        return ( this->pt.y < 110 ) && ( this->hp > 0 );
//////
//////    }
//////
//////};
//////
//////
//////
//////struct TPlaneManager{
//////    
//////    void AddPlane( TPlane *pPlane ){
//////        g_vPlaneList.push_back( pPlane );
//////    }
//////    void Update(){
//////        for( auto it = g_vPlaneList.begin(); it != g_vPlaneList.end(); ){
//////            TPlane *_pPlane = *it;
//////            if( _pPlane->Update() ){
//////                it ++;
//////            } else{
//////                it = g_vPlaneList.erase( it );
//////                delete _pPlane;
//////            }
//////        }
//////    }
//////    void Draw(){
//////        for( auto it = g_vPlaneList.begin(); it != g_vPlaneList.end(); it ++ ){
//////            TPlane *_pPlane = *it;
//////            _pPlane->Draw();
//////        }
//////    }
//////
//////    std::list<TPlane*> g_vPlaneList;
//////
//////};
//////
//////TPlaneManager g_PlaneManager;
//////
//////void DrawGround(){
//////    for( SHORT i = 0; i < 100; i ++ ){
//////        char _nCode = '*';
//////        SetScreenInfo( 99, i, WhiteColor, _nCode );
//////
//////        SetScreenInfo( i, 99, WhiteColor, _nCode );
//////    }
////// //   printf( "----------------------------------------------------------------------------------------------------\n" );
//////}
//////
//////int Rand( int v ){
//////    return rand() % v;
//////}
//////
//////void BulletCheckCollent(){
//////    auto &_vBullList = g_tBulletManager.m_vBulletList;
//////    for( auto it = _vBullList.begin(); it != _vBullList.end();  ){
//////        TBulletInfo* _pBullet = *it;
//////        TPT& _tPT = _pBullet->pt;
//////        TPT& _tOriginPT = _pBullet->originPT;
//////
//////        TPlane* _pColletPlane = NULL;
//////        int _x = _tOriginPT.x;
//////        int _nMinY = _tOriginPT.y < _tPT.y ? _tOriginPT.y : _tPT.y;
//////        int _nMaxY = _tOriginPT.y > _tPT.y ? _tOriginPT.y : _tPT.y;
//////        for( int _y = _nMinY; _y <= _nMaxY; _y ++ ){
//////            if( g_vBlueGraph[ _y ][ _x ].m_pPlane != NULL ){
//////                _pColletPlane = g_vBlueGraph[ _y ][ _x ].m_pPlane;
//////                break;
//////            }
//////        }
//////
//////        if( _pColletPlane ){
//////            _pColletPlane->hp -= 5;
//////            it = _vBullList.erase( it );
//////            delete _pBullet;
//////        } else{
//////            it ++;
//////        }
//////    }
//////}
//////
//////void PlaneCheckCollent(){
//////    std::map< TPlane*, TPlane* >_vPlaneMap;
//////    TPlane* _pPlayerPlane = NULL;
//////    for( int y = 0; y < 99; y ++ ){
//////        for( int x = 0; x < 99; x ++ ){
//////            if( g_vRedGraph[ y ][ x ].m_pPlane != NULL && g_vBlueGraph[ y ][ x ].m_pPlane != NULL ){
//////                _pPlayerPlane = g_vRedGraph[ y ][ x ].m_pPlane;
//////                _vPlaneMap[ g_vBlueGraph[ y ][ x ].m_pPlane ] = g_vBlueGraph[ y ][ x ].m_pPlane;
//////            }
//////        }
//////    }
//////    for( auto it = _vPlaneMap.begin(); it != _vPlaneMap.end(); it ++ ){
//////        TPlane* _pPlane = it->second;
//////        _pPlane->hp = 0;
//////        _pPlayerPlane->hp -= 20;
//////    }
//////}


int main(){
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
    //CCanvas* _pCanvas = CCanvas::CreateCanvas( ECT_DCCAVNAS, 100, 150 );
    CCanvas* _pCanvas = CCanvas::CreateCanvas( ECT_CONSOLECAVNAS, 100, 150 );
    //CCanvas* _pCanvas = CCanvas::CreateCanvas( ECT_TRUECOLORCONSOLECANVAS, 100, 150 );
    
    CCollisionMap* _pCollisionMap = CCollisionMap::GetInterface();
    CGUIManager* _pGUIManager = CGUIManager::GetInterface();

    CStageManager* _pStageManager = CStageManager::GetInterface();
    _pStageManager->ResetStage( 0 );
    _pPlaneManager->CreatePlayerPlane( EPT_TYPE0 );
    PlayBKSound("sound/background.wav");
    uint32 _nTime = GetTickCount();
    while( 1 ){
        uint32 _nCurTime = GetTickCount();
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
        Sleep( 33 );
    }
    CBulletMitterManager::Release();
    CStageManager::Release();
    CGUIManager::Release();
    CPlaneManager::Release();
    CBulletManager::Release();
    CCollisionMap::Release();
    DELETE( _pCanvas );
    CBehaviourControlManager::Release();
    CBulletBehaviourControlManager::Release();
    CBulletConfig::Release();
    CPlaneConfig::Release();
    CPictureManager::Release();

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
