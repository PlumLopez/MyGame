#include "SaveControl.h"

DECLARE_SINGLETON_MEMBER(SaveControl);


SaveControl::SaveControl()
{
}


SaveControl::~SaveControl()
{
}

void SaveControl::save(int order)
{
	
	//sqlite3* pDataBase;
	//if ((sqlite3_open("Save.db", &pDataBase) != SQLITE_OK)) {
	//	assert("open_failed");
	//}
	//sqlite3_exec(pDataBase, "create table test( ID integer primary key autoincrement, name nvarchar(32) )", nullptr, nullptr, nullptr);
	//sqlite3_exec(pDataBase, "insert into MyTable_1(name) values(����·��)", nullptr, nullptr, nullptr);

	std::string order_str = std::to_string(order);
	std::string space = " ";
	auto Saver = UserDefault::getInstance();
	auto Hero = Global::instance()->hero;
	auto GameMaps = Global::instance()->GameMaps;

	//����ô浵ȷʵ����
	Saver->setBoolForKey((order_str).c_str(), true);

	//����Ӣ���������
	Saver->setIntegerForKey((order_str + space + "HP").c_str(), Hero->HP);
	Saver->setIntegerForKey((order_str + space + "ATK").c_str(), Hero->ATK);
	Saver->setIntegerForKey((order_str + space + "DEF").c_str(), Hero->DEF);
	Saver->setIntegerForKey((order_str + space + "coins").c_str(), Hero->coins);
	Saver->setIntegerForKey((order_str + space + "YellowKeys").c_str(), Hero->YellowKeys);
	Saver->setIntegerForKey((order_str + space + "BlueKeys").c_str(), Hero->BlueKeys);
	Saver->setIntegerForKey((order_str + space + "RedKeys").c_str(), Hero->RedKeys);
	Saver->setIntegerForKey((order_str + space + "currentlevel").c_str(), Global::instance()->currentLevel);
	Saver->setDoubleForKey((order_str + space + "HeroCocosPositionX").c_str(), Hero->getPositionX());
	Saver->setDoubleForKey((order_str + space + "HeroCocosPositionY").c_str(), Hero->getPositionY());

	
	for (auto iter = GameMaps.begin(); iter != GameMaps.end(); iter++) {
		int floor = iter->first;
		std::string floor_str = std::to_string(floor);
		GameMap* map = iter->second;
		auto DoorLayer = map->DoorLayer;
		auto ItemLayer = map->ItemLayer;
		auto enemyLayer = map->enemyLayer;
		Size s = DoorLayer->getLayerSize();

		for (int x = 0; x < s.width; x++) {   
			for (int y = 0; y < s.height; y++) {
				
				std::string x_str = std::to_string(x);
				std::string y_str = std::to_string(y);

				if (DoorLayer->getTileGIDAt(Vec2(x, y)) != 0) {    //�����ͼ�ϵ��� �Ƿ��Ѿ�������
					Saver->setBoolForKey((order_str + space + "isDoorsClosed" + space + floor_str + space + x_str + space + y_str).c_str(), true);  //�Ż��� �洢Ϊtrue
				}

				if (ItemLayer->getTileGIDAt(Vec2(x, y)) != 0) {    //�����ͼ�ϵ���Ʒ �Ƿ��Ѿ�������
					Saver->setBoolForKey((order_str + space + "isItemHaveNotBeenPickedUp" + space + floor_str + space + x_str + space + y_str).c_str(), true); //�������� �洢Ϊtrue
				}

				if (enemyLayer->getTileGIDAt(Vec2(x, y)) != 0) {    //�����ͼ�ϵĹ��� �Ƿ��Ѿ�������
					Saver->setBoolForKey((order_str + space + "isEnemyExisted" + space + floor_str + space + x_str + space + y_str).c_str(), true); //���ﻹ�� �洢Ϊtrue
				}

			}
		}

	}

	Saver->flush();
	log(UserDefault::getXMLFilePath().c_str());
}

void SaveControl::load(int order)
{
	if (!checkIfTheSaveExisted(order)) {
		return;
	}
	std::string order_str = std::to_string(order);
	auto Saver = UserDefault::getInstance();
	auto Hero = Global::instance()->hero;
	auto GameMaps = Global::instance()->GameMaps;


	Hero->HP = Saver->getIntegerForKey((order_str + "HP").c_str());
	Hero->ATK = Saver->getIntegerForKey((order_str + "ATK").c_str());
	Hero->DEF = Saver->getIntegerForKey((order_str + "DEF").c_str());
	Hero->coins = Saver->getIntegerForKey((order_str + "coins").c_str());
	Hero->YellowKeys = Saver->getIntegerForKey((order_str + "YellowKeys").c_str());
	Hero->BlueKeys = Saver->getIntegerForKey((order_str + "BlueKeys").c_str());
	Hero->RedKeys = Saver->getIntegerForKey((order_str + "RedKeys").c_str());
	Global::instance()->currentLevel = Saver->getIntegerForKey((order_str + "currentlevel").c_str());
	int x = Saver->getFloatForKey((order_str + "HeroCocosPositionX").c_str());
	int y = Saver->getFloatForKey((order_str + "HeroCocosPositionY").c_str());
	Hero->setPosition(x, y);

	//����ǰ��map��gameLayer��ȥ��
	Global::instance()->gameLayer->removeChildByTag(kZmap);  
	
	//��������GameMaps���� ��ÿ��ԭ�������map�ͷ� �������µĵ�ͼ������
	for (auto iter : GameMaps) { 
		iter.second->release();
		iter.second = nullptr;
		int floor = iter.first;
		std::string floor_str = std::to_string(floor);
		std::string space = " ";
		GameMap* map = GameMap::createMap(floor);
		TMXLayer* DoorLayer = map->DoorLayer;
		TMXLayer* enemyLayer = map->enemyLayer;
		TMXLayer* ItemLayer = map->ItemLayer;
		Size s = DoorLayer->getLayerSize();

		for (int x = 0; x < s.width; x++) {
			for (int y = 0; y < s.height; y++) {

				std::string x_str = std::to_string(x);
				std::string y_str = std::to_string(y);

				if (DoorLayer->getTileGIDAt(Vec2(x, y)) != 0) {    //�鿴��ͼ�ϵ��� �Ƿ��Ѿ�������
					   //���� ����true ���� ����false
					if (!  (Saver->getBoolForKey((order_str + space + "isDoorsClosed" + space + floor_str + space + x_str + space + y_str).c_str(), false) ) ) {
						DoorLayer->removeTileAt(GameMap::tileCoordForPosition(Vec2(x, y)));
					}
				}

				if (ItemLayer->getTileGIDAt(Vec2(x, y)) != 0) {    //�鿴��ͼ�ϵ���Ʒ �Ƿ��Ѿ�������
						//�������� ����true ���� ����false
					if (!  (Saver->getBoolForKey((order_str + space + "isItemHaveNotBeenPickedUp" + space + floor_str + space + x_str + space + y_str).c_str(), false))) {
						ItemLayer->removeTileAt(GameMap::tileCoordForPosition(Vec2(x, y)));
					}
				}

				if (enemyLayer->getTileGIDAt(Vec2(x, y)) != 0) {    //�鿴��ͼ�ϵĹ��� �Ƿ��Ѿ�������
						//���ﻹ�� ����true ���� ����false
					if (!(Saver->getBoolForKey((order_str + space + "isEnemyExisted" + space + floor_str + space + x_str + space + y_str).c_str(), false))) {
						enemyLayer->removeTileAt(GameMap::tileCoordForPosition(Vec2(x, y)));
					}
				}

			}
		}

		iter.second = map;

	}

	GameMap* currentMap = GameMaps.at(Global::instance()->currentLevel);
	Global::instance()->gameMap = currentMap;
	Global::instance()->gameLayer->addChild(currentMap,kZmap,kZmap);
	currentMap->setPosition(0, 0);

}

bool SaveControl::checkIfTheSaveExisted(int order)
{
	if (!UserDefault::isXMLFileExist()) {
		return false;
	}

	if (UserDefault::getInstance()->getBoolForKey(std::to_string(order).c_str(), false)) {
		return true;
	}
	else {
		return false;
	}
}


