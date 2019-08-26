#include "picturemanager.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

static CPictureManager* _pThis = NULL;
CPictureManager* CPictureManager::GetInterface(){
    if( _pThis == NULL ){
        _pThis = NEW CPictureManager();
        _pThis->Init();
    }
    return _pThis;
}
void CPictureManager::Release(){
    if( _pThis ){
        _pThis->Final();
        DELETE( _pThis );
    }
}
CPictureManager::CPictureManager(){

}
CPictureManager::~CPictureManager(){

}
void CPictureManager::Init(){
    const int32 _nPictureCount = 1;
    const char* _vPictureFileName[_nPictureCount] = {
        "plane0.png",
    };

    for( int32 i = 0; i < _nPictureCount; i ++ ){
        int32 x, y, dummy;
        byte* _pData = stbi_load( _vPictureFileName[ i ], &x, &y, &dummy, 0 );
        if( _pData ){
            CPictureInfo* _pPictureInfo = NEW CPictureInfo();
            _pPictureInfo->m_nID = i;
            _pPictureInfo->m_nWidth = x;
            _pPictureInfo->m_nHeight = y;
            _pPictureInfo->m_nChannel = dummy;
            _pPictureInfo->m_pData = _pData;
            m_vPictureInfoList.push_back( _pPictureInfo );
        } else{
            m_vPictureInfoList.push_back( NULL );
        }
    }
    
}
void CPictureManager::Final(){

}