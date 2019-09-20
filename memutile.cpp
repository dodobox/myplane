
#include "memutile.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#define sys_mem_ext_int_count ( 2 )
static __int32__ mem_size = 0;

__int32__ mem_getsysallocsize(){
    printf( "--system all alloc size:%d\n", mem_size );
    return mem_size;
}

void* mem_getmem( __int32__ s ){
    int* _pData = (int*)::malloc( s + sizeof( int ) * sys_mem_ext_int_count );
    _pData[0] = CMemory::m_nFlag;
    _pData[1] = s;
    mem_size += s;
    return _pData + sys_mem_ext_int_count;
}
void mem_freemem( void* p ){
    int* _pData = ((int*)p) - sys_mem_ext_int_count;
    if( _pData[0] != CMemory::m_nFlag ){
        printf( "" );
        return;
    }
    mem_size -= _pData[1];
    ::free( _pData );
}
void mem_print( const __char__* format, ... ){
    char _strBuff[1024];
    va_list args;
    va_start( args, format );
    vsprintf( _strBuff, format, args );
    va_end( args );
    puts( _strBuff );
}
void mem_assert( bool exp, int errorno, const char* file, int fileno ){
    if( !exp ){
        printf( "assert file:%s fileno:%d errorno:%d\n", file, fileno, errorno );
    }
}
__uint32__ mem_gettime(){
    clock_t start= clock();
    return start;
}



CMemObject::CMemObject(){

}
CMemObject::~CMemObject(){

}
void* CMemObject::operator new(size_t sz, const __char__* file, const size_t line){
    return MallocMemory( sz, file, line );
}
void CMemObject::operator delete(void* pointer){
    if( 0 != pointer ){
        FREE( pointer );
    }
}
void CMemObject::operator delete(void* pointer, const __char__* file, const size_t line){
    operator delete(pointer);
}
void* CMemObject::operator new[]( size_t sz, const __char__* file, const size_t line ){
    return operator new(sz, file, line);
}
void CMemObject::operator delete[]( void* pointer ){
    operator delete(pointer);
}
void CMemObject::operator delete[]( void* pointer, const __char__* file, const size_t line ){
    operator delete(pointer);
}