#include "picture.h"
#include <stdlib.h>

CPictureInfo::CPictureInfo():
m_nKey( 0 ),
m_nWidth( 0 ),
m_nHeight( 0 ),
m_nChannel( 0 ),
m_pData( NULL ){

}
CPictureInfo::~CPictureInfo(){
    //DELETEARRAY( m_pData );
    free( m_pData );
}