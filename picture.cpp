#include "picture.h"

CPictureInfo::CPictureInfo():
//m_nID( 0 ),
m_nWidth( 0 ),
m_nHeight( 0 ),
m_nChannel( 0 ),
m_pData( NULL ){

}
CPictureInfo::~CPictureInfo(){
    DELETEARRAY( m_pData );
}