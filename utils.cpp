#include "utils.h"
#include <stdio.h>
#include <stdarg.h>

bool GetFileData( const char* strFileName, byte **pData, int32 *nSize ){
    FILE* f = fopen( strFileName, "rb" );
    if( f == NULL ){
        return false;
    }

    fseek( f, 0, SEEK_SET );
    fseek( f, 0, SEEK_END );
    int32 _nSize = ftell( f );
    fseek( f, 0, SEEK_SET );

    if( _nSize == 0 ){
        fclose( f );
        return false;
    }
    byte *_pData = NEW byte[_nSize + 1];
    fread( _pData, _nSize, 1, f );
    _pData[_nSize] = 0;
    fclose( f );
    *pData = _pData;
    *nSize = _nSize;
    return true;
}

uint32 HashStr( const char* str ){
    uint32 h = 0;
    byte *p;
    byte n;
    for( h = 0, p = (byte*)str; *p; p ++ ){
        n = *p;
        if( n == '/' ){
            n = '\\';
        }
        h = 33 * h + n;
    }
    return h;
}

char* FormatStr( char* str, const char* strFormat, ... ){
    va_list va;
    va_start( va, strFormat );
    _vsprintf_p( str, 2048, strFormat, va );
    va_end( va );
    return str;
}
int32 FormatStr1( char* str, const char* strFormat, ... ){
    int32 _nRet = 0;
    va_list va;
    va_start( va, strFormat );
    _nRet = _vsprintf_p( str, 2048, strFormat, va );
    va_end( va );
    return _nRet;
}

static uint32 next = 1;
static const int32 __RAND_MAX__ = 32768;
void SRand( uint32 nValue ){
    next = nValue * 1103515245 + 12345;
}
int32 Rand(){
    next = next * 1103515245 + 12345;
    return ((uint32)(next / 65536) % __RAND_MAX__);
}
int32 Rand( int32 nMax ){
    if( nMax == 0 ) return 0;
    return Rand() % (nMax);
}
int32 Rand( int32 nMin, int32 nMax ){
    if( nMin == nMax ) return nMin;
    return nMin + Rand() % (nMax - nMin);
}
float fRand(){
    return (float)Rand() / (float)__RAND_MAX__;
}
float fRand( float fMax ){
    return (float)Rand( 0.0f, fMax );
}
float fRand( float lower, float upper ){
    return lower + (upper - lower)*(Rand());
}
int32 RandIntArray( int32* pArray, int32 nCount ){
    for( int32 i = 0; i < nCount; ++i ){
        int32 index = Rand( i + 1 ) % (i + 1);
        if( index != i ){
            pArray[i] = pArray[i] ^ pArray[index];
            pArray[index] = pArray[i] ^ pArray[index];
            pArray[i] = pArray[i] ^ pArray[index];
        }
    }
    return 0;
}