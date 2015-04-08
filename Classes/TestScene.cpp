#include "TestScene.h"


USING_NS_CC;
TestScene* TestScene::m_testScene = nullptr;

Scene* TestScene::createTestScene()
{
	auto scene = Scene::create();
	auto layer = TestScene::create();
	TestScene::m_testScene = layer;
	scene->addChild(layer);
	return scene;
}