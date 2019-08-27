#include <Windows.h>
#include <list>
#include <map>


#include "consolecanvas.h"
#include "planemanager.h"
#include "behaviourcontrolmanager.h"
#include "picturemanager.h"
#include "planeconfig.h"

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)

const WORD WhiteColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD RedColor = FOREGROUND_RED;
const WORD GreenColor = FOREGROUND_GREEN;
const WORD BlueColor = FOREGROUND_BLUE;
const WORD YellowColor = FOREGROUND_RED | FOREGROUND_GREEN;

char g_nCode = '*';

CHAR_INFO charInfoAarray[ 100 ][ 100 ];

struct TPlane;
struct TGraphPT{
    TPlane* m_pPlane;
};

TGraphPT g_vRedGraph[ 100 ][ 100 ];
TGraphPT g_vBlueGraph[ 100 ][ 100 ];

void SetRedGraph( int x, int y, TPlane* pPlane ){
    if( x < 0 || x > 99 || y < 0 || y > 99 )return;
    g_vRedGraph[ y ][ x ].m_pPlane = pPlane;
}

void SetBlueGraph( int x, int y, TPlane* pPlane ){
    if( x < 0 || x > 99 || y < 0 || y > 99 )return;
    g_vBlueGraph[ y ][ x ].m_pPlane = pPlane;
}


struct TPT{
    int x, y;
};

void ClearScreen(){
    for( int i = 0; i < 100; i++ ){
        for( int j = 0; j < 100; j++ ){
            charInfoAarray[ i ][ j ].Attributes = 0;
            charInfoAarray[ i ][ j ].Char.AsciiChar = ' ';
        }
    }
}

void SetScreenInfo( int x, int y, WORD attribute, char code ){
    if( x < 0 || x > 99 || y < 0 || y > 99 )return;
    charInfoAarray[ y ][ x ].Attributes = attribute;
    charInfoAarray[ y ][ x ].Char.AsciiChar = code;
}

struct TBulletInfo{
    int m_nFlag;
    TPT pt;
    TPT originPT;

    void Init( int nFlag, int _x, int _y ){
        m_nFlag = nFlag;
        pt.x = _x;
        pt.y = _y;

        originPT.x = _x;
        originPT.y = _y;
    }

    bool Update(){
        originPT.y = pt.y;
        pt.y -= 3;
        return pt.y > 0;
    }

    void Draw(){
        SetScreenInfo( pt.x, pt.y, RedColor, '+' );
    }
};

struct TBulletManager{
    void AddBullet( TBulletInfo *pBulletInfo ){
        m_vBulletList.push_back( pBulletInfo );
    }
    void Update(){
        for( std::list<TBulletInfo*>::iterator it = m_vBulletList.begin(); it != m_vBulletList.end(); ){
            TBulletInfo *_pBulletInfo = *it;
            if( _pBulletInfo->Update() ){
                it ++;
            } else{
                delete _pBulletInfo;
                it = m_vBulletList.erase( it );
            }
        }
    }
    void Draw(){
        for( std::list<TBulletInfo*>::iterator it = m_vBulletList.begin(); it != m_vBulletList.end(); it ++ ){
            TBulletInfo *_pBulletInfo = *it;
            _pBulletInfo->Draw();
        }
    }
    std::list<TBulletInfo*> m_vBulletList;
};

TBulletManager g_tBulletManager;



struct TPlane{
    virtual void Init( int x, int y ){}
    virtual bool Update(){ return false;  }
    virtual void Draw(){}

    int m_nType;
    TPT pt;
    int hp;

};

struct PlayerPlane: public TPlane{
    PlayerPlane(){
        this->m_nType = 0;
        this->pt.x = 15;
        this->pt.y = 80;
        this->hp = 100;
    }
    
    virtual void Draw(){
        int _x = this->pt.x;
        int _y = this->pt.y - 2;

        TPT _vShape[ 100 ];
        int _nShape = 0;

        _vShape[ _nShape++ ] = { _x, _y + 0 };
        _vShape[ _nShape++ ] = { _x, _y + 1 };
        for( int i = _x - 5; i <= _x + 5; i ++ ){
            _vShape[ _nShape++ ] = { i, _y + 2 };
        }
        _vShape[ _nShape++ ] = { _x, _y + 3 };
        _vShape[ _nShape++ ] = { _x, _y + 4 };
        for( int i = _x - 2; i <= _x + 2; i ++ ){
            _vShape[ _nShape++ ] = { i, _y + 5 };
        }
        
        for( int i = 0; i < _nShape; i ++ ){
            SetScreenInfo( _vShape[i].x, _vShape[ i ].y, WhiteColor, g_nCode );
            //g_vRedGraph[ _vShape[ i ].y ][ _vShape[ i ].x ].m_pPlane = this;
            SetRedGraph( _vShape[ i ].x, _vShape[ i ].y, this );
        }        
    }
        
    virtual bool Update(){
        int _nLeft = KEYDOWN( 'A' );
        int _nRight = KEYDOWN( 'D' );
        int _nUp = KEYDOWN( 'W' );
        int _nDown = KEYDOWN( 'S' );
        int _nFire = KEYDOWN( VK_SPACE );


        if( _nLeft ){
            this->pt.x -= 3;
            if( this->pt.x < 5 ){
                this->pt.x = 5;
            }
        }
        if( _nRight ){
            this->pt.x += 3;
            if( this->pt.x > 93 ){
                this->pt.x = 93;
            }
        }
        if( _nUp ){
            this->pt.y -= 2;

            if( this->pt.y < 2 ){
                this->pt.y = 2;
            }

        }
        if( _nDown ){
            this->pt.y += 2;
            if( this->pt.y > 95 ){
                this->pt.y = 95;
            }
        }
        if( _nFire ){
            TBulletInfo* _pNewBuller = new TBulletInfo();
            _pNewBuller->Init( 0, this->pt.x, this->pt.y - 3 );
            g_tBulletManager.AddBullet( _pNewBuller  );
        }
        return hp > 0;
    }
};


struct TPlaneType0: public TPlane{

    virtual void Init( int x, int y ){
        this->m_nType = 1;
        this->pt.x = x;
        this->pt.y = y;
        this->hp = 20;
    }

    virtual void Draw(){
        int _x = this->pt.x;
        int _y = this->pt.y - 2;

        TPT _vShape[ 100 ];
        int _nShape = 0;

        _vShape[ _nShape++ ] = { _x - 3, _y - 1 };
        _vShape[ _nShape++ ] = { _x + 3, _y - 1 };
        _vShape[ _nShape++ ] = { _x - 2, _y + 0 };
        _vShape[ _nShape++ ] = { _x + 2, _y + 0 };
        _vShape[ _nShape++ ] = { _x - 1, _y + 1 };
        _vShape[ _nShape++ ] = { _x + 1, _y + 1 };
        _vShape[ _nShape++ ] = { _x, _y + 2 };
        _vShape[ _nShape++ ] = { _x, _y + 3 };
        _vShape[ _nShape++ ] = { _x, _y + 4 };

        for( int i = 0; i < _nShape; i ++ ){
            SetScreenInfo( _vShape[ i ].x, _vShape[ i ].y, YellowColor, g_nCode );
            //g_vBlueGraph[ _vShape[ i ].y ][ _vShape[ i ].x ].m_pPlane = this;
            SetBlueGraph( _vShape[ i ].x, _vShape[ i ].y, this );
        }
    }

    virtual bool Update(){
        this->pt.y ++;
        return ( this->pt.y < 110 ) && ( this->hp > 0 );

    }

};



struct TPlaneManager{
    
    void AddPlane( TPlane *pPlane ){
        g_vPlaneList.push_back( pPlane );
    }
    void Update(){
        for( auto it = g_vPlaneList.begin(); it != g_vPlaneList.end(); ){
            TPlane *_pPlane = *it;
            if( _pPlane->Update() ){
                it ++;
            } else{
                it = g_vPlaneList.erase( it );
                delete _pPlane;
            }
        }
    }
    void Draw(){
        for( auto it = g_vPlaneList.begin(); it != g_vPlaneList.end(); it ++ ){
            TPlane *_pPlane = *it;
            _pPlane->Draw();
        }
    }

    std::list<TPlane*> g_vPlaneList;

};

TPlaneManager g_PlaneManager;

void DrawGround(){
    for( SHORT i = 0; i < 100; i ++ ){
        char _nCode = '*';
        SetScreenInfo( 99, i, WhiteColor, _nCode );

        SetScreenInfo( i, 99, WhiteColor, _nCode );
    }
 //   printf( "----------------------------------------------------------------------------------------------------\n" );
}

int Rand( int v ){
    return rand() % v;
}

void BulletCheckCollent(){
    auto &_vBullList = g_tBulletManager.m_vBulletList;
    for( auto it = _vBullList.begin(); it != _vBullList.end();  ){
        TBulletInfo* _pBullet = *it;
        TPT& _tPT = _pBullet->pt;
        TPT& _tOriginPT = _pBullet->originPT;

        TPlane* _pColletPlane = NULL;
        int _x = _tOriginPT.x;
        int _nMinY = _tOriginPT.y < _tPT.y ? _tOriginPT.y : _tPT.y;
        int _nMaxY = _tOriginPT.y > _tPT.y ? _tOriginPT.y : _tPT.y;
        for( int _y = _nMinY; _y <= _nMaxY; _y ++ ){
            if( g_vBlueGraph[ _y ][ _x ].m_pPlane != NULL ){
                _pColletPlane = g_vBlueGraph[ _y ][ _x ].m_pPlane;
                break;
            }
        }

        if( _pColletPlane ){
            _pColletPlane->hp -= 5;
            it = _vBullList.erase( it );
            delete _pBullet;
        } else{
            it ++;
        }
    }
}

void PlaneCheckCollent(){
    std::map< TPlane*, TPlane* >_vPlaneMap;
    TPlane* _pPlayerPlane = NULL;
    for( int y = 0; y < 99; y ++ ){
        for( int x = 0; x < 99; x ++ ){
            if( g_vRedGraph[ y ][ x ].m_pPlane != NULL && g_vBlueGraph[ y ][ x ].m_pPlane != NULL ){
                _pPlayerPlane = g_vRedGraph[ y ][ x ].m_pPlane;
                _vPlaneMap[ g_vBlueGraph[ y ][ x ].m_pPlane ] = g_vBlueGraph[ y ][ x ].m_pPlane;
            }
        }
    }
    for( auto it = _vPlaneMap.begin(); it != _vPlaneMap.end(); it ++ ){
        TPlane* _pPlane = it->second;
        _pPlane->hp = 0;
        _pPlayerPlane->hp -= 20;
    }
}


int main(){
    //    936 GBK( 一般情况下为默认编码 )
    //    437 美国英语
    //    65001 utf - 8
    system( "chcp 437" );
    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    CHAR_INFO CharInfo;

    COORD size = { 100, 100 };
    SetConsoleScreenBufferSize( hOut, size ); // 重新设置缓冲区大小
    ////                                          //_getch();
    SMALL_RECT rc = { 0,0, 1024 - 1, 1024 - 1 }; // 重置窗口位置和大小
    SetConsoleWindowInfo( hOut, true, &rc );

    CPictureManager::GetInterface();
    CPlaneConfig::GetInterface();
    CBehaviourControlManager::GetInterface();

    CCanvas* _pCanvas = CCanvas::CreateCanvas( ECT_CONSOLECAVNAS, 90, 110 );
    CPlaneManager* _pPlaneManager = CPlaneManager::GetInterface();
    _pPlaneManager->AddPlane( EPT_TYPE0, 50, 50, EPD_S, EBT_KEYBOARD, EPC_RED );
    
    while( 1 ){
        _pPlaneManager->Update( 0 );
        _pCanvas->Clear();
        _pPlaneManager->Draw( _pCanvas );
        _pCanvas->Show();
        Sleep( 33 );
    }
    CPlaneManager::Release();
    DELETE( _pCanvas );
    CBehaviourControlManager::Release();
    CPlaneConfig::Release();
    CPictureManager::Release();

    system("pause");

    return 0;
}

