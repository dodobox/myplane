#include "keyboardcontrol.h"
#include <Windows.h>
#include "plane.h"
#include "canvas.h"
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)


CKeyboardControl::CKeyboardControl():
CBehaviourControl(){
    m_eBehaviourType = EBT_KEYBOARD;
}
CKeyboardControl::~CKeyboardControl(){

}
void CKeyboardControl::Init(){

}
void CKeyboardControl::Final(){

}
void CKeyboardControl::Update( CPlane* pPlane, float fDelta ){
    int _nLeft = KEYDOWN( 'A' );
    int _nRight = KEYDOWN( 'D' );
    int _nUp = KEYDOWN( 'W' );
    int _nDown = KEYDOWN( 'S' );
    int _nFire = KEYDOWN( VK_SPACE );

    float _fX = pPlane->m_tPosition.X;
    float _fY = pPlane->m_tPosition.Y;

    CCanvas* _pCanvas = CCanvas::GetInterface();
    float _fWidth = _pCanvas->m_tSize.X;
    float _fHeight = _pCanvas->m_tSize.Y;

    if( _nLeft ){
        _fX -= 3.0f;
        if( _fX < 0.0f ){
            _fX = 0.0f;
        }
    }
    if( _nRight ){
        _fX += 3.0f;
        if( _fX > _fWidth ){
            _fX = _fWidth;
        }
    }
    if( _nUp ){
        _fY -= 2.0f;
        if( _fY < 0.0f ){
            _fY = 0.0f;
        }

    }
    if( _nDown ){
        _fY += 2.0f;
        if( _fY > _fHeight ){
            _fY = _fHeight;
        }
    }

    pPlane->m_tPosition.X = _fX;
    pPlane->m_tPosition.Y = _fY;

    //if( _nFire ){
    //    TBulletInfo* _pNewBuller = new TBulletInfo();
    //    _pNewBuller->Init( 0, this->pt.x, this->pt.y - 3 );
    //    g_tBulletManager.AddBullet( _pNewBuller );
    //}
    //return hp > 0;


}