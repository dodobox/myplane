#ifndef __MEM_CHK_H__
#define __MEM_CHK_H__

#define __NULL__          (0)
typedef int             __int32__;
typedef unsigned int    __uint32__;
typedef unsigned char   __byte__;
typedef char            __char__;

typedef void*(*func_getmem)(__int32__);
typedef void(*func_freemem)(void*);
typedef void(*func_print)(const __char__*, ...);
typedef void(*func_assert )(bool, __int32__, const char*, int );
typedef __uint32__( *func_gettime )();

enum mem_error{
    error_allocfail,
    error_headerflagerror,
    error_tailflagerror,
    error_memrangeerror,
    error_unkown_error,
};

struct TListNodeMemInfo{
    __int32__ m_nIndex;   //索引
    __int32__ m_nState;   //使用状态
};

struct TIdleMemInfo{
    __int32__ m_nAddress;
    __int32__ m_nSize;
    __int32__ m_nNextAddress;
};

struct TMemListNode{
    TListNodeMemInfo m_tMemInfo;
    TIdleMemInfo m_tData;
    TMemListNode *next;
};

#define MEMLISTGROWCOUNT (16)
class CMemListNodePool{
public:
    CMemListNodePool();
    ~CMemListNodePool();
    void Init( __int32__ nBlockCount );
    TMemListNode* GetMemory( __int32__ nAddress, __int32__ nSize, __int32__ nNextAddress, TMemListNode*& pHeadNode );
    void FreeMemory( TMemListNode* p );
    __int32__ m_nBlockCount;
    TMemListNode* m_vPools;
};

class CLeakRangeList{
public:
    struct TLeakData{
        __int32__ m_nStart;
        __int32__ m_nEnd;
    };

    struct TListNode{
        TLeakData m_tData;
        TListNode *next;
    };

    CLeakRangeList();
    ~CLeakRangeList();
    void Push( __int32__ nStart, __int32__ nEnd );
    void Erase( TListNode *pPrevNode, TListNode *pNode );

    TListNode* m_pHead;
};

#define MEMORYHEADERINFOFILENAMELEN (128)
class CMemory{
    struct TAllocMemHeaderInfo{
        __int32__ m_nFlag;                    //标志
        __int32__ m_nHeaderMD5Code;           //MD5code
        __char__ m_strFileName[MEMORYHEADERINFOFILENAMELEN];        //文件名
        __int32__ m_nFileNo;                  //文件行号
        __uint32__ m_nTime;           //申请时间
        __int32__ m_nUserData0;               //用户数据0
        __int32__ m_nUserData1;               //用户数据1
        __int32__ m_nAddress;                 //地址
        __int32__ m_nUserSize;                //使用大小
        __int32__ m_nRealSize;                //实际大小
    };

    struct TAllocMemTailInfo{
        __int32__ m_nFlag;                   //标志
        __int32__ m_nHeaderMD5Code;          //MD5code
    };

    struct TLeakRangeDefine{
        __int32__ m_nStart;
        __int32__ m_nEnd;
    };

public:
    static const __int32__ m_nFlag = 'WFMM';
    CMemory();
    ~CMemory();
    void Init( __int32__ nMemorySize );
    __int32__ GetMem( __int32__ nSize, const __char__* strFileName, __int32__ nFileNo, __int32__ nParame0 = 0, __int32__ nParame1 = 0 );
    bool FreeMem( __int32__ nAddress, const char* filename, __int32__ line );
    void DumpIdle();
    void DumpLeak( );
    void CheckMemAll();
    bool CheckMem( __int32__ nAddr );

    __int32__ m_nMemSize;
    __byte__* m_vMem;
private:
    void _ClearMem( __int32__ nStart, __int32__ nEnd );
    void _BuildLeadSegmentList( CLeakRangeList &vLeakRangeList, __int32__ nStart, __int32__ nEnd );
    void _DumpLeakRange( __int32__ nStart, __int32__ nEnd );
    __int32__ _DumpLeak( __int32__ nAddr );
    __int32__ Repair_IdleList0( __int32__ nAddr, __int32__ nSize );
    __int32__ Repair_IdleList1( __int32__ nAddr, __int32__ nSize );

    void list_push( __int32__, __int32__, __int32__ );
    __int32__ list_erase( TMemListNode *, TMemListNode * );

    TMemListNode *m_vIdleListHead;
};

#ifdef NEW
#undef NEW
#endif
#define NEW new(__FILE__, __LINE__)

#ifdef DELETE
#undef DELETE
#endif
#define DELETE( p ) delete[] p, p = 0;

#ifdef MALLOC
#undef MALLOC
#endif
#define MALLOC( size ) MallocMemory(size, __FILE__, __LINE__ )

#ifdef FREE
#undef FREE
#endif
#define FREE( p ) FreeMemory( p, __FILE__, __LINE__ ), p =0;

#ifdef CHECK
#undef CHECK
#endif
#define CHECK( p ) (CheckMem( p, __FILE__, __LINE__ ) )


#ifdef SAFE
#undef SAFE
#endif
#define SAFE( p ) (CheckMem( p, __FILE__, __LINE__ ), p )


void InitMemory( __int32__ nMaxMemory, func_getmem, func_freemem, func_print, func_assert, func_gettime );
void DumpIdle();
void DumpLeak();
void CheckMem( void* p, const __char__* file, const size_t line );

void* MallocMemory( size_t sz, const __char__* file, const size_t line );
void FreeMemory( void* p, const __char__* file, const size_t line );


#endif
