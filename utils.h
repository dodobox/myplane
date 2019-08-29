#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"

#define GETALPHA( c, a ) ( a = (byte)((c & 0xFF000000) >> 24) )
#define GETCOLORARGB( c, a, r, g, b ) ( a = (byte)((c & 0xFF000000) >> 24), b = (byte)((c & 0x00FF0000) >> 16), g = (byte)((c & 0x0000FF00) >> 8), r = (byte)(c & 0x000000FF) )
#define GETCOLORRGB( c, r, g, b ) ( b = (byte)((c & 0x00FF0000) >> 16), g = (byte)((c & 0x0000FF00) >> 8), r = (byte)(c & 0x000000FF) )
#define MAKECOLOR32( a, r, g, b ) (uint32(((a & 0xff) << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff)))
#define MAKEINT32( a, b ) ( a << 16 | b )


uint32 HashStr( const char* str );
bool GetFileData( const char* strFileName, byte **pData, int32 *nSize );
char* FormatStr( char* str, const char* strFormat, ... );
int32 FormatStr1( char* str, const char* strFormat, ... );
void SRand( uint32 nValue );
int32 Rand();
int32 Rand( int32 nMax );
int32 Rand( int32 nMin, int32 nMax );
float fRand();
float fRand( float fMax );
float fRand( float lower, float upper );


template<class T>inline const T& Min( const T& a, const T& b ){
    return a < b ? a : b;
}
template<class T>inline const T&  Min( const T&  a, const T&  b, const T&  c ){
    return ((a < b ? a : b)  < c) ? (a < b ? a : b) : c;
}

template<class T>inline const T&  Max( const T&  a, const T&  b ){
    return a < b ? b : a;
}
template<class T>inline const T&  Max( const T&  a, const T&  b, const T&  c ){
    return ((a>b ? a : b) >c) ? (a>b ? a : b) : c;
}
template<class T>inline const T&  Mid( const T&  a, const T&  b, const T&  c ){
    return a < b ? b : (a > c ? c : a);
}
template <class T>
inline T Distance( const T& x0, const T& y0, const T& x1, const T& y1 ){
    T nx = x0 - x1;
    T ny = y0 - y1;
    T _fLen = nx * nx + ny * ny;
    return _fLen;
}
template <class T>
inline bool PointInRect( const T x, const T y, const T left, const T top, const T right, const T bottom ){
    return x >= left && x <= right && y >= top && y <= bottom;
}

template <class T>
inline bool RectIntersectRect( const T x01, const T y01, const T x02, const T y02, const T x11, const T y11, const T x12, const T y12 ){
    float zx = Abs<T>( x01 + x02 - x11 - x12 );
    float x = Abs<T>( x01 - x02 ) + Abs<T>( x11 - x12 );
    float zy = Abs<T>( y01 + y02 - y11 - y12 );
    float y = Abs<T>( y01 - y02 ) + Abs<T>( y11 - y12 );
    return (zx <= x && zy <= y);
}
template<class T>
inline T Abs( const T& a ){
    return a < (T)0 ? -a : a;
}

template <class T>
inline const T Clamp( const T& value, const T& low, const T& high ){
    return Min( Max( value, low ), high );
}

#endif
