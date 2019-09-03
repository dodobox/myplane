#include "sound.h"
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

void PlayBKSound( const char* strFileName ){
    //::PlaySound( strFileName, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
}
void PlayEffectSound( EEffectSound eSound ){
   // ::PlaySound( "sound/ball.wav", NULL, SND_FILENAME | SND_ASYNC );
    
}