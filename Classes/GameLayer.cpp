#include"GameLayer.h"

GameLayer::GameLayer()
{
	Global::instance()->gameLayer = this;
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	return true;
}

void GameLayer::extraInit(int floor)
{
	GameMap* map = GameMap::createMap(floor);

	this->addChild(map, kZmap, kZmap);
	map->setPosition(0, 0);

	Hero* hero = Hero::create();
	hero->setPosition(GameMap::positionForTileCoord(Global::instance()->heroSpawnTileCoord));
	hero->setZOrder(kZhero);
	this->addChild(hero);


}

GameLayer* GameLayer::createGameLayer(int floor)
{
	GameLayer* layer = GameLayer::create();
	layer->extraInit(floor);
	return layer;
}

void GameLayer::showTip()
{

}

void GameLayer::switchMap(int floor)
{
	GameMap* gameMap = Global::instance()->gameMap;
	//��ȡ�����
	TMXObjectGroup* group = gameMap->objectGroupNamed("object");

	//��ȡ������ڵ����ж���
	const ValueVector &objects = group->getObjects();

	//�������ж���
	for (ValueVector::const_iterator it = objects.begin(); it != objects.end(); it++)
	{
		const ValueMap &dict = (*it).asValueMap();

		std::string key = "x";

		//��ȡx����
		int x = dict.at(key).asInt();
		key = "y";

		//��ȡy����
		int y = dict.at(key).asInt();
		Point tileCoord = GameMap::tileCoordForPosition(Point(x, y));

		//����ΨһID
		int index = tileCoord.x + tileCoord.y * gameMap->getMapSize().width;

		this->removeChildByTag(index);

	}
	this->removeChildByTag(kZmap);
	gameMap = GameMap::createMap(floor);
	this->addChild(gameMap, kZmap, kZmap);
	Global::instance()->hero->setPosition(GameMap::positionForTileCoord(Global::instance()->heroSpawnTileCoord));
	Global::instance()->hero->setFaceDirection(kdown);
}
