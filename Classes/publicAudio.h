#ifndef __PUBLIC_AUDIO_
#define __PUBLIC_AUDIO_

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

void PlayMusic(char* mstr, bool loop = false);

#ifndef BUBBLE
#define BUBBLE PlayMusic("music/eft_btn_bubble.mp3")
#endif

#endif __PUBLIC_AUDIO_