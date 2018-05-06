#ifndef _GLOBAL_H_
#define _GLOBAL_H_


#include"MagicTower.h"
USING_NS_CC;

class GameScene;
class GameLayer;
class ControlLayer;
class GameMap;
class Hero;

class Global : public Singleton<Global>
{
public:
	Global(void);
	~Global(void);

	GameScene *gameScene;

	//��Ϸ��ͼ��
	GameLayer *gameLayer;

	ControlLayer *controlLayer;

	//��Ϸ��ͼ
	GameMap *gameMap;

	//��ʿ
	Hero *hero;

	//Ŀ���ͼ�Ĳ���
	int currentLevel;

	//��ʿ���ֵ���ʼλ��
	Point heroSpawnTileCoord;
};



#endif

