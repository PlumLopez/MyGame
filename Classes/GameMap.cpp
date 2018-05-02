#include"GameMap.h"

GameMap* GameMap::createMap(int floor)
{

	char cfloor[2];
	sprintf(cfloor, "%d", floor);
	std::string strFloor(cfloor);

	GameMap* map = new GameMap;
	if (map->initWithTMXFile("tile maps/" + strFloor + ".tmx"))
	{
		//���ö����init����
		map->extraInit();

		//��ʵ������autorelease�أ�ͳһ��������ƶ������������
		map->autorelease();
		return map;
	}

	CC_SAFE_DELETE(map);
	return NULL;

}

void GameMap::extraInit()
{
	
}
