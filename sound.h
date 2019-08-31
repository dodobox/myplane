#ifndef __SOUND_H__
#define __SOUND_H__

enum EEffectSound{
    EES_0,
};

void PlayBKSound( const char* strFileName );
void PlayEffectSound( EEffectSound eSound );


#endif

