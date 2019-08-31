#ifndef __UIIMAGE_H__
#define __UIIMAGE_H__

#include "uinode.h"
#include "picturemanager.h"

class CUIImage: public CUINode{
public:
    CUIImage();
    virtual ~CUIImage();
    virtual void Init();
    virtual void Final();
    virtual void Update( float fDelta );
    virtual void Draw( CCanvas* pCanvas );
    void SetImage( const char* strFileName );
    

private:
    CPictureInfo* m_pPicture;

};


#endif
