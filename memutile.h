#ifndef __MEMUTILE_H__
#define __MEMUTILE_H__

#include "mem_chk.h"


void* mem_getmem( __int32__ s );
void mem_freemem( void* p );
void mem_print( const __char__* format, ... );
void mem_assert( bool exp, int errorno, const char* file, int fileno );
__uint32__ mem_gettime();

__int32__ mem_getsysallocsize();

class CMemObject{
public:
    CMemObject();
    virtual ~CMemObject();
    void* operator new(size_t sz, const __char__* file, const size_t line);
    void operator delete(void* pointer, const __char__* file, const size_t line);
    void operator delete(void* pointer);
    void* operator new[]( size_t sz, const __char__* file, const size_t line );
    void operator delete[]( void* p, const __char__* file, const size_t line );
    void operator delete[]( void* p );
};



#define NEW2DARRAY( T, x, y ) _New2DArray<T>( x, y, __FILE__, __LINE__ )
#define DELETE2DARRAY( T, p ) _Delete2DArray<T>( p, __FILE__, __LINE__ );

template<class T>
T** _New2DArray( __int32__ x, __int32__ y, const char* file, __int32__ fileno ){
    T** p = (T**)MallocMemory( sizeof( T* ) * y, file, fileno );
    p[0] = (T*)MallocMemory( sizeof( T ) * (x * y), file, fileno );
    for( __int32__ i = 1; i < y; i++ )
        p[i] = p[i - 1] + x;
    return p;
}

template<class T>
inline void _Delete2DArray( T** p, const char* file, __int32__ fileno ){
    if( p ){
        FreeMemory( p[0], file, fileno );
        FreeMemory( p, file, fileno );
    }
    p = __NULL__;
}



#endif
