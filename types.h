#ifndef __TYPES_H__
#define __TYPES_H__

#ifdef NULL
#undef NULL
#endif
#define NULL 0

#ifdef NEW
#undef NEW
#endif
#define NEW new

#ifdef DELETE
#undef DELETE
#endif
#define DELETE( p ) if( p ) delete p, p = 0;

#ifdef DELETEARRAY
#undef DELETEARRAY
#endif
#define DELETEARRAY( p ) if( p ) delete[] p, p = 0;

typedef unsigned char byte;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef void* object32;


template<class T>
T** New2DArray( int32 x, int32 y ){
    T** p = NEW T*[ y ];
    p[ 0 ] = NEW T[ x * y ];
    for( int32 i = 1; i < y; i++ )
        p[ i ] = p[ i - 1 ] + x;
    return p;
}

template<class T>
void Delete2DArray( T** &p ){
    if( p ){
        delete[] p[ 0 ];
        delete[] p;
    }
    p = NULL;
}

enum ECanvasType{
    ECT_UNKOWN = -1,
    ECT_CONSOLECAVNAS,
    ECT_DCCAVNAS,
    ECT_DATACANVAS,
};

enum EPlaneType{
    EPT_UNKOWN = -1,
    EPT_TYPE0,
    EPT_TYPE1,
    EPT_TYPE2,
    EPT_TYPE3,
    EPT_TYPE4,
    EPT_TYPE5,
    EPT_COUNT,
};

enum ESpriteCamp{
    EPC_UNKOWN = -1,
    EPC_RED,
    EPC_BLUE,
    EPC_COUNT,
};

enum EPlaneBehaviourType{
    EPBT_UNKOWN = -1,
    EPBT_KEYBOARD,
    EPBT_MOUSE,
    EPBT_TYPE0,
    EPBT_COUNT,
};

enum ESpriteDirection{
    EPD_UNKOWN = -1,
    EPD_E,  //东
    EPD_S,  //南
    EPD_W,  //西
    EPD_N,  //北
};

enum EPicture{
    EP_Plane0,
    EP_Count,
};

enum EEventType{    //事件类型
    EET_0,      //
    EET_1,      
    EET_2,
    EET_3,
    EET_4,
    EET_COUNT,
};

enum EAppearPositionType{
    EAPT_0,
    EAPT_1,
    EAPT_2,
    EAPT_3,
    EAPT_4,
    EAPT_COUNT,
    EAPT_RAND = 10,
};

enum ETriggerType{  //触发器
    ETT_0,      //距离触发
    ETT_1,
    ETT_2,
    ETT_3,
    ETT_4,
    ETT_5,
    ETT_6,
    ETT_COUNT,
};

enum EBulletType{
    EBT_UNKOWN = -1,
    EBT_0,
    EBT_1,
    EBT_2,
    EBT_3,
    EBT_4,
    EBT_COUNT,
};

enum EBulletBehaviourType{
    EBBT_UNKOWN = -1,
    EBBT_0,
    EBBT_1,
    EBBT_2,
    EBBT_COUNT,
};

enum EBulletEmitterType{
    EBET_UNKOWN = -1,
    EBET_0,
    EBET_1,
    EBET_COUNT,
};

enum EUIType{
    EUT_NODE,
    EUT_UIMANAGER,
    EUT_LABEL,
    EUT_IMAGE,
    EUT_INFOMATIONDLG,
};

struct TIntPoint{
    int32 X, Y;
};
struct TFloatPoint{
    float X, Y;
};
struct TIntRect{
    int32 m_nLeft, m_nTop, m_nRight, m_nBottom;
};
struct TColor{
    union{
        struct{
            byte R;
            byte G;
            byte B;
            byte A;
        }RGBA;
        uint32 C;
    };
};


#endif
