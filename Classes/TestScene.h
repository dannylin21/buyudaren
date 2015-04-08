
#ifndef __TEST_SCENE__
#define __TEST_SCENE__
#include "cocos2d.h"

class TestScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createTestScene();
	CREATE_FUNC(TestScene);
	static TestScene *m_testScene;
};




#endif //__TEST_SCENE__