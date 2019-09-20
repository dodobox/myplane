#include "mem_chk.h"


static CMemListNodePool sys_tMemListNodePool;
static CMemory sys_tMemory;
static func_getmem sys_pGetMem = __NULL__;
static func_freemem sys_pFreeMem = __NULL__;
static func_print sys_pPrint = __NULL__;
static func_assert sys_pAssert = __NULL__;
static func_gettime sys_pGetTime = __NULL__;

void InitMemory( __int32__ nMaxMemory, func_getmem pGetMem, func_freemem pFreeMem, func_print pPrint, func_assert pAssert, func_gettime pGetTime ){
    sys_pGetMem = pGetMem;
    sys_pFreeMem = pFreeMem;
    sys_pPrint = pPrint;
    sys_pAssert = pAssert;
    sys_pGetTime = pGetTime;
    sys_tMemListNodePool.Init( MEMLISTGROWCOUNT );
    sys_tMemory.Init( nMaxMemory );
}
void DumpIdle(){
    sys_tMemory.DumpIdle();
}
void DumpLeak(){
    sys_tMemory.DumpLeak();
}
void _StrCpy( __char__* strDesc, const __char__* strSrc, __int32__ nMaxLen ){
    __char__* _strDesc = strDesc;
    __char__* _strSrc = (__char__*)strSrc;
    __int32__ n = 0;
    nMaxLen --;
    while( *_strSrc && n < nMaxLen ){
        *_strDesc = *_strSrc;
        _strDesc ++;
        _strSrc ++;
        n ++;
    }
    *_strDesc = 0;
}

CLeakRangeList::CLeakRangeList(){
    m_pHead = __NULL__;
}
CLeakRangeList::~CLeakRangeList(){
    TListNode *_pNode;
    TListNode *_pOldNode = __NULL__;
    for( _pNode = m_pHead; _pNode; _pNode = _pOldNode ){
        _pOldNode = _pNode->next;
        sys_pFreeMem( _pNode );
    }
}

void CLeakRangeList::Push( __int32__ nStart, __int32__ nEnd ){
    TListNode *head = m_pHead;
    TListNode *node = (TListNode *)sys_pGetMem( sizeof( TListNode ) );
    node->m_tData.m_nStart = nStart;
    node->m_tData.m_nEnd = nEnd;
    node->next = __NULL__;
    if( head ){
        node->next = m_pHead;
    }
    m_pHead = node;
}
void CLeakRangeList::Erase( TListNode *pPrevNode, TListNode *pNode ){
    TListNode *head = m_pHead;
    if( pPrevNode == __NULL__ && pNode == head ){
        m_pHead = head->next;
        sys_pFreeMem( head );
        return;
    }
    pPrevNode->next = pNode->next;
    sys_pFreeMem( pNode );
    return;
}




CMemListNodePool::CMemListNodePool(){
    m_nBlockCount = 0;
    m_vPools = __NULL__;
}

CMemListNodePool::~CMemListNodePool(){

}

void CMemListNodePool::Init( __int32__ nBlockCount ){
    m_vPools = __NULL__;
    m_nBlockCount = nBlockCount;
    m_vPools = (TMemListNode*)sys_pGetMem( nBlockCount * sizeof( TMemListNode ) );
    
    for( __int32__ i = 0; i < nBlockCount; i ++ ){
        m_vPools[i].m_tMemInfo.m_nIndex = i;
        m_vPools[i].m_tMemInfo.m_nState = 0;
    }
}

TMemListNode* CMemListNodePool::GetMemory( __int32__ nAddress, __int32__ nSize, __int32__ nNextAddress, TMemListNode* &pHeadNode ){
    for( __int32__ i = 0; i < m_nBlockCount; i ++ ){
        if( m_vPools[i].m_tMemInfo.m_nState == 0 ){
            m_vPools[i].m_tMemInfo.m_nState = 1;
            m_vPools[i].m_tData.m_nAddress = nAddress;
            m_vPools[i].m_tData.m_nSize = nSize;
            m_vPools[i].m_tData.m_nNextAddress = nNextAddress;
            m_vPools[i].next = __NULL__;
            return &m_vPools[i];
        }
    }
    //空间不够了，再申请
    TMemListNode* _vPools = (TMemListNode*)sys_pGetMem( (m_nBlockCount + MEMLISTGROWCOUNT) * sizeof( TMemListNode ) );
    //复制原来的数据
    for( __int32__ i = 0; i < m_nBlockCount; i ++ ){
        _vPools[i].m_tMemInfo.m_nIndex = m_vPools[i].m_tMemInfo.m_nIndex;
        _vPools[i].m_tMemInfo.m_nState = m_vPools[i].m_tMemInfo.m_nState;
        _vPools[i].m_tData.m_nAddress = m_vPools[i].m_tData.m_nAddress;
        _vPools[i].m_tData.m_nSize = m_vPools[i].m_tData.m_nSize;
        _vPools[i].m_tData.m_nNextAddress = m_vPools[i].m_tData.m_nNextAddress;
        if( m_vPools[i].next == __NULL__ ){
            _vPools[i].next = __NULL__;
        } else{
            _vPools[i].next = _vPools + ( m_vPools[i].next->m_tMemInfo.m_nIndex );
        }
    }

    int _nHeadNodeID = pHeadNode->m_tMemInfo.m_nIndex;
    pHeadNode = _vPools + _nHeadNodeID;

    sys_pFreeMem( m_vPools ); 
    __int32__ _nBlockCount = m_nBlockCount;
    m_nBlockCount += MEMLISTGROWCOUNT;
    m_vPools = _vPools;

    for( __int32__ i = _nBlockCount; i < m_nBlockCount; i ++ ){
        _vPools[i].m_tMemInfo.m_nIndex = i;
        _vPools[i].m_tMemInfo.m_nState = 0;
    }

    m_vPools[_nBlockCount].m_tMemInfo.m_nState = 1;
    m_vPools[_nBlockCount].m_tData.m_nAddress = nAddress;
    m_vPools[_nBlockCount].m_tData.m_nSize = nSize;
    m_vPools[_nBlockCount].m_tData.m_nNextAddress = nNextAddress;
    m_vPools[_nBlockCount].next = __NULL__;
    return m_vPools + _nBlockCount;
}
void CMemListNodePool::FreeMemory( TMemListNode* p ){
    p->m_tMemInfo.m_nState = 0;
}




/////////////////////////////////////////////////////////////////
CMemory::CMemory(){
    m_nMemSize = 0;
    m_vMem = 0;
    m_vIdleListHead = __NULL__;
}
CMemory::~CMemory(){

}
void CMemory::Init( __int32__ nMemorySize ){
    m_nMemSize = nMemorySize;
    m_vMem = (__byte__*)sys_pGetMem( nMemorySize );
    list_push( 0, m_nMemSize, m_nMemSize );
}

void CMemory::list_push( __int32__ m_nAddress, __int32__ m_nSize, __int32__ m_nNextAddress ){
    TMemListNode *node = sys_tMemListNodePool.GetMemory( m_nAddress, m_nSize, m_nNextAddress, m_vIdleListHead );
    if( m_vIdleListHead ){
        node->next = m_vIdleListHead;
    }
    m_vIdleListHead = node;
}

__int32__ CMemory::list_erase( TMemListNode *pPrevNode, TMemListNode *pNode ){
    TMemListNode *head = m_vIdleListHead;
    if( pPrevNode == __NULL__ && pNode == head ){
        m_vIdleListHead = head->next;
        sys_tMemListNodePool.FreeMemory( head );
        return 1;
    }
    pPrevNode->next = pNode->next;
    sys_tMemListNodePool.FreeMemory( pNode );
    return 1;
}

__int32__ CMemory::GetMem( __int32__ nSize, const __char__* strFileName, __int32__ nFileNo, __int32__ nParame0, __int32__ nParame1 ){
    __int32__ _nAddr = -1;
    __int32__ _nAllocMemSize = sizeof( TAllocMemHeaderInfo ) + sizeof( TAllocMemTailInfo );
    __int32__ _nSize = nSize + _nAllocMemSize;
    TMemListNode *_pNode;
    TMemListNode *_pPrevNode = __NULL__;
    for( _pNode = m_vIdleListHead; _pNode; _pPrevNode = _pNode, _pNode = _pNode->next ){
        TIdleMemInfo& _tIdleMemInfo = _pNode->m_tData;
        if( _tIdleMemInfo.m_nSize == _nSize ){
            _nAddr = _tIdleMemInfo.m_nAddress;
            list_erase( _pPrevNode, _pNode );
            break;
        } else if( _tIdleMemInfo.m_nSize > _nSize ){
            if( _tIdleMemInfo.m_nSize <= _nAllocMemSize ){
                _nAddr = _tIdleMemInfo.m_nAddress;
                _nSize = _tIdleMemInfo.m_nSize;
                list_erase( _pPrevNode, _pNode );
            } else{
                _nAddr = _tIdleMemInfo.m_nAddress;
                _tIdleMemInfo.m_nAddress += _nSize;
                _tIdleMemInfo.m_nSize -= _nSize;
                _tIdleMemInfo.m_nNextAddress = _tIdleMemInfo.m_nAddress + _tIdleMemInfo.m_nSize;
            }
            break;
        }
    }
    sys_pAssert( _nAddr >= 0, error_allocfail, strFileName, nFileNo );
    if( _nAddr < 0 ){
        return -1;
    }
    _ClearMem( _nAddr, _nSize );    //清空
    TAllocMemHeaderInfo* _pAllocMemHeaderInfo = (TAllocMemHeaderInfo*)(m_vMem + _nAddr);
    TAllocMemTailInfo* _pAllocMemTailInfo = (TAllocMemTailInfo*)(m_vMem + (_nAddr + _nSize - sizeof( TAllocMemTailInfo )));
    _pAllocMemHeaderInfo->m_nFlag = m_nFlag;
    _pAllocMemHeaderInfo->m_nHeaderMD5Code = 0;
    _StrCpy( _pAllocMemHeaderInfo->m_strFileName, strFileName, MEMORYHEADERINFOFILENAMELEN );
    _pAllocMemHeaderInfo->m_nFileNo = nFileNo;
    _pAllocMemHeaderInfo->m_nTime = sys_pGetTime();
    _pAllocMemHeaderInfo->m_nUserData0 = nParame0;
    _pAllocMemHeaderInfo->m_nUserData1 = nParame1;
    _pAllocMemHeaderInfo->m_nAddress = _nAddr;
    _pAllocMemHeaderInfo->m_nUserSize = nSize;
    _pAllocMemHeaderInfo->m_nRealSize = _nSize;
    _pAllocMemTailInfo->m_nFlag = m_nFlag;
    _pAllocMemTailInfo->m_nHeaderMD5Code = 0;
    return _nAddr + sizeof( TAllocMemHeaderInfo );
}
bool CMemory::FreeMem( __int32__ nAddress, const char* filename, __int32__ line ){
    __int32__ _nAddr = nAddress - sizeof( TAllocMemHeaderInfo );
    TAllocMemHeaderInfo* _pAllocMemHeaderInfo = (TAllocMemHeaderInfo*)(m_vMem + _nAddr);
    sys_pAssert( m_nFlag == _pAllocMemHeaderInfo->m_nFlag, error_headerflagerror, filename, line );
    __int32__ _nSize = _pAllocMemHeaderInfo->m_nRealSize;
    TAllocMemTailInfo* _pAllocMemTailInfo = (TAllocMemTailInfo*)(m_vMem + (_nAddr + _nSize - sizeof( TAllocMemTailInfo )));
    sys_pAssert( m_nFlag == _pAllocMemTailInfo->m_nFlag, error_tailflagerror, filename, line );
    _ClearMem( _nAddr, _nSize );    //清空
    __int32__ _nNextAddr = _nAddr + _nSize;
    //合并处理
    bool _bMeg = false;
    TMemListNode *_pNode;
    TMemListNode *_pPrevNode = __NULL__;
    for( _pNode = m_vIdleListHead; _pNode; _pPrevNode = _pNode, _pNode = _pNode->next ){
        TIdleMemInfo& _tIdleMemInfo = _pNode->m_tData;
        if( _tIdleMemInfo.m_nAddress == _nNextAddr ){
            _tIdleMemInfo.m_nAddress -= _nSize;
            _tIdleMemInfo.m_nSize += _nSize;
            _tIdleMemInfo.m_nNextAddress = _tIdleMemInfo.m_nAddress + _tIdleMemInfo.m_nSize;
            if( Repair_IdleList0( _tIdleMemInfo.m_nAddress, _tIdleMemInfo.m_nSize ) == 1 ){
                list_erase( _pPrevNode, _pNode );
            }
            _bMeg = true;
            break;
        }
        if( _tIdleMemInfo.m_nNextAddress == _nAddr ){
            _tIdleMemInfo.m_nSize += _nSize;
            _tIdleMemInfo.m_nNextAddress = _tIdleMemInfo.m_nAddress + _tIdleMemInfo.m_nSize;
            //向前生长的
            if( Repair_IdleList1( _tIdleMemInfo.m_nNextAddress, _tIdleMemInfo.m_nSize ) == 1 ){
                list_erase( _pPrevNode, _pNode );
            }
            _bMeg = true;
            break;
        }
    }
    if( !_bMeg ){
        list_push( _nAddr, _nSize, _nAddr + _nSize );
    }
    return true;
}

__int32__ CMemory::Repair_IdleList0( __int32__ nAddr, __int32__ nSize ){
    TMemListNode *_pNode;
    for( _pNode = m_vIdleListHead; _pNode; _pNode = _pNode->next ){
        TIdleMemInfo& _tIdleMemInfo = _pNode->m_tData;
        if( _tIdleMemInfo.m_nNextAddress == nAddr ){
            _tIdleMemInfo.m_nSize += nSize;
            _tIdleMemInfo.m_nNextAddress = _tIdleMemInfo.m_nAddress + _tIdleMemInfo.m_nSize;
            return 1;
        }
    }
    return 0;
}

__int32__ CMemory::Repair_IdleList1( __int32__ nNextAddress, __int32__ nSize ){
    TMemListNode *_pNode;
    for( _pNode = m_vIdleListHead; _pNode; _pNode = _pNode->next ){
        TIdleMemInfo& _tIdleMemInfo = _pNode->m_tData;
        if( _tIdleMemInfo.m_nAddress == nNextAddress ){
            _tIdleMemInfo.m_nAddress -= nSize;
            _tIdleMemInfo.m_nSize += nSize;
            _tIdleMemInfo.m_nNextAddress = _tIdleMemInfo.m_nAddress + _tIdleMemInfo.m_nSize;
            return 1;
        }
    }
    return 0;
}

void CMemory::DumpIdle(){
    sys_pPrint("-------------DumpIdle--------------");
    TMemListNode *_pNode;
    __int32__ _nIdleSize = 0;
    for( _pNode = m_vIdleListHead; _pNode; _pNode = _pNode->next ){
        TIdleMemInfo& _tIdleMemInfo = _pNode->m_tData;
        _nIdleSize += _tIdleMemInfo.m_nSize;
        sys_pPrint( "IdleInfo addr:%d size:%d endaddr:%d", _tIdleMemInfo.m_nAddress, _tIdleMemInfo.m_nSize, _tIdleMemInfo.m_nNextAddress );
    }
    sys_pPrint( "--idle size: %d\n", _nIdleSize );
}

void CMemory::DumpLeak(){
    CLeakRangeList _vLeakRangeList;
    _vLeakRangeList.Push( 0, m_nMemSize );
    TMemListNode *_pNode;
    for( _pNode = m_vIdleListHead; _pNode; _pNode = _pNode->next ){
        TIdleMemInfo& _tIdleMemInfo = _pNode->m_tData;
        _BuildLeadSegmentList( _vLeakRangeList, _tIdleMemInfo.m_nAddress, _tIdleMemInfo.m_nNextAddress );
    }
    sys_pPrint( "------------DumpLeak---------------" );
    __int32__ _nLeakSize = 0;
    CLeakRangeList::TListNode *_pNode0;
    for( _pNode0 = _vLeakRangeList.m_pHead; _pNode0; _pNode0 = _pNode0->next ){
        CLeakRangeList::TLeakData& _tLeakRangeInfo = _pNode0->m_tData;
        _nLeakSize += _tLeakRangeInfo.m_nEnd - _tLeakRangeInfo.m_nStart;
        _DumpLeakRange( _tLeakRangeInfo.m_nStart, _tLeakRangeInfo.m_nEnd );
    }
    sys_pPrint( "-- leak size: %d\n", _nLeakSize );
}
void CMemory::_DumpLeakRange( __int32__ nStart, __int32__ nEnd ){
    if( nStart >= nEnd )return;
    __int32__ _nPos = nStart;
    do{
        _nPos = _DumpLeak( _nPos );
    } while( _nPos < nEnd );
}
__int32__ CMemory::_DumpLeak( __int32__ nAddr ){
    TAllocMemHeaderInfo* _pAllocMemHeaderInfo = (TAllocMemHeaderInfo*)(m_vMem + nAddr);
    sys_pAssert( m_nFlag == _pAllocMemHeaderInfo->m_nFlag, error_headerflagerror, __NULL__, 0 );
    __int32__ _nSize = _pAllocMemHeaderInfo->m_nRealSize;
    TAllocMemTailInfo* _pAllocMemTailInfo = (TAllocMemTailInfo*)(m_vMem + (nAddr + _nSize - sizeof( TAllocMemTailInfo )));
    sys_pAssert( m_nFlag == _pAllocMemTailInfo->m_nFlag, error_tailflagerror, __NULL__, 0 );
    sys_pPrint( "leak file:%s, row:%d, addr:%d, size:%d", _pAllocMemHeaderInfo->m_strFileName, _pAllocMemHeaderInfo->m_nFileNo, _pAllocMemHeaderInfo->m_nAddress, _pAllocMemHeaderInfo->m_nRealSize );
    return nAddr + _nSize;
}
void CMemory::_BuildLeadSegmentList( CLeakRangeList &vLeakRangeList, __int32__ nStart, __int32__ nEnd ){
    
    CLeakRangeList::TListNode *_pNode;
    CLeakRangeList::TListNode *_pPrevNode = __NULL__;
    for( _pNode = vLeakRangeList.m_pHead; _pNode; _pPrevNode = _pNode, _pNode = _pNode->next ){
        CLeakRangeList::TLeakData& _tLeakRangeInfo = _pNode->m_tData;
        if( nStart > _tLeakRangeInfo.m_nStart && nEnd < _tLeakRangeInfo.m_nEnd ){
            vLeakRangeList.Push( nEnd, _tLeakRangeInfo.m_nEnd );
            _tLeakRangeInfo.m_nEnd = nStart;
            break;
        }
        if( nStart == _tLeakRangeInfo.m_nStart && nEnd < _tLeakRangeInfo.m_nEnd ){
            _tLeakRangeInfo.m_nStart = nEnd;
            break;
        }
        if( nStart > _tLeakRangeInfo.m_nStart && nEnd == _tLeakRangeInfo.m_nEnd ){
            _tLeakRangeInfo.m_nEnd = nStart;
            break;
        }
        if( nStart == _tLeakRangeInfo.m_nStart && nEnd == _tLeakRangeInfo.m_nEnd ){
            vLeakRangeList.Erase( _pPrevNode, _pNode );
            break;
        }
    }
}
void CMemory::_ClearMem( __int32__ nStart, __int32__ nEnd ){
    for( __int32__ i = nStart; i < nEnd; i ++ ){
        m_vMem[i] = 0;
    }
}
void CMemory::CheckMemAll(){

}
bool CMemory::CheckMem( __int32__ nAddr ){
    TMemListNode *_pNode;
    for( _pNode = m_vIdleListHead; _pNode; _pNode = _pNode->next ){
        TIdleMemInfo& _tIdleMemInfo = _pNode->m_tData;
        if( nAddr >= _tIdleMemInfo.m_nAddress &&  nAddr <= _tIdleMemInfo.m_nNextAddress ){
            return false;
        }
    }
    return true;
}


//////////////////////////////////////////////////////////////////////////////////

void* MallocMemory( size_t sz, const __char__* file, const size_t line ){
    __int32__ _nAddr = sys_tMemory.GetMem( sz, file, line );
    void *p = sys_tMemory.m_vMem + _nAddr;
    return p;
}
void FreeMemory( void* p, const __char__* file, const size_t line ){
    __byte__* _address = (__byte__*)p;
    __int32__ _nAddr = _address - sys_tMemory.m_vMem;
    sys_pAssert( _nAddr >= 0 && _nAddr < sys_tMemory.m_nMemSize, error_memrangeerror, file, line );
    sys_pAssert( sys_tMemory.FreeMem( _nAddr, file, line ), error_unkown_error, file, line );
}
void CheckMem( void* p, const __char__* file, const size_t line ){
    __byte__* _address = (__byte__*)p;
    __int32__ _nAddr = _address - sys_tMemory.m_vMem;
    sys_pAssert( _nAddr >= 0 && _nAddr < sys_tMemory.m_nMemSize, error_memrangeerror, file, line );
    sys_pAssert( sys_tMemory.CheckMem( _nAddr ), error_unkown_error, file, line );
}