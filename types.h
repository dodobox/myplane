#ifndef __TYPES_H__
#define __TYPES_H__


#define NULL 0

#define NEW new
#define DELETE( p ) if( p ) delete p, p = 0;
#define DELETEARRAY( p ) if( p ) delete[] p, p = 0;

typedef unsigned char byte;
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

enum EPlaneCamp{
    EPC_UNKOWN = -1,
    EPC_RED,
    EPC_BLUE,
};

enum EBehaviourType{
    EBT_UNKOWN = -1,
    EBT_KEYBOARD,
    EBT_MOUSE,
    EBT_TYPE0,
    EBT_COUNT,
};

enum EPlaneDirection{
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
    EET_0,      //刷飞机事件
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
    EAPT_5,
    EAPT_COUNT,
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


struct TIntPoint{
    int32 X, Y;
};
struct TFloatPoint{
    float X, Y;
};


#endif
