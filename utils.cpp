#include "utils.h"
#include <stdio.h>

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
