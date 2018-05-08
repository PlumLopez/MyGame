#include "GameScene.h"


USING_NS_CC;
#define MAP_SIZE 416

Scene* GameScene::createScene()
{
    return GameScene::create();
}


bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	Global::instance()->gameScene = this;

	
	GameLayer* gamelayer = GameLayer::createGameLayer(0);
	addChild(gamelayer,1);
	gamelayer->setPosition(192 , 0);

	LayerColor* statusLayer = LayerColor::create(Color4B::YELLOW, 192, 416);
	addChild(statusLayer, 1);
	statusLayer->setPosition(0, 0);

	ControlLayer* controllayer = ControlLayer::create();
	addChild(controllayer, 2);
	controllayer->setPosition(Vec2::ZERO);


	//���������ʾ������Ϣ��״̬��
	//��ʾѪ��
	TTFConfig ttfconfig("fonts/arial.ttf", 12);
	std::string temp = std::to_string(Global::instance()->hero->HP);
	auto currentHP = Label::createWithTTF(ttfconfig, "Hero HP : " + temp);
	currentHP->setAnchorPoint(Vec2::ZERO);
	currentHP->setColor(Color3B::BLACK);
	currentHP->setPosition(192 / 3, 32 * 11);
	this->addChild(currentHP, kZHP, kZHP);
	//��ʾ������
	temp = std::to_string(Global::instance()->hero->ATK);
	auto currentATK = Label::createWithTTF(ttfconfig, "Hero ATK : " + temp);
	currentATK->setAnchorPoint(Vec2::ZERO);
	currentATK->setColor(Color3B::BLACK);
	currentATK->setPosition(192 / 3, 32 * 10);
	this->addChild(currentATK, kZATK, kZATK);
	//��ʾ������
	temp = std::to_string(Global::instance()->hero->DEF);
	auto currentDEF = Label::createWithTTF(ttfconfig, "Hero DEF : " + temp);
	currentDEF->setAnchorPoint(Vec2::ZERO);
	currentDEF->setColor(Color3B::BLACK);
	currentDEF->setPosition(192 / 3, 32 * 9);
	this->addChild(currentDEF, kZDEF, kZDEF);
	//��ʾ��Կ������
	temp = std::to_string(Global::instance()->hero->YellowKeys);
	auto currentYellowKeys = Label::createWithTTF(ttfconfig, "Hero YellowKeys : " + temp);
	currentYellowKeys->setAnchorPoint(Vec2::ZERO);
	currentYellowKeys->setColor(Color3B::BLACK);
	currentYellowKeys->setPosition(192 / 3, 32 * 8);
	this->addChild(currentYellowKeys, kZYellowKeys, kZYellowKeys);
	//��ʾ��Կ������
	temp = std::to_string(Global::instance()->hero->BlueKeys);
	auto currentBlueKeys = Label::createWithTTF(ttfconfig, "Hero BlueKeys : " + temp);
	currentBlueKeys->setAnchorPoint(Vec2::ZERO);
	currentBlueKeys->setColor(Color3B::BLACK);
	currentBlueKeys->setPosition(192 / 3, 32 * 7);
	this->addChild(currentBlueKeys, kZBlueKeys, kZBlueKeys);
	//��ʾ��Կ������
	temp = std::to_string(Global::instance()->hero->RedKeys);
	auto currentRedKeys = Label::createWithTTF(ttfconfig, "Hero RedKeys : " + temp);
	currentRedKeys->setAnchorPoint(Vec2::ZERO);
	currentRedKeys->setColor(Color3B::BLACK);
	currentRedKeys->setPosition(192 / 3, 32 * 6);
	this->addChild(currentRedKeys, kZRedKeys, kZRedKeys);

	

}

//ˢ�����״̬�� �β�ΪkZoder��ö�ٳ��� ��ʾ����仯����Ϣ���
void GameScene::refreshStatus(kZorder order)
{
	Label* newLabel;
	GameScene* tempGameScene = Global::instance()->gameScene;

	if (order == kZHP) {
		newLabel = createNewLabelForStatus((Label*)(tempGameScene->getChildByTag(kZHP)));
		this->removeChildByTag(kZHP);
		this->addChild(newLabel, kZHP, kZHP);
	}
	else if (order == kZATK) {
		newLabel = createNewLabelForStatus((Label*)(tempGameScene->getChildByTag(kZATK)));
		this->removeChildByTag(kZATK);
		this->addChild(newLabel, kZATK, kZATK);
	}
	else if (order == kZDEF) {
		newLabel = createNewLabelForStatus((Label*)(tempGameScene->getChildByTag(kZDEF)));
		this->removeChildByTag(kZDEF);
		this->addChild(newLabel, kZDEF, kZDEF);
	}
	else if (order == kZYellowKeys) {
		newLabel = createNewLabelForStatus((Label*)(tempGameScene->getChildByTag(kZYellowKeys)));
		this->removeChildByTag(kZYellowKeys);
		this->addChild(newLabel, kZYellowKeys, kZYellowKeys);
	}
	else if (order == kZBlueKeys) {
		newLabel = createNewLabelForStatus((Label*)(tempGameScene->getChildByTag(kZBlueKeys)));
		this->removeChildByTag(kZBlueKeys);
		this->addChild(newLabel, kZBlueKeys, kZBlueKeys);
	}
	else if (order == kZRedKeys) {
		newLabel = createNewLabelForStatus((Label*)(tempGameScene->getChildByTag(kZRedKeys)));
		this->removeChildByTag(kZRedKeys);
		this->addChild(newLabel, kZRedKeys, kZRedKeys);
	}

	
}

Label* GameScene::createNewLabelForStatus(Label* oldLabel) {
	TTFConfig ttfconfig("fonts/arial.ttf", 12);
	std::string newString;
	switch (oldLabel->getZOrder()) {
	case kZHP:newString = std::string("Hero HP : " + std::to_string(Global::instance()->hero->HP)); break;
	case kZATK:newString = std::string("Hero ATK : " + std::to_string(Global::instance()->hero->ATK)); break;
	case kZDEF:newString = std::string("Hero DEF : " + std::to_string(Global::instance()->hero->DEF)); break;
	case kZYellowKeys:newString = std::string("Hero YellowKeys : " + std::to_string(Global::instance()->hero->YellowKeys)); break;
	case kZBlueKeys:newString = std::string("Hero BlueKeys : " + std::to_string(Global::instance()->hero->BlueKeys)); break;
	case kZRedKeys:newString = std::string("Hero RedKeys : " + std::to_string(Global::instance()->hero->RedKeys)); break;
	default:;
	}
	Label* newLabel = Label::createWithTTF(ttfconfig, newString);
	newLabel->setAnchorPoint(Vec2::ZERO);
	newLabel->setColor(oldLabel->getColor());
	newLabel->setPosition(oldLabel->getPosition());
	return newLabel;

}


