#include "keyboardcontrol.h"
#include <Windows.h>
#include "plane.h"
#include "canvas.h"
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)


CKeyboardControl::CKeyboardControl():
CBehaviourControl(){
    m_eBehaviourType = EPBT_KEYBOARD;
}
CKeyboardControl::~CKeyboardControl(){

}
void CKeyboardControl::Init(){

}
void CKeyboardControl::Final(){

}
void CKeyboardControl::Update( CPlane* pPlane, float fDelta ){
    int32 _nLeft = KEYDOWN( 'A' );
    int32 _nRight = KEYDOWN( 'D' );
    int32 _nUp = KEYDOWN( 'W' );
    int32 _nDown = KEYDOWN( 'S' );
    int32 _nFire = KEYDOWN( VK_SPACE );

    float _fX = pPlane->m_tPosition.X;
    float _fY = pPlane->m_tPosition.Y;

    float _fWidth = CCanvas::m_tCanvasSize.X;
    float _fHeight = CCanvas::m_tCanvasSize.Y;

    float _fSpeed = pPlane->m_fSpeed;

    if( _nLeft ){
        _fX -= _fSpeed * fDelta;
        if( _fX < 0.0f ){
            _fX = 0.0f;
        }
    }
    if( _nRight ){
        _fX += _fSpeed * fDelta;
        if( _fX > _fWidth ){
            _fX = _fWidth;
        }
    }
    if( _nUp ){
        _fY -= _fSpeed * fDelta;
        if( _fY < 0.0f ){
            _fY = 0.0f;
        }

    }
    if( _nDown ){
        _fY += _fSpeed * fDelta;
        if( _fY > _fHeight ){
            _fY = _fHeight;
        }
    }
    if( _nFire ){
        pPlane->Fire( 0 );
    }

    pPlane->m_tPosition.X = _fX;
    pPlane->m_tPosition.Y = _fY;

}