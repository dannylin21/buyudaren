#include "publicAudio.h"
#include "LoadScene.h"


void PlayMusic(char* mstr, bool loop)
{
	if(LoadScene::duangOpen)
		AudioEngine::play2d(mstr, loop);
}
