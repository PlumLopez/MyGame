/*#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "CommonHeader.h"


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

*/