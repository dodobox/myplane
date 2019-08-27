#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"

uint32 HashStr( const char* str );
bool GetFileData( const char* strFileName, byte **pData, int32 *nSize );


#endif
