#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HRocker.h"
USING_NS_CC;
#define MAP_SIZE 1280

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	map = TMXTiledMap::create("tile maps/1.tmx");
	meta = map->layerNamed("meta");
	if (meta) {
		log("ok");
	}
	addChild(map, 0);
	log("%f,%f", map->getPositionX(), map->getPositionY());
	//HRocker* rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", Vec2(100, 100));
	//map->addChild(rocker,10);
	//rocker->startRocker(true);

   

	size = Director::getInstance()->getVisibleSize();
    
	/*�����ĸ�����ť
	auto pLeft = MenuItemImage::create("left.png", "left.png", this,menu_selector(GameScene::left));
	auto pRight = MenuItemImage::create("right.png", "right.png", this, menu_selector(GameScene::right));
	auto pUp = MenuItemImage::create("up.png", "up.png", this, menu_selector(GameScene::up));
	auto pDown = MenuItemImage::create("down.png", "down.png", this, menu_selector(GameScene::down));
	auto left = Menu::create(pLeft, NULL);
	auto right = Menu::create(pRight, NULL);
	auto up = Menu::create(pUp, NULL);
	auto down = Menu::create(pDown, NULL);
	left->setPosition(16 + 32, 16 + 32 * 2);
	right->setPosition(16 + 32 * 3, 16 + 32 * 2);
	up->setPosition(16 + 32 * 2, 16 + 32 * 3);
	down->setPosition(16 + 32 * 2, 16 + 32);
	addChild(left, 10);
	addChild(right, 10);
	addChild(down, 10);
	addChild(up, 10);
    */


	//���Ӽ����¼�
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* unused_event) {
		switch(keycode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW: if (!(keyDownHolding || keyLeftHolding || keyRightHolding)) {
			keyUpHolding = true; GameScene::up(this); this->schedule(schedule_selector(GameScene::keyup), 0.15f); break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW: if (!(keyUpHolding || keyLeftHolding || keyRightHolding)) {
			keyDownHolding = true; GameScene::down(this); this->schedule(schedule_selector(GameScene::keydown), 0.15f); break;
		}
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW: if (!(keyDownHolding || keyUpHolding || keyRightHolding)) {
			keyLeftHolding = true; GameScene::left(this); this->schedule(schedule_selector(GameScene::keyleft), 0.15f); break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: if (!(keyDownHolding || keyUpHolding || keyLeftHolding)) {
			keyRightHolding = true; GameScene::right(this); this->schedule(schedule_selector(GameScene::keyright), 0.15f); break;
		}
		}
		
};
	keyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event* unused_event) {
		switch (keycode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW: keyUpHolding = false; this->unschedule(schedule_selector(GameScene::keyup)); break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW: keyDownHolding = false; this->unschedule(schedule_selector(GameScene::keydown)); break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW: keyLeftHolding = false; this->unschedule(schedule_selector(GameScene::keyleft)); break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: keyRightHolding = false; this->unschedule(schedule_selector(GameScene::keyright)); break;
			}
		
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	//






	littleman = Sprite::create("contact.png");
	map->addChild(littleman, 9);
	littleman->setPosition(112, 144 + 4 * 32);

    
    return true;
}

void GameScene::up(Ref * psender)
{
	float y = littleman->getPositionY();
	if (y + 16 < MAP_SIZE && isCanReach(littleman->getPositionX(),y+32)  ) {
		auto action = MoveBy::create(0.12f, Vec2(0, 32));
		littleman->runAction(action);
		if ((y + map->getPositionY() > size.height / 2) && ((MAP_SIZE - y) > size.height / 2)) {
			auto action = MoveBy::create(0.12f, Vec2(0, -32));
			map->runAction(action);
		}
	}
}

void GameScene::left(Ref * psender)
{
	float x = littleman->getPositionX();
	if (x - 16 > 0 && isCanReach(x-32,littleman->getPositionY())  ){
		auto action = MoveBy::create(0.12f, Vec2(-32, 0));
		littleman->runAction(action);
		if ((x + map->getPositionX() < size.width / 2) && map->getPositionX() != 0) {
			auto action = MoveBy::create(0.12f, Vec2(32, 0));
			map->runAction(action);
		}
	}
}

void GameScene::down(Ref * psender)
{
	float y = littleman->getPositionY();
	if (y - 16 > 0 && isCanReach(littleman->getPositionX(), y - 32) ) {
		auto action = MoveBy::create(0.12f, Vec2(0, -32));
		littleman->runAction(action);
		if ((y + map->getPositionY() < size.height / 2) && map->getPositionY() != 0) {
			auto action = MoveBy::create(0.12f, Vec2(0, 32));
			map->runAction(action);
		}
	}
}

void GameScene::right(Ref * psender)
{
	float x = littleman->getPositionX();
	if (x + 16 < MAP_SIZE && isCanReach(x+32,littleman->getPositionY()) ) {
		auto action = MoveBy::create(0.12f, Vec2(32, 0));
		littleman->runAction(action);
		if ((x + map->getPositionX() > size.width / 2) && ((MAP_SIZE - x) > size.width / 2)) {
			auto action = MoveBy::create(0.12f, Vec2(-32, 0));
			map->runAction(action);
		}
	}
}

void GameScene::keyup(float dt)
{
	up(this);
}

void GameScene::keydown(float dt)
{
	down(this);
}

void GameScene::keyright(float dt)
{
	right(this);
}

void GameScene::keyleft(float dt)
{
	left(this);
}

bool GameScene::isCanReach(float x,float y)
{
	int mapX = (int)(x - 16) / 32;
	int mapY = (int)(39 - (y - 16) / 32);

	if (meta) {
		int tileGid = meta->tileGIDAt(Vec2(mapX, mapY));
			if (tileGid == 15) {
				return true;
			}
			else {
				return false;
			}
	}
	else {
		log("fuck");
	}
	
}

